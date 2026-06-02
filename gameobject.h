/*============================================================
*	@file	 : gameobject.h
*	@brief	 : 3Dゲームオブジェクト基底クラス
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/05/12
*	@Updated : 2026/06/02
*============================================================*/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "vector3.h"
#include "component.h"
#include <sstream>
#include <DirectXMath.h>

/*============================================================
*	@class	: GameObject
*	@brief	: ゲームオブジェクト基底クラス
*============================================================*/
class GameObject
{
protected: // 継承先からアクセス可能なメンバ変数
	Vector3 position{ 0.0f, 0.0f, 0.0f };
	Vector3 rotation{ 0.0f, 0.0f, 0.0f };
	Vector3 scale{ 1.0f, 1.0f, 1.0f };

	std::list<Component*> components; // コンポーネント

	std::string tag{};
	bool isDestroy{ false };

public:
	GameObject() = default;
	GameObject(const Vector3& position, const Vector3& rotation, const Vector3& scale, const std::string& tag, bool isDestroy = true) 
		: position(position), rotation(rotation), scale(scale), tag(tag), isDestroy(isDestroy) {}
	virtual ~GameObject() = default;

	void SetPosition(const Vector3& pos) { position = pos; }
	void SetDestroy() { isDestroy = true; }
	bool Destroy() {
		if (isDestroy) {
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
		for (Component* component : components) {
			component->Finalize();
			delete component;
		}
	}
	virtual void Update() {
		for (Component* component : components) {
			component->Update();
		}
	}
	virtual void Draw() const {
		for (Component* component : components) {
			component->Draw();
		}
	}

	template <typename T> // テンプレート関数
	T* AddComponent(GameObject* object) {
		T* component = new T(object);
		component->Initialize();
		components.push_back(component);

		return component;
	}

	// ゲッター
	const Vector3& GetPosition() const { return position; }
	const Vector3& GetRotation() const { return rotation; }
	const Vector3& GetScale() const { return scale; }

	virtual Vector3 GetForward() const {
		DirectX::XMMATRIX r = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

		Vector3 forward;
		XMStoreFloat3((XMFLOAT3*)&forward, r.r[2]);
		return forward;
	}

	virtual Vector3 GetRight() const {
		DirectX::XMMATRIX r = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

		Vector3 forward;
		XMStoreFloat3((XMFLOAT3*)&forward, r.r[0]);
		return forward;
	}

	const std::string& GetTag() const { return tag; }
};

#endif // GAMEOBJECT_H