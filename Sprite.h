/*============================================================
*	@file	 : Sprite.h
*	@brief	 : スプライト描画
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/01
*	@updated : 2026/07/24
*============================================================*/
#pragma once

#include "DeviceManager.h"
#include <DirectXMath.h>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;
class SpriteSheet;

/*============================================================
*	@class	: Sprite
*	@brief	: スプライト描画クラス
*============================================================*/
class Sprite 
{
private:
	static constexpr int NUM_VERTEX{ 4 }; // 頂点数
	static ID3D11Buffer* pVertexBuffer; // 頂点バッファ

	Sprite() {}
	Sprite(const Sprite&);
	Sprite& operator=(const Sprite&);
	~Sprite() {};

public:
	static Sprite& GetInstance() {
		static Sprite instance;
		return instance;
	}

	const void Initialize();
	const void Finalize();

	const void Draw(Texture* pTexture, const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size,
		const float& rotate, const DirectX::XMFLOAT4& color);

	const void Draw(SpriteSheet* pSpriteSheet, const int& patternNum,
		const DirectX::XMFLOAT2& position, DirectX::XMFLOAT2 size, const float& rotate,
		const DirectX::XMFLOAT4& color);
};