/*============================================================
*	@file	 : FontManager.h
*	@brief	 : フォント管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/11
*	@updated : 2026/08/11
*============================================================*/
#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <d3d11.h>
#include <dwrite.h>
#include <wrl/client.h>

class Texture;
struct Font;

struct Glyph
{
	//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SRV{ nullptr };  // テクスチャ
	// int Width = 0;
	// int Height = 0;

	Texture* Texture{ nullptr };

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
	std::unordered_map<uint32_t, std::unique_ptr<Glyph>> mGlyphs{};

	// DirectWriteファクトリ
	Microsoft::WRL::ComPtr <IDWriteFactory> _mFactory{ nullptr };

public:
	void Initialize(IDWriteFactory* factory) {
		_mFactory = factory;
	}

	// フォント取得
	Font* GetFont(const std::string& keyName);
	Glyph* GetGlyph(Font* font, uint32_t codePoint);

	Font* Register(const std::string& keyName, const char* fontPath);

	// クリア
	void Clear()
	{
		mFonts.clear();
		mGlyphs.clear();
	}

private:
	// フォント生成
	bool generateGlyph(Glyph& glyph, Font* font, uint32_t codepPoint);
};