/*============================================================
*	@file	 : Transform.h
*	@brief	 : トランスフォームコンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/07/20
*============================================================*/
#pragma once

#include "Vector3.h"
#include <DirectXMath.h>

/*============================================================
*	@class	: Transform
*	@brief	: トランスフォームコンポーネント
*============================================================*/
class Transform
{
private:
	Vector3 mPosition{ 0.0f, 0.0f, 0.0f };
	Vector3 mRotation{ 0.0f, 0.0f, 0.0f };
	Vector3 mScale{ 1.0f, 1.0f, 1.0f };

	// 更新フラグ
	mutable bool mDirty{ true };

	// ワールド行列
	mutable DirectX::XMMATRIX mWorldMatrix{};

	// 子オブジェクト
	Transform* mParent{ nullptr };

public:
	Transform() = default;
	Transform(Vector3 position, Vector3 rotation = { 0.0f, 0.0f, 0.0f }, Vector3 scale = { 1.0f, 1.0f, 1.0f })
		: mPosition(position), mRotation(rotation), mScale(scale) {}

private:
	// 行列作成
	DirectX::XMMATRIX createScaleMatrix() const;
	DirectX::XMMATRIX createRotationMatrix() const;
	DirectX::XMMATRIX createTranslationMatrix() const;

	// ワールド行列を更新
	void rebuildWorldMatrix() const;
	
	// 更新フラグをオン
	void markDirty() { mDirty = true; }
	
public:
	// セッター
	// メンバ更新後、更新フラグ有効化
	void SetPosition(const Vector3& position) {
		mPosition = position;
		markDirty();
	}
	void SetRotation(const Vector3& rotation) { 
		mRotation = rotation;
		markDirty();
	}
	void SetScale(const Vector3& scale) { 
		mScale = scale;
		markDirty();
	}

	// ゲッター
	const Vector3& GetPosition() const { return mPosition; }
	const Vector3& GetRotation() const { return mRotation; }
	const Vector3& GetScale() const { return mScale; }
	const DirectX::XMMATRIX& GetWorldMatrix() const {
		// 前のワールド行列から更新されていれば更新後のワールド行列を返す
		if (mDirty) { rebuildWorldMatrix(); }
		return mWorldMatrix;
	}
};