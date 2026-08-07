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
#include "TextureManager.h"
#include "AnimationManager.h"
#include "Model.h"
#include "Utility.h"
#include <memory>
#include <Windows.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>

// assimp関連
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"

using namespace Element;
using namespace DirectX;

namespace
{
	DirectX::XMFLOAT4X4 convertMatrix(const aiMatrix4x4& matrix)
	{
		return {
			matrix.a1, matrix.a2, matrix.a3, matrix.a4,
			matrix.b1, matrix.b2, matrix.b3, matrix.b4,
			matrix.c1, matrix.c2, matrix.c3, matrix.c4,
			matrix.d1, matrix.d2, matrix.d3, matrix.d4
		};
	}
}

/*--------------------------------------------------
	デバッグ用関数 プロトタイプ宣言
----------------------------------------------------*/
#ifndef NDEBUG
namespace AssimpDebug {
	void printMeshCount(const aiScene* scene);
	void printVertexCount(const aiMesh* mesh);
	void printVertexElement(Element::VERTEX3D& vertex, int v);
	void printIndexElement(const aiFace& face, int f);
	void printConvertedIndex(const std::vector<uint32_t>& indices,
		uint32_t startIndex, uint32_t indexNum);
	void printTextureElement(const aiTexture* tex, unsigned int index);
	void printAnimationElement(const aiScene* scene);
}
#endif

bool AssimpLoader::GenerateModel(Model& model, const std::string& path)
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

	if (!scene) {
		OutputDebugStringA(importer.GetErrorString());
		return false;
	}

	if (!AiAnimationLoader::loadBoneHierarchy(scene->mRootNode, model.mSkeleton, -1)) {
		return false;
	}

	if (!AiAnimationLoader::loadBones(scene, model.mSkeleton)) {
		return false;
	}

	// メッシュ読み込み
	if (!loadMeshes(scene, model, model.mSkeleton))
		return false;

	if (scene->mAnimations) {
		AiAnimationLoader::GenerateAnim(scene, model.mSkeleton);
	}

	// 埋め込みテクスチャ読み込み
	if (!loadTextures(scene, model))
		return false;

	// マテリアル読み込み
	loadMaterials(scene, model, path);

	mTextureMap.clear();

	return true;
}

bool AssimpLoader::loadMeshes(const aiScene* scene, Model& model, const Skeleton& skeleton)
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
			頂点ウェイト取得
		----------------------------------------------------*/
		for (UINT boneIndex = 0; boneIndex < mesh->mNumBones; boneIndex++) {
			const aiBone* aiBone = mesh->mBones[boneIndex];

			int skeletonIndex = skeleton.FindBone(aiBone->mName.C_Str());

			if (skeletonIndex < 0) {
				continue;
			}

			// ウェイト正規化
			for (UINT weightIndex = 0; weightIndex < aiBone->mNumWeights; weightIndex++) {
				UINT vertexId = aiBone->mWeights[weightIndex].mVertexId;
				const aiVertexWeight& weight = aiBone->mWeights[weightIndex];

				for (int slot = 0; slot < 4; slot++) {
					if (vertices[vertexId].BoneWeights[slot] == 0.0f) {
						vertices[vertexId].BoneIndices[slot] =
							static_cast<uint32_t>(skeletonIndex);

						vertices[vertexId].BoneWeights[slot] = weight.mWeight;

						//float total =
						//	vertices[weight.mVertexId].BoneWeights[0] +
						//	vertices[weight.mVertexId].BoneWeights[1] +
						//	vertices[weight.mVertexId].BoneWeights[2] +
						//	vertices[weight.mVertexId].BoneWeights[3];

						//if (total > 0)
						//{
						//	vertices[weight.mVertexId].BoneWeights[slot] /= total;
						//}

						break;
					}
				}
			}
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

	vertex.BoneIndices[0] = 0;
	vertex.BoneIndices[1] = 0;
	vertex.BoneIndices[2] = 0;
	vertex.BoneIndices[3] = 0;

	vertex.BoneWeights[0] = 0.0f;
	vertex.BoneWeights[1] = 0.0f;
	vertex.BoneWeights[2] = 0.0f;
	vertex.BoneWeights[3] = 0.0f;

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
		HRESULT hr = LoadFromWICMemory(reinterpret_cast<const uint8_t*>(tex->pcData),
			static_cast<size_t>(tex->mWidth), WIC_FLAGS_NONE, &metadata, image);
		if (FAILED(hr)) return false;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

		hr = CreateShaderResourceView(
			D3D11::DeviceManager::getInstance().GetDevice(),
			image.GetImages(), image.GetImageCount(), metadata, srv.GetAddressOf());
		if (FAILED(hr)) return false;

		// サイズとSRVを登録
		texture->mSize = { static_cast<UINT>(metadata.width), static_cast<UINT>(metadata.height) };
		texture->_mSRV = srv;

		// モデルへ登録
		Texture* ptr = texture.get();
		model.mTextures.push_back(std::move(texture));

		// 検索用マップへ登録
		mTextureMap.emplace(tex->mFilename.C_Str(), ptr);
	}

	return true;
}

void AssimpLoader::loadMaterials(const aiScene* scene, Model& model, const std::string& modelPath)
{
	// マテリアル取得
	for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
		Model::MATERIAL material{};

		aiMaterial* aiMat = scene->mMaterials[i];

		// テクスチャ取得
		aiString path{};

		if (aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {

			if (scene->mNumTextures > 0) {
				// 埋め込みテクスチャ取得
				auto it = mTextureMap.find(path.C_Str());

				if (it != mTextureMap.end()) {
					material._Texture = it->second;
					material.Material.TextureEnable = true;
				}
			}
			else {
				// mtlファイルからテクスチャ取得
				std::filesystem::path dir = Utility::File::getDirectoryPath(modelPath.c_str());

				// mtlファイル登録テクスチャ探索用パス
				std::filesystem::path mtlTexPath = dir / path.C_Str();

				// mtlファイル登録テクスチャをロード
				material._Texture = TextureManager::getInstance().Load(mtlTexPath.string().c_str());

				if (!material._Texture) {
					return;
				}
				else {
					material.Material.TextureEnable = true;
				}
			}
		}

		// カラー取得
		aiColor4D color{};

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
	アニメーション関連ロード
----------------------------------------------------*/
bool AssimpLoader::AiAnimationLoader::GenerateAnim(const aiScene* scene, Skeleton& skeleton)
{
	if (!loadAnimations(scene, skeleton)) {
		return false;
	}

	return true;
}

bool AssimpLoader::AiAnimationLoader::loadBones(const aiScene* scene, Skeleton& skeleton)
{
	aiMatrix4x4 inverse = scene->mRootNode->mTransformation.Inverse();

	DirectX::XMMATRIX dxInverse = DirectX::XMMatrixSet(
			inverse.a1, inverse.a2, inverse.a3, inverse.a4,
			inverse.b1, inverse.b2, inverse.b3, inverse.b4,
			inverse.c1, inverse.c2, inverse.c3, inverse.c4,
			inverse.d1, inverse.d2, inverse.d3, inverse.d4);

	DirectX::XMStoreFloat4x4(&skeleton.GetGlobalInverse(), dxInverse);

	// 全メッシュ検索
	for (UINT meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
	{
		const aiMesh* mesh = scene->mMeshes[meshIndex];

		// メッシュ内のボーンを検索
		for (UINT i = 0; i < mesh->mNumBones; i++)
		{
			const aiBone* aiBone = mesh->mBones[i];

			int skeletonIndex = skeleton.FindBone(aiBone->mName.C_Str());

			if (skeletonIndex == -1)
			{
				continue;
			}

			skeleton.GetBone(skeletonIndex).Offset =
				convertMatrix(aiBone->mOffsetMatrix);

			//const aiBone* aiBone = mesh->mBones[i];
			//int boneIndex = skeleton.FindBone(aiBone->mName.C_Str());

			//auto offset = aiBone->mOffsetMatrix;

			//// 登録済みならスキップ
			//if (boneIndex != -1){
			//	continue;
			//}

			//// ボーン登録
			//Skeleton::Bone bone{};
			//bone.Name = aiBone->mName.C_Str();
			//bone.Offset = convertMatrix(aiBone->mOffsetMatrix);
			//skeleton.AddBone(bone);
		}
	}

	return true;
}

bool AssimpLoader::AiAnimationLoader::loadBoneHierarchy(const aiNode* node, Skeleton& skeleton, int parentIndex)
{
	// ボーン階層取得
	int currentIndex = parentIndex;

	int boneIndex = skeleton.FindBone(node->mName.C_Str());

	if (boneIndex == -1)
	{
		Skeleton::Bone bone{};
		bone.Name = node->mName.C_Str();
		bone.Local = convertMatrix(node->mTransformation);

		boneIndex = skeleton.AddBone(bone);
	}

	auto& bone = skeleton.GetBone(boneIndex);

	bone.ParentIndex = parentIndex;
	bone.Local = convertMatrix(node->mTransformation);

	currentIndex = boneIndex;

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		loadBoneHierarchy(node->mChildren[i], skeleton, currentIndex);
	}

	return true;
}

bool AssimpLoader::AiAnimationLoader::loadAnimations(const aiScene* scene, const Skeleton& skeleton)
{
	if (scene->mNumAnimations == 0) {
		return false;
	}

	for (UINT i = 0; i < scene->mNumAnimations; i++) {
		auto animation = std::make_unique<Animation>();

		loadAnimationClip(scene, skeleton, *animation, i);

		// Managerに登録
		std::string name = scene->mAnimations[i]->mName.C_Str();
		AnimationManager::getInstance().Register(name, std::move(animation));
	}

	return true;
}

bool AssimpLoader::AiAnimationLoader::loadAnimationClip(const aiScene* scene, const Skeleton& skeleton, Animation& animation, UINT index)
{
	// アニメーションが存在しなければreturn
	if (scene->mNumAnimations == 0) {
		return false;
	}

	// 指定したアニメーションを取得
	const aiAnimation* aiAnim = scene->mAnimations[index];

	/*--------------------------------------------------
		アニメーション全体情報登録
	----------------------------------------------------*/
	// 総再生時間
	animation.mDuration = aiAnim->mDuration;

	// 1秒あたりのTick数
	animation.mTicksPerSecond = aiAnim->mTicksPerSecond != 0 ? aiAnim->mTicksPerSecond : 25.0;

	// ボーンごとのアニメーションチャンネル取得
	for (UINT channelIndex = 0; channelIndex < aiAnim->mNumChannels; channelIndex++) {
		const aiNodeAnim* aiChannel = aiAnim->mChannels[channelIndex];

		std::string boneName = aiChannel->mNodeName.C_Str();

		// Assimpの名前に親階層が付いている場合を除去
		size_t separator = boneName.find_last_of('|');

		if (separator != std::string::npos)
		{
			boneName = boneName.substr(separator + 1);
		}

		int boneIndex = skeleton.FindBone(boneName);

		if (boneIndex == -1)
		{
			continue;
		}

		Animation::Channel channel{};
		channel.BoneIndex = boneIndex;

		/*--------------------------------------------------
			移動キー
		----------------------------------------------------*/
		for (UINT i = 0; i < aiChannel->mNumPositionKeys; i++) {
			const aiVectorKey& key = aiChannel->mPositionKeys[i];

			Animation::KeyPosition position{};

			position.Time =	key.mTime;
			position.Position = { key.mValue.x, key.mValue.y, key.mValue.z };

			channel.Positions.push_back(position);
		}

		/*--------------------------------------------------
			回転キー
		----------------------------------------------------*/
		for (UINT i = 0; i < aiChannel->mNumRotationKeys; i++) {
			const aiQuatKey& key = aiChannel->mRotationKeys[i];

			Animation::KeyRotation rotation{};

			rotation.Time = key.mTime;
			rotation.Rotation = { key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w };


			channel.Rotations.push_back(rotation);
		}

		/*--------------------------------------------------
			拡大縮小キー
		----------------------------------------------------*/
		for (UINT i = 0; i < aiChannel->mNumScalingKeys; i++) {
			const aiVectorKey& key = aiChannel->mScalingKeys[i];

			Animation::KeyScale scale{};

			scale.Time = key.mTime;
			scale.Scale = { key.mValue.x, key.mValue.y, key.mValue.z };

			channel.Scales.push_back(scale);
		}

		// チャンネル情報登録
		animation.AddChannel(channel);
	}

	return true;
}

#ifndef NDEBUG
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

void AssimpDebug::printAnimationElement(const aiScene* scene)
{
#ifndef NDEBUG

	std::string log = "----------printAnimationElement----------\n";

	// シーン情報取得
	log += std::format("Scene\n" " Meshes:{}\n" " Materials:{}\n" " Animations:{}\n",
		scene->mNumMeshes, scene->mNumMaterials, scene->mNumAnimations).c_str();

	// アニメーション情報取得
	const aiAnimation* anim = scene->mAnimations[0];

	log += std::format("Animation\n" "Name:{}\n" "Duration:{}\n" "TicksPerSecond:{}\n" "Channels:{}\n",
		anim->mName.C_Str(), anim->mDuration, anim->mTicksPerSecond, anim->mNumChannels).c_str();

	// チャンネル情報取得
	for (UINT i = 0; i < anim->mNumChannels; i++)
	{
		auto channel = anim->mChannels[i];

		log += std::format("Channel:{}\n", channel->mNodeName.C_Str()).c_str();
	}

	// キー情報取得
	const aiNodeAnim* channel = anim->mChannels[0];

	log += std::format("PositionKeys:{}\n" "RotationKeys:{}\n" "ScaleKeys:{}\n",
		channel->mNumPositionKeys, channel->mNumRotationKeys, channel->mNumScalingKeys).c_str();

	for (UINT i = 0; i < channel->mNumRotationKeys; i++)
	{
		auto& key = channel->mRotationKeys[i];

		log += std::format("Time:{}\n" "Quat:{} {} {} {}\n",
			key.mTime, key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w
		).c_str();
	}

	OutputDebugStringA(log.c_str());

#endif
}
#endif