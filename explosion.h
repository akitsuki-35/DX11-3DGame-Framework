/*============================================================
*	@file	 : explosion.h
*	@brief	 : 爆発エフェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/09
*	@updated : 2026/06/09
*============================================================*/
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"
#include "animation.h"

/*============================================================
*	@class	: Explosion
*	@brief	: 爆発エフェクト描画
*============================================================*/
class Explosion : public GameObject
{
private:
	Animation* pExplosion{ nullptr };
	//static constexpr int PATTERN_X{ 4 };
	//static constexpr int PATTERN_Y{ 4 };
	//int patternMax{ PATTERN_X * PATTERN_Y };
	int frame{};

	ID3D11Buffer* pVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* pVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* pVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* pPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* pTexture{}; // テクスチャ

public:
	Explosion() = default;
	Explosion(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // EXPLOSION_H