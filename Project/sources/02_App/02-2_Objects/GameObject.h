/*============================================================
*	@file	 : GameObject.h
*	@brief	 : 3Dゲームオブジェクト基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/12
*	@updated : 2026/07/21
*============================================================*/
#pragma once

#include "Vector3.h"
#include "Component.h"
#include "Transform.h"
#include <sstream>
#include <memory>
#include <DirectXMath.h>

/*============================================================
*	@class	: GameObject
*	@brief	: ゲームオブジェクト基底クラス
*============================================================*/
class GameObject
{
protected:

	int mLayer{ 1 }; // レイヤー番号
	float mCameraZ{}; // カメラからの距離（Zソート用）

	// トランスフォーム
	Transform mTransform{};

	// コンポーネント
	std::vector<Component*> mComponents;

	std::string mTag{};

	// 削除フラグ
	bool mIsDestroy{ false };

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	void SetDestroy() { mIsDestroy = true; }
	bool Destroy() {
		if (mIsDestroy) {
			// 削除フラグがオンなら削除
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
	const Vector3& GetPosition() const { return mTransform.GetPosition(); }
	const Vector3& GetRotation() const { return mTransform.GetRotation(); }
	const Vector3& GetScale() const { return mTransform.GetScale(); }

	// セッター
	GameObject& SetPosition(const Vector3& position) {
		mTransform.SetPosition(position);
		return *this;
	}

	GameObject& SetRotation(const Vector3& rotation) {
		mTransform.SetRotation(rotation);
		return *this;
	}

	GameObject& SetScale(const Vector3& scale) {
		mTransform.SetScale(scale);
		return *this;
	}

	// Z値計算
	void CalcCameraZ(Vector3 cameraPosition, Vector3 cameraForward) {
		Vector3 dir = mTransform.GetPosition() - cameraPosition;
		mCameraZ = Vector3::Dot(dir, cameraForward);
	}

	const std::string& GetTag() const { return mTag; }
};