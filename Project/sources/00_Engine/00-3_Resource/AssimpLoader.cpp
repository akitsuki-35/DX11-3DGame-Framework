/*============================================================
*	@file	 : AssimpLoader.cpp
*	@brief	 : assimpによるモデルロード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/02
*	@updated : 2026/08/02
*============================================================*/
#include "AssimpLoader.h"
#include "Model.h"
#include <vector>
#include <Windows.h>

// assimp関連
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"

using namespace Element;

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
}

bool AssimpLoader::generateModel(Model& model, const std::string& path)
{
	Assimp::Importer importer{};

	// モデルロード
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenSmoothNormals
	);

	if (!scene)
	{
		OutputDebugStringA(importer.GetErrorString());
		return false;
	}

	AssimpDebug::printMeshCount(scene);

	std::vector<VERTEX3D> vertices{};
	std::vector<uint32_t> indices{};

	uint32_t vertexOffset = 0;

	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
		aiMesh* mesh = scene->mMeshes[m];
		AssimpDebug::printVertexCount(mesh);

		ModelMesh modelMesh{};

		uint32_t startIndex = indices.size();

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

			AssimpDebug::printIndexElement(face, f);

			for (unsigned int i = 0; i < face.mNumIndices; ++i) {
				indices.push_back(face.mIndices[i] + vertexOffset);
			}
		}

		uint32_t indexNum = indices.size() - startIndex;
		AssimpDebug::printConvertedIndex(indices, startIndex, indexNum);

		// サブセット生成
		modelMesh.subsets.push_back(createSubset(mesh, startIndex, indexNum));

		vertexOffset += mesh->mNumVertices;

		modelMesh.DebugPrintSubsets();

		// モデル用メッシュ作成
		modelMesh.Create(vertices, indices);
		model.AddMesh(std::move(modelMesh));
	}

	convertMaterial(scene, model);

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

	AssimpDebug::printVertexElement(vertex, v);

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

void AssimpLoader::convertMaterial(const aiScene* scene, Model& model)
{
	// マテリアル取得
	for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
		Model::MATERIAL material{};

		aiMaterial* aiMat = scene->mMaterials[i];
		aiColor4D color;

		// カラー取得
		if (AI_SUCCESS == aiGetMaterialColor(aiMat, AI_MATKEY_COLOR_DIFFUSE, &color)) {
			material.material.Diffuse = {
				color.r,
				color.g,
				color.b,
				color.a
			};
		}

		////テクスチャ読み込み
		//for (int i = 0; i < scene->mNumTextures; i++)
		//{
		//	aiTexture* aitexture = scene->mTextures[i];

		//	ID3D11Resource* presource{};

		//	ID3D11ShaderResourceView* texture;
		//	TexMetadata metadata;
		//	ScratchImage image;
		//	LoadFromWICMemory(aitexture->pcData, aitexture->mWidth, WIC_FLAGS_NONE, &metadata, image);
		//	CreateShaderResourceView(Direct3D_GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &texture);
		//	assert(texture);

		//	material.texture[aitexture->mFilename.data] = texture;
		//}

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
	OutputDebugStringA("----------printConvertedIndex----------\n");
	for (uint32_t i = startIndex; i < startIndex + indexNum; i += 3)
	{
		std::string log =
			"Triangle[" +
			std::to_string((i - startIndex) / 3) +
			"] : " +
			std::to_string(indices[i]) + ", " +
			std::to_string(indices[i + 1]) + ", " +
			std::to_string(indices[i + 2]) +
			"\n";

		OutputDebugStringA(log.c_str());
	}
#endif
}