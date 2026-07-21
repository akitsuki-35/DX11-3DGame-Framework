/*============================================================
*	@file	 : GameObject.h
*	@brief	 : 3Dゲームオブジェクト基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/12
*	@updated : 2026/07/21
*============================================================*/
#pragma once

#include "vector3.h"
#include "Component.h"
#include "Transform.h"
#include <sstream>
#include <DirectXMath.h>

/*============================================================
*	@class	: GameObject
*	@brief	: ゲームオブジェクト基底クラス
*============================================================*/
class GameObject
{
protected: // 継承先からアクセス可能なメンバ変数

	int mLayer{ 1 }; // レイヤー番号
	float mCameraZ{}; // カメラからの距離（Zソート用）

	// トランスフォーム
	Transform mTransform{};

	// コンポーネント
	std::list<Component*> mComponents;

	std::string mTag{};
	bool mIsDestroy{ false };

public:
	GameObject() = default;
	//GameObject(const Vector3& position, const Vector3& rotation, const Vector3& scale, const std::string& tag, bool isDestroy = true) 
	//	: mPosition(position), mRotation(rotation), mScale(scale), mTag(tag), mIsDestroy(isDestroy) {}

	//GameObject(const Vector3& position, const Vector3& rotation, const Vector3& scale, const std::string& tag, bool isDestroy = true)
	//	: mPosition(position), mRotation(rotation), mScale(scale), mTag(tag), mIsDestroy(isDestroy) {}

	virtual ~GameObject() = default;

	void SetDestroy() { mIsDestroy = true; }
	bool Destroy() {
		if (mIsDestroy) {
			Finalize();
			delete this;
			return true;
		}
		else {
			return false;
		}
	}

	virtual void Initialize() = 0;
	virtual void Finalize() {
		for (Component* component : mComponents) {
			component->Finalize();
			delete component;
		}
	}
	virtual void Update() {
		for (Component* component : mComponents) {
			component->Update();
		}
	}
	virtual void Draw() const {
		for (Component* component : mComponents) {
			component->Draw();
		}
	}

	template <typename T> // テンプレート関数
	T* AddComponent(GameObject* object) {
		T* component = new T(object);
		component->Initialize();
		mComponents.push_back(component);

		return component;
	}

	// ゲッター
	const int& GetLayer() const { return mLayer; }
	const float& GetCameraZ() const { return mCameraZ; }
	const Transform& GetTransform() const { return mTransform; }

	// Z値計算
	void CalcCameraZ(Vector3 cameraPosition, Vector3 cameraForward) {
		Vector3 dir = mTransform.GetPosition() - cameraPosition;
		mCameraZ = Vector3::dot(dir, cameraForward);
	}

	virtual Vector3 GetForward() const {
		Vector3 rotation = mTransform.GetRotation();
		DirectX::XMMATRIX r = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

		Vector3 forward;
		XMStoreFloat3((XMFLOAT3*)&forward, r.r[2]);
		return forward;
	}

	virtual Vector3 GetRight() const {
		Vector3 rotation = mTransform.GetRotation();
		DirectX::XMMATRIX r = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

		Vector3 forward;
		XMStoreFloat3((XMFLOAT3*)&forward, r.r[0]);
		return forward;
	}

	const std::string& GetTag() const { return mTag; }
};