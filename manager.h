/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	マネージャー[manager.h]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/21
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef MANAGER_H
#define MANAGER_H

/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	ゲーム全体の処理を管理するマネージャークラス
	インスタンスを作らず静的に関数を呼び出す

	シングルトンにできるかも
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
class GameObject;

class Manager
{
private:
	static std::list<GameObject*> gameObjects;

public:
	static void Init();
	static void Uninit();
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