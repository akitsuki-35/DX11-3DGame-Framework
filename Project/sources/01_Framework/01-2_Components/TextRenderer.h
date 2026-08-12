/*============================================================
*	@file	 : TextRenderer.h
*	@brief	 : テキスト描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/12
*	@updated : 2026/08/12
*============================================================*/
#pragma once

#include "UIRenderer.h"
#include "UIStyle.h"
#include "FontManager.h"
#include "Utility.h"

/*============================================================
*	@class	: UIRenderer
*	@brief	: UI描画コンポーネント
*============================================================*/
class TextRenderer : public UIRenderer
{
private:
	Font* _mFont{}; // フォント
	std::wstring mText{}; // 表示文字列
	size_t mCharsPerLine{ 30 }; // 1行あたりの文字数

public:
	TextRenderer(GameObject* owner)
		: UIRenderer(owner) {
		// 2Dレイヤーに描画
		mSortKey.layer = Layer::UI;
	};

	~TextRenderer() override = default;

	void Draw() const override;

private:
	// ワールド行列取得
	//DirectX::XMMATRIX GetWorldMatrix() const override {
	//	return _mOwner->GetTransform().GetWorldMatrix();
	//}


public:
	UIRenderer* LoadTexture(const char* fileName) = delete;

	// フォントのセット
	TextRenderer* SetFont(const std::string& fontName) {
		_mFont = FontManager::getInstance().GetFont(fontName);
		return this;
	}

	// テキスト更新
	TextRenderer* SetText(const std::string& text) {
		mText = Utility::String::toWideString(text);
		return this;
	}

	// 1行あたりの文字数更新
	TextRenderer* SetCharsPerLine(const size_t& charsPerLine) {
		mCharsPerLine = charsPerLine;
		return this;
	}
};