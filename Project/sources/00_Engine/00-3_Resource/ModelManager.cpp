/*============================================================
*	@file	 : ModelManager.cpp
*	@brief	 : テクスチャ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/07/30
*============================================================*/
#include "ModelManager.h"
#include "DeviceManager.h"
#include "Utility.h"

// assimp関連
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"

Model* ModelManager::Load(const char* modelPath)
{
	// キャッシュ取得用にパスを正規化
	std::string key = Utility::File::normalizePath(modelPath);

	// キャッシュが存在すれば返す
	auto it = mModels.find(key);

	if (it != mModels.end()) {
		return it->second.get();
	}

	// モデル生成
	std::unique_ptr<Model> model = std::make_unique<Model>();

	if (!generateModel(*model, key))
		return nullptr;

	Model* result = model.get();
	
	// モデル登録
	mModels.emplace(key, std::move(model));

	return result;
}

bool ModelManager::generateModel(Model& model, const std::string& path)
{
	Assimp::Importer importer;

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

	OutputDebugStringA(
		("Mesh Count : " + std::to_string(scene->mNumMeshes)).c_str());

	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[i];

		OutputDebugStringA(
			("Vertices : " +
				std::to_string(mesh->mNumVertices) + "\n").c_str());
	}

	return true;
}