/*============================================================
*	@file	 : AssimpLoader.cpp
*	@brief	 : assimpによるモデルロード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/02
*	@updated : 2026/08/02
*============================================================*/
#include "AssimpLoader.h"
#include "DeviceManager.h"
#include "Model.h"
#include <memory>
#include <Windows.h>
#include <wrl/client.h>
#include <DirectXTex/DirectXTex.h>

// assimp関連
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"

using namespace Element;
using namespace DirectX;

/*--------------------------------------------------
	デバッグ用関数 プロトタイプ宣言
----------------------------------------------------*/
namespace AssimpDebug {
	void printMeshCount(const aiScene* scene);
	void printVertexCount(const aiMesh* mesh);
	void printVertexElement(Element::VERTEX3D& vertex, int v);
	void printIndexElement(const aiFace& face, int f);
	void printConvertedIndex(const std::vector<uint32_t>& indices,
		uint32_t startIndex, uint32_t indexNum);
	void printTextureElement(const aiTexture* tex, unsigned int index);
}

bool AssimpLoader::generateModel(Model& model, const std::string& path)
{
	mTextureMap.clear();

	Assimp::Importer importer{};

	// モデルロード
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenSmoothNormals
	);

	if (!scene){
		OutputDebugStringA(importer.GetErrorString());
		return false;
	}

	// メッシュ読み込み
	if (!loadMeshes(scene, model))
		return false;

	// テクスチャ読み込み
	if (!loadTextures(scene, model))
		return false;

	// マテリアル読み込み
	loadMaterials(scene, model);

	mTextureMap.clear();

	return true;
}

bool AssimpLoader::loadMeshes(const aiScene* scene, Model& model)
{
	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {

		std::vector<VERTEX3D> vertices{};
		std::vector<uint32_t> indices{};

		aiMesh* mesh = scene->mMeshes[m];

		ModelMesh modelMesh{};

		uint32_t startIndex = static_cast<uint32_t>(indices.size());

		/*--------------------------------------------------
			頂点データ作成
		----------------------------------------------------*/
		for (unsigned int v = 0; v < mesh->mNumVertices; ++v) {
			vertices.push_back(convertVertex(mesh, v));
		}

		/*--------------------------------------------------
			インデックス取得
		----------------------------------------------------*/
		for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
			const aiFace& face = mesh->mFaces[f];

			for (unsigned int i = 0; i < face.mNumIndices; ++i) {
				indices.push_back(face.mIndices[i]);
			}
		}

		uint32_t indexNum = static_cast<uint32_t>(indices.size()) - startIndex;

		// サブセット生成
		modelMesh.subsets.push_back(createSubset(mesh, startIndex, indexNum));

		// モデル用メッシュ作成
		if (!modelMesh.Create(vertices, indices))
			return false;

		model.AddMesh(std::move(modelMesh));
	}

	return true;
}

Element::VERTEX3D AssimpLoader::convertVertex(const aiMesh* mesh, int v)
{
	// 頂点データ取得
	VERTEX3D vertex{};

	// 座標取得
	vertex.Position =
	{
		mesh->mVertices[v].x,
		mesh->mVertices[v].y,
		mesh->mVertices[v].z
	};

	// 法線
	if (mesh->HasNormals())
	{
		vertex.Normal =
		{
			mesh->mNormals[v].x,
			mesh->mNormals[v].y,
			mesh->mNormals[v].z
		};
	}

	// UV
	if (mesh->HasTextureCoords(0))
	{
		vertex.TexCoord = {
			mesh->mTextureCoords[0][v].x,
			mesh->mTextureCoords[0][v].y
		};
	}

	// カラー
	if (mesh->HasVertexColors(0))
	{
		vertex.Diffuse = {
			mesh->mColors[0][v].r,
			mesh->mColors[0][v].g,
			mesh->mColors[0][v].b,
			mesh->mColors[0][v].a
		};
	}
	else
	{
		vertex.Diffuse = {
			1.0f,
			1.0f,
			1.0f,
			1.0f
		};
	}

	return vertex;
}

ModelMesh::SUBSET AssimpLoader::createSubset(const aiMesh* mesh, uint32_t startIndex, uint32_t indexNum)
{
	// サブセット生成
	ModelMesh::SUBSET subset{};

	subset.StartIndex = startIndex;
	subset.IndexNum = indexNum;
	subset.MaterialIndex = mesh->mMaterialIndex;

	return subset;
}

bool AssimpLoader::loadTextures(const aiScene* scene, Model& model)
{
	// テクスチャ取得
	model.mTextures.reserve(scene->mNumTextures);

	for (unsigned int i = 0; i < scene->mNumTextures; ++i) {
		const aiTexture* tex = scene->mTextures[i];

		// テクスチャ生成;
		auto texture = std::make_unique<Texture>();

		TexMetadata metadata{};
		ScratchImage image{};

		// テクスチャ読み込み
		LoadFromWICMemory(reinterpret_cast<const uint8_t*>(tex->pcData),
			static_cast<size_t>(tex->mWidth), WIC_FLAGS_NONE, &metadata, image);

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

		HRESULT hr = CreateShaderResourceView(
			D3D11::DeviceManager::getInstance().GetDevice(),
			image.GetImages(), image.GetImageCount(), metadata, srv.GetAddressOf());

		if (FAILED(hr)) return false;

		// サイズとSRVを登録
		texture->mSize = { static_cast<UINT>(metadata.width), static_cast<UINT>(metadata.height) };
		texture->_mSRV = srv;

		model.mTextures.push_back(std::move(texture));

		// 検索用マップへ登録
		Texture* ptr = model.mTextures.back().get();
		mTextureMap.emplace(tex->mFilename.C_Str(), ptr);
	}

	return true;
}

void AssimpLoader::loadMaterials(const aiScene* scene, Model& model)
{
	// マテリアル取得
	for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
		Model::MATERIAL material{};

		aiMaterial* aiMat = scene->mMaterials[i];
		aiColor4D color{};

		aiString path{};

		// テクスチャ取得
		if (aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
			auto it = mTextureMap.find(path.C_Str());

			if (it != mTextureMap.end()) {
				material._Texture = it->second;
				material.Material.TextureEnable = true;
			}
		}

		// カラー取得
		if (AI_SUCCESS == aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_DIFFUSE, &color)) {
			material.Material.Diffuse = {
				color.r,
				color.g,
				color.b,
				color.a
			};
		}

		model.mMaterials.push_back(material);
	}
}

/*--------------------------------------------------
	デバッグ用関数
----------------------------------------------------*/
void AssimpDebug::printMeshCount(const aiScene* scene)
{
#ifndef NDEBUG
	OutputDebugStringA(
		("----------printMeshCount----------\n"
			"Meshs : " + std::to_string(scene->mNumMeshes) + "\n").c_str());
#endif
}

void AssimpDebug::printVertexCount(const aiMesh* mesh)
{
#ifndef NDEBUG
	OutputDebugStringA(
		("----------printVertexCount----------\n"
			"Vertices : " +
			std::to_string(mesh->mNumVertices) + "\n").c_str());
#endif
}

void AssimpDebug::printVertexElement(Element::VERTEX3D& vertex, int v)
{
#ifndef NDEBUG
	if (v < 5)
	{
		std::string log =
			"----------printVertexElement----------\n"
			"Vertex[" + std::to_string(v) + "]\n" +
			" Pos : " +
			std::to_string(vertex.Position.x) + ", " +
			std::to_string(vertex.Position.y) + ", " +
			std::to_string(vertex.Position.z) + "\n" +
			" Normal : " +
			std::to_string(vertex.Normal.x) + ", " +
			std::to_string(vertex.Normal.y) + ", " +
			std::to_string(vertex.Normal.z) + "\n" +
			" UV : " +
			std::to_string(vertex.TexCoord.x) + ", " +
			std::to_string(vertex.TexCoord.y) + "\n" +
			" Diffuse : " +
			std::to_string(vertex.Diffuse.x) + ", " +
			std::to_string(vertex.Diffuse.y) + ", " +
			std::to_string(vertex.Diffuse.z) + ", " +
			std::to_string(vertex.Diffuse.w) + "\n";

		OutputDebugStringA(log.c_str());
	}
#endif
}

void AssimpDebug::printIndexElement(const aiFace& face, int f)
{
#ifndef NDEBUG
	std::string log =
		"----------printIndexElement----------\n"
		"Face[" + std::to_string(f) + "] : " +
		std::to_string(face.mIndices[0]) + ", " +
		std::to_string(face.mIndices[1]) + ", " +
		std::to_string(face.mIndices[2]) +
		"\n";

	OutputDebugStringA(log.c_str());
#endif
}

void AssimpDebug::printConvertedIndex(const std::vector<uint32_t>& indices, uint32_t startIndex, uint32_t indexNum)
{
#ifndef NDEBUG
	std::string log = "----------printConvertedIndex----------\n";

	for (uint32_t i = startIndex; i < startIndex + indexNum; i += 3)
	{
		log +=
			"Triangle[" +
			std::to_string((i - startIndex) / 3) +
			"] : " +
			std::to_string(indices[i]) + ", " +
			std::to_string(indices[i + 1]) + ", " +
			std::to_string(indices[i + 2]) +
			"\n";
	}

	OutputDebugStringA(log.c_str());
#endif
}

void AssimpDebug::printTextureElement(const aiTexture* tex, unsigned int index)
{
#ifndef NDEBUG

	std::string log = "----------printTextureElement----------\n"
		"Texture[" + std::to_string(index) + "]\n" +
		" Filename : " + std::string(tex->mFilename.C_Str()) + "\n" +
		" Width : " + std::to_string(tex->mWidth) + "\n" +
		" Height : " + std::to_string(tex->mHeight) + "\n";

	OutputDebugStringA(log.c_str());

#endif
}