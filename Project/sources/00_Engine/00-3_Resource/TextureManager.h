/*============================================================
*	@file	 : TextureManager.h
*	@brief	 : テクスチャ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/07/30
*============================================================*/
#pragma once

#include "Texture.h"
#include <d3d11.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <wrl/client.h>

class TextureManager final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static TextureManager& getInstance() {
		static TextureManager  instance;
		return instance;
	}

private:
	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;

	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;

	TextureManager& operator=(TextureManager&&) = delete;
	~TextureManager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// テクスチャコンテナ
	std::unordered_map <std::string, std::unique_ptr<Texture>> mTextures{};

public:
	// ロード
	Texture* Load(const char* texturePath);

private:
	bool generateTexture(Texture& texture, const std::string& path);
};