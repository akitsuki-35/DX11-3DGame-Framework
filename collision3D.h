/*============================================================
*	@file	 : collision3D.h
*	@brief	 : 3Dコリジョンクラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/16
*	@updated : 2026/06/16
*============================================================*/
#ifndef COLLISION3D_H
#define COLLISION3D_H

#include "vector3.h"
#include "component.h"

namespace Collision3D {
	class Circle;
	class Box;
}

/*============================================================
*	@class	: Collision3DBase
*	@brief	: 3Dコリジョン基底クラス
*============================================================*/
class Cllision3DBase : public Component
{
private:
	Vector3 mPosition{};
	Vector3 mCollisionSize{};
	bool mEnable{ true };

public:
	// コリジョン移動
	virtual void Move(const Vector3& position) { mPosition = mCollisionSize; }
	// サイズのセット
	virtual void SetSize(const Vector3& collisionSize) { mCollisionSize = collisionSize; }

	// 有効・無効切り替え
	virtual void Enable() { mEnable = true; }
	virtual void Disable() { mEnable = false; }

	// ゲッター
	virtual const Vector3& GetPosition() { return mPosition; }
	virtual const Vector3& GetSize() { return mCollisionSize; }
	virtual const bool& IsEnabled() { return mEnable; }

	// 各種コリジョンとの当たり判定
	virtual bool IsOverlap(const Collision3D::Circle*) const { return false; }
	virtual bool IsOverlap(const Collision3D::Box*) const { return false; }
};

#endif // COLLISSION3D_H