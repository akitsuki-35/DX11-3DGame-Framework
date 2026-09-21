/*============================================================
*	@file	 : GameObject.h
*	@brief	 : 3Dゲームオブジェクト基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/12
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "Vector3.h"
#include "Component.h"
#include "Transform.h"
#include <string>
#include <memory>
#include <vector>
#include <DirectXMath.h>

/*============================================================
*	@class	: GameObject
*	@brief	: ゲームオブジェクト基底クラス
*============================================================*/
class GameObject
{
protected:
	// トランスフォーム
	Transform mTransform{};

	// コンポーネント
	std::vector<std::unique_ptr<Component>> mComponents{};

	// タグ
	std::string mTag{};

	// 削除フラグ
	bool mDestroy{ false };

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Initialize() = 0;
	virtual void Finalize();
	virtual void Update(double deltaTime);
	virtual void Draw() const;

	// 削除処理
	bool Destroy();

	// ゲッター
	const Transform& GetTransform() const { return mTransform; }
	const Vector3& GetPosition() const { return mTransform.GetPosition(); }
	const Vector3& GetRotation() const { return mTransform.GetRotation(); }
	const Vector3& GetScale() const { return mTransform.GetScale(); }
	const std::string& GetTag() const { return mTag; }
	virtual const bool IsDestroy() const { return mDestroy; }

	// セッター
	GameObject& SetPosition(const Vector3& position);
	GameObject& SetRotation(const Vector3& rotation);
	GameObject& SetScale(const Vector3& scale);
	GameObject& SetTag(const std::string& tag);
	void SetDestroy() { mDestroy = true; }
	
	/*------------------------------------------------------------
		テンプレート関数
	------------------------------------------------------------*/
	// コンポーネント追加
	template <typename T>
	T* AddComponent(GameObject* object) {
		auto component = std::make_unique<T>(object);
		T* ptr = component.get();

		mComponents.push_back(std::move(component));
		ptr->Initialize();

		return ptr;
	}

	// コンポーネント取得
	template <typename T>
	T* GetComponent() const {
		for (const auto& component : mComponents) {
			T* find = dynamic_cast<T*>(component.get());
			if (find) return find;
		}
		return nullptr;
	}
};