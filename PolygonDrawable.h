/*============================================================
*	@file	 : PolygonDrawable.h
*	@brief	 : 板ポリゴン描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/07/27
*============================================================*/
#pragma once

#include "Drawable.h"
#include "GameObject.h"

/*============================================================
*	@class	: PolygonDrawable
*	@brief	: 板ポリゴン描画
*============================================================*/
class PolygonDrawable final : public Drawable
{
private:
	PolygonDrawable(GameObject* owner) {
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::World;
	};

	~PolygonDrawable() override = default;

	// ワールド行列取得
	DirectX::XMMATRIX GetWorldMatrix() const override {
		_mOwner->GetTransform().GetWorldMatrix();
	}

};