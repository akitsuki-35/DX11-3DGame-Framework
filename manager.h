/*============================================================
*	@file	 : manager.h
*	@brief	 : マネージャー
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/21
*	@Updated : 2026/06/02
*============================================================*/
#ifndef MANAGER_H
#define MANAGER_H

#include "main.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class GameObject;

/*============================================================
*	@class	: Manager
*	@brief	: ゲーム全体の処理を管理するマネージャークラス
*============================================================*/
class Manager
{
private:
	static std::list<GameObject*> gameObjects;

public:
	static void Initialize();
	static void Finalize();
	static void Update();
	static void Draw();

	template <typename T> // テンプレート関数
	static T* AddGameObject() {
		T* gameObject = new T();
		gameObject->Initialize();
		gameObjects.push_back(gameObject);

		return gameObject;
	}

	template <typename T> // テンプレート関数
	static T* GetGameObject() {
		for (GameObject* gameObject : gameObjects) {
			// RTTI（実行時型情報）
			T* find = dynamic_cast<T*>(gameObject);
			if (find) return find;
		}
		return nullptr;
	}

	template <typename T>
	static std::vector<T*> GetGameObjects() {
		std::vector<T*> objects;
		for (GameObject* gameObject : gameObjects) {
			// RTTI（実行時型情報）
			T* find = dynamic_cast<T*>(gameObject);
			if (find != nullptr) {
				objects.push_back(find);
			}
		}
		return objects;
	}
};

#endif // MANAGER_H