/*============================================================
*	@file	 : ModelDrawable.h
*	@brief	 : モデル描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/31
*	@updated : 2026/07/31
*============================================================*/
#pragma once

#include "Drawable.h"
#include "ModelManager.h"
#include "GameObject.h"

/*============================================================
*	@class	: ModelDrawable
*	@brief	: モデル描画
*============================================================*/
class ModelDrawable : public Drawable
{
private:
	Model* _mModel{};

public:
	ModelDrawable(GameObject* owner)
		: Drawable(owner) {
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::World;
	};

	~ModelDrawable() override = default;

	void Draw() const override;

private:
	// ワールド行列取得
	DirectX::XMMATRIX GetWorldMatrix() const override {
		return _mOwner->GetTransform().GetWorldMatrix();
	}

public:
	// モデル読み込み
	void LoadModel(const char* fileName) {
		_mModel = ModelManager::getInstance().Load(fileName);
	}
};