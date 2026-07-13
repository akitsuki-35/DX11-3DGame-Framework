/*============================================================
*	@file	 : result.h
*	@brief	 : リザルトシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/06/23
*============================================================*/
#ifndef RESULT_H
#define RESULT_H

#include "scene.h"
#include "gameobject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*============================================================
*	@class	: Result
*	@brief	: リザルトシーン（Sceneを継承）
*============================================================*/
class Result : public Scene
{
private:
	double accumulatedTime{ 0.0 };
	double keyInputTime{};
	Texture* pTexture{ nullptr };
	static std::list<GameObject*> resultObjects;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double elapsedTime) override;
	void Draw() const override;

	template <typename T> // テンプレート関数
	static T* AddResultObject() {
		T* ResultObject = new T();
		ResultObject->Initialize();
		resultObjects.push_back(ResultObject);

		return ResultObject;
	}

	template <typename T> // テンプレート関数
	static T* GetResultObject() {
		for (GameObject* ResultObject : resultObjects) {
			// RTTI（実行時型情報）
			T* find = dynamic_cast<T*>(ResultObject);
			if (find) return find;
		}
		return nullptr;
	}

	template <typename T>
	static std::vector<T*> GetResultObjects() {
		std::vector<T*> objects;
		for (GameObject* ResultObject : resultObjects) {
			// RTTI（実行時型情報）
			T* find = dynamic_cast<T*>(ResultObject);
			if (find != nullptr) {
				objects.push_back(find);
			}
		}
		return objects;
	}
};

#endif //  RESULT_H