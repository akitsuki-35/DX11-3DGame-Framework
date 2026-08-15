/*============================================================
*	@file	 : BillboardRenderer.h
*	@brief	 : ビルボード描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "SpriteRenderer.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*============================================================
*	@class	: BillboardRenderer
*	@brief	: 板ポリゴン描画
*============================================================*/
class BillboardRenderer final : public SpriteRenderer
{
private:
	Mesh mMesh{}; // メッシュ
	Element::MATERIAL mMaterial{}; // マテリアル
	Texture* _mTexture{ nullptr }; // テクスチャ

public:
	BillboardRenderer(GameObject* owner)
		: SpriteRenderer(owner) {
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::Alpha;
	};

	~BillboardRenderer() override = default;

	void Finalize() override {
		SpriteRenderer::Finalize();
	}

private:
	// ワールド行列取得
	DirectX::XMMATRIX getWorldMatrix() const override;
};