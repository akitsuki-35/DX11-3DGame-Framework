/*============================================================
*	@file	 : ParticleRenderer.h
*	@brief	 : パーティクル描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "BillboardRenderer.h"

/*============================================================
*	@class	: ParticleRenderer
*	@brief	: パーティクル描画コンポーネント
*============================================================*/
class ParticleRenderer : public BillboardRenderer
{
	friend class ParticleEmitter;

private:
	ParticleEmitter* _mEmitter{ nullptr };
	DirectX::XMFLOAT4 mColor{ 1.0f, 1.0f, 1.0f, 1.0f };

public:
	ParticleRenderer(GameObject* owner)
		: BillboardRenderer(owner) {
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::Alpha;
	};

	~ParticleRenderer() override = default;

	ParticleRenderer* SetEmitter(ParticleEmitter* emitter) {
		_mEmitter = emitter;
		return this;
	}

	void Draw() const override;

	void Finalize() override {
		_mTexture = nullptr;
		SpriteRenderer::Finalize();
	}
};