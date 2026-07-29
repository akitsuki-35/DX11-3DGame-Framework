/*============================================================
*	@file	 : BillboardDrawable.h
*	@brief	 : 板ポリゴン描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/07/27
*============================================================*/
#pragma once

#include "Drawable.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"

/*============================================================
*	@class	: BillboardDrawable
*	@brief	: 板ポリゴン描画
*============================================================*/
class BillboardDrawable final : public Drawable
{
public:
	BillboardDrawable(GameObject* owner)
		: Drawable(owner) {
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::Alpha;
	};

	~BillboardDrawable() override = default;

private:
	// ワールド行列取得
	DirectX::XMMATRIX GetWorldMatrix() const override {
		Camera* camera = Game::GetGameObject<Camera>();
		return _mOwner->GetTransform().GetBillboardMatrix(camera->GetViewMatrix());
	}

};