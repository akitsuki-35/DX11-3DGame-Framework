/*============================================================
*	@file	 : Explosion.h
*	@brief	 : 爆発エフェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/09
*	@updated : 2026/08/06
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Explosion
*	@brief	: 爆発エフェクト描画
*============================================================*/
class Explosion : public GameObject
{
private:
	int mFrame{};
	class Texture* _mTexture{};

	ID3D11ShaderResourceView* pTexture{}; // テクスチャ

public:
	Explosion() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};