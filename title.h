/*============================================================
*	@file	 : title.h
*	@brief	 : タイトルシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/06/23
*============================================================*/
#ifndef TITLE_H
#define TITLE_H

#include "scene.h"
#include "gameobject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*------------------------------------------------------------
	タイトルシーンの状態
------------------------------------------------------------*/
enum TitleState
{
	TITLE_FADE_IN,
	TITLE_KEYINPUT_WAIT,
	TITLE_KEYINPUT_ACTION,
	TITLE_FADE_OUT
};

/*============================================================
*	@class	: Title
*	@brief	: タイトルシーン（Sceneを継承）
*============================================================*/
class Title : public Scene
{
private:
	TitleState state{ TitleState::TITLE_FADE_IN };
	double accumulatedTime{ 0.0 };
	double keyInputTime{};
	Texture* pTexture{ nullptr };
	static std::list<GameObject*> titleObjects;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double elapsedTime) override;
	void Draw() const override;

	template <typename T> // テンプレート関数
	static T* AddTitleObject() {
		T* TitleObject = new T();
		TitleObject->Initialize();
		titleObjects.push_back(TitleObject);

		return TitleObject;
	}

	template <typename T> // テンプレート関数
	static T* GetTitleObject() {
		for (GameObject* TitleObject : titleObjects) {
			// RTTI（実行時型情報）
			T* find = dynamic_cast<T*>(TitleObject);
			if (find) return find;
		}
		return nullptr;
	}

	template <typename T>
	static std::vector<T*> GetTitleObjects() {
		std::vector<T*> objects;
		for (GameObject* TitleObject : titleObjects) {
			// RTTI（実行時型情報）
			T* find = dynamic_cast<T*>(TitleObject);
			if (find != nullptr) {
				objects.push_back(find);
			}
		}
		return objects;
	}
};

#endif // TITLE_H