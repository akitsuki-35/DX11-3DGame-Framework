/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	スプライト描画[sprite.h]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/01
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef SPRITE_H
#define SPRITE_H

#include <DirectXMath.h>

class Texture;
class SpriteSheet;

void SpriteInitialize();
void SpriteFinalize();

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	スプライト描画関数
	サイズ指定方式でオーバーロード関数化
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*----------------------------------------------------------------------------------------------------------
	通常スプライト描画

	引数：
	テクスチャ, 左上座標, サイズ, カラー
	テクスチャ, 左上座標, 拡大率, カラー
----------------------------------------------------------------------------------------------------------*/
// 数値で直接サイズ指定
void SpriteDraw(Texture* pTexture, const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size, 
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

// 拡大率でサイズ指定
void SpriteDraw(Texture* pTexture, const DirectX::XMFLOAT2& position, const float& scale = 1.0f,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

/*----------------------------------------------------------------------------------------------------------
	スプライトシート描画
	0を始点としたx, y番号でパターン指定

	引数：
	テクスチャ, 左上座標, パターン番号(x, y), サイズ, カラー
	テクスチャ, 左上座標, パターン番号(x, y), 拡大率, カラー
----------------------------------------------------------------------------------------------------------*/
// 数値で直接サイズ指定
void SpriteDraw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
	const DirectX::XMUINT2& patternNum, DirectX::XMFLOAT2 size,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

// 拡大率でサイズ指定
void SpriteDraw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
	const DirectX::XMUINT2& patternNum, const float& scale = 1.0f,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

/*----------------------------------------------------------------------------------------------------------
	スプライトシート描画
	0を始点としたパターン番号でパターン指定

	引数：
	テクスチャ, 左上座標, パターン番号, サイズ, カラー
	テクスチャ, 左上座標, パターン番号, 拡大率, カラー
----------------------------------------------------------------------------------------------------------*/
// 数値で直接サイズ指定
void SpriteDraw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
	const int& patternNum, DirectX::XMFLOAT2 size,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

// 拡大率でサイズ指定
void SpriteDraw(SpriteSheet* pSpriteSheet, const DirectX::XMFLOAT2& position,
	const int& patternNum, const float& scale = 1.0f,
	const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f });

#endif // SPRITE_H
