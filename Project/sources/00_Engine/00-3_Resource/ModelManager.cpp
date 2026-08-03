/*============================================================
*	@file	 : ModelManager.cpp
*	@brief	 : テクスチャ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/07/30
*============================================================*/
#include "ModelManager.h"
#include "AssimpLoader.h"
#include "TextureManager.h"
#include "Utility.h"

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

	// Loaderからモデルをインポート
	if (!AssimpLoader::getInstance().GenerateModel(*model, key))
		return nullptr;

	Model* result = model.get();
	
	// モデル登録
	mModels.emplace(key, std::move(model));

	return result;
}