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
#include "ModelRenderer.h"
#include "Utility.h"
#include <DirectXTex.h>
using namespace DirectX;

Model* ModelManager::Load(const char* modelPath)
{
	// キャッシュ取得用にパスを正規化
	std::string key = Utility::File::normalizePath(modelPath);

	// キャッシュが存在すれば返す
	auto it = mModels.find(key);

	if (it != mModels.end()) {
		return it->second.get();
	}

	return nullptr;
}

bool ModelManager::generateModel(Model& model, const std::string& path)
{
	return false;
}