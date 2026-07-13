/*============================================================
*	@file	 : texture.h
*	@brief	 : テクスチャ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/06/02
*============================================================*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>
#include <string>
#include <DirectXMath.h>

/*============================================================
*	@class	: Texture
*	@brief	: テクスチャクラス
*============================================================*/
class Texture
{
protected:
	DirectX::XMUINT2 originalSize{}; // テクスチャのオリジナルサイズ
	ID3D11ShaderResourceView* pShaderResourceView{ nullptr }; // シェーダーリソースビュー

	DirectX::XMFLOAT2 position{}; // 描画座標
	DirectX::XMFLOAT2 drawSize{}; // 描画サイズ
	float rotate{}; // 回転角
	DirectX::XMFLOAT4 color{ 1.0f, 1.0f, 1.0f, 1.0f }; // カラー

public:
	Texture(const wchar_t* pFileName, const DirectX::XMFLOAT2& position = { 0.0f, 0.0f },
		const DirectX::XMFLOAT2& size = { 0.0f, 0.0f }, const float& rotate = 0.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, bool isMipMap = true);

	virtual ~Texture();

	// 描画
	virtual void Draw();
	virtual void SetTexture();

	const DirectX::XMUINT2& GetSize() { return originalSize; }

/*------------------------------------------------------------
	セッター
------------------------------------------------------------*/
	void SetPosition(const DirectX::XMFLOAT2& newPosition) { position = newPosition; }
	void SetSize(const DirectX::XMFLOAT2& newSize) { drawSize = newSize; }
	void SetRotate(const float& newRotate) { rotate = newRotate; }
	void SetColor(const DirectX::XMFLOAT4& newColor) { color = newColor; }

	void BulkUpdate(const DirectX::XMFLOAT2& newPosition, const DirectX::XMFLOAT2& newSize,
		const float& newRotate, const DirectX::XMFLOAT4& newColor) {
		SetPosition(newPosition), SetSize(newSize), SetRotate(newRotate), SetColor(newColor);
	}
};

/*============================================================
*	@class	: SpriteSheet
*	@brief	: スプライトシートクラス（テクスチャを継承）
*============================================================*/
class SpriteSheet : public Texture
{
private:
	int patternMax{}; // パターン数
	int CurrentPattern{}; // 現在のパターン番号
	DirectX::XMUINT2 patternMatrix{}; // 縦・横のパターン数
	DirectX::XMUINT2 patternSize{}; // パターンごとのサイズ

public:
	SpriteSheet(const wchar_t* pFileName, const DirectX::XMUINT2& patternMatrix,
		const DirectX::XMFLOAT2& position = { 0.0f, 0.0f },
		const DirectX::XMFLOAT2& size = { 0.0f, 0.0f }, const float& rotate = 0.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, bool isMipMap = true);

	// 描画
	void Draw() override;

/*------------------------------------------------------------
	スプライト関係ゲッター・セッター
------------------------------------------------------------*/
	const int& GetCurrentPattern() { return CurrentPattern; }
	const int& GetPatternMax() { return patternMax; }
	const DirectX::XMUINT2& GetPatternMatrix() { return patternMatrix; }
	const DirectX::XMUINT2& GetPatternSize() { return patternSize; }

	void SetPattern(int patternNum) {
		if (patternMax < patternNum) return;
		CurrentPattern = patternNum;
	}
};

#endif // TEXTURE_H

