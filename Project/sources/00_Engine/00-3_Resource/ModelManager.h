/*============================================================
*	@file	 : ModelManager.h
*	@brief	 : テクスチャ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/07/30
*============================================================*/
#pragma once

#include "Model.h"
#include "GraphicsTypes.h"
#include <d3d11.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <wrl/client.h>

/*--------------------------------------------------
	前方宣言
----------------------------------------------------*/
struct aiMesh;

/*============================================================
*	@class	: ModelManager
*	@brief	: モデルのロード・管理
*============================================================*/
class ModelManager final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static ModelManager& getInstance() {
		static ModelManager  instance;
		return instance;
	}

private:
	ModelManager() = default;
	ModelManager(const ModelManager&) = delete;

	ModelManager& operator=(const ModelManager&) = delete;
	ModelManager(ModelManager&&) = delete;

	ModelManager& operator=(ModelManager&&) = delete;
	~ModelManager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// モデルコンテナ
	std::unordered_map <std::string, std::unique_ptr<Model>> mModels{};

public:
	// ロード
	Model* Load(const char* modelPath);

	// クリア
	void Clear() {
		mModels.clear();
	}
};