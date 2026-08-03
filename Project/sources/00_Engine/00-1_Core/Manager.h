/*============================================================
*	@file	 : Manager.h
*	@brief	 : マネージャー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/08/02
*============================================================*/
#pragma once

#include "Scene.h"
#include <memory>

/*============================================================
*	@class	: Manager
*	@brief	: ゲーム全体の処理を管理するマネージャークラス
*============================================================*/
class Manager final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static Manager& getInstance() {
		static Manager instance;
		return instance;
	}

private:
	Manager() = default;
	Manager(const Manager&) = delete;

	Manager& operator=(const Manager&) = delete;
	Manager(Manager&&) = delete;

	Manager& operator=(Manager&&) = delete;
	~Manager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	std::unique_ptr<Scene> mCurrentScene{};
	std::unique_ptr<Scene> mNextScene{};

public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	template <class T>
	void SceneChange() {
		mNextScene = std::make_unique<T>();
	}
};