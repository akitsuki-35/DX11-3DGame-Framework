/*============================================================
*	@file	 : BillboardRenderer.h
*	@brief	 : ビルボード描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "SpriteRenderer.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*============================================================
*	@class	: BillboardRenderer
*	@brief	: ビルボード描画コンポーネント
*============================================================*/
class BillboardRenderer : public SpriteRenderer
{
	friend class ParticleEmitter;

protected:
	// メッシュ
	Mesh mMesh{};

	// マテリアル
	Element::MATERIAL mMaterial{};

public:
	BillboardRenderer(GameObject* owner)
		: SpriteRenderer(owner) {
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::Alpha;
	};

	~BillboardRenderer() override = default;

	void Finalize() override {
		_mTexture = nullptr;
		SpriteRenderer::Finalize();
	}

protected:
	// ワールド行列取得
	DirectX::XMMATRIX getWorldMatrix() const override;
};