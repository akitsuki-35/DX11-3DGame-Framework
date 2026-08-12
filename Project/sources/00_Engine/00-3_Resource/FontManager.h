/*============================================================
*	@file	 : FontManager.h
*	@brief	 : フォント管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/11
*	@updated : 2026/08/11
*============================================================*/
#pragma once

#include "FontLoader.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <d3d11.h>
#include <dwrite.h>
#include <wrl/client.h>

// 文字テクスチャデータ
struct Glyph
{
	std::shared_ptr<class Texture> Texture{ nullptr };

    int BearingX = 0;   // 左側の余白
    int BearingY = 0;   // 上側の余白
    int Advance = 0;   // 次の文字までの移動量
};

/*============================================================
*	@class	: FontManager
*	@brief	: テクスチャのロード・管理
*============================================================*/
class FontManager final
{
	friend class FontLoader;

/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static FontManager& getInstance() {
		static FontManager  instance;
		return instance;
	}

private:
	FontManager() = default;
	FontManager(const FontManager&) = delete;

	FontManager& operator=(const FontManager&) = delete;
	FontManager(FontManager&&) = delete;

	FontManager& operator=(FontManager&&) = delete;
	~FontManager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// フォントコンテナ
	std::unordered_map <std::string, std::unique_ptr<Font>> mFonts{};

	// Glyphキャッシュ
	std::unordered_map<Font*, std::unordered_map<uint32_t, std::unique_ptr<Glyph>>> mAtlas{};

	// DirectWriteファクトリ
	Microsoft::WRL::ComPtr<IDWriteFactory> _mFactory{ nullptr };

public:
	void Initialize(IDWriteFactory* factory) {
		_mFactory = factory;
	}

	// フォント取得
	Font* GetFont(const std::string& keyName);
	
	// 文字テクスチャ取得
	Glyph* GetGlyph(Font* font, uint32_t codePoint);

	// フォント登録
	Font* Register(const std::string& keyName, const char* fontPath);

	// クリア
	void Clear()
	{
		mFonts.clear();
		mAtlas.clear();
	}

private:
	// 文字テクスチャ生成
	bool generateGlyph(Glyph& glyph, Font* font, uint32_t codepPoint);
};

namespace FontSet {
	inline void initialize() {
		FontManager::getInstance().Register("MPLUS_Regular", "assets\\fonts\\MPLUS1-Regular.ttf");
		FontManager::getInstance().Register("MPLUS_Bold", "assets\\fonts\\MPLUS1-Bold.ttf");
	}
}