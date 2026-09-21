/*============================================================
*	@file	 : Application.h
*	@brief	 : アプリケーション内部処理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/09/20
*============================================================*/
#pragma once

#include "Scene.h"
#include <memory>

/*============================================================
*	@class	: Application
*	@brief	: アプリケーション内部処理
*============================================================*/
class Application final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static Application& getInstance() {
		static Application instance;
		return instance;
	}

private:
	Application() = default;
	Application(const Application&) = delete;

	Application& operator=(const Application&) = delete;
	Application(Application&&) = delete;

	Application& operator=(Application&&) = delete;
	~Application() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// 現在シーン
	std::unique_ptr<Scene> _mCurrentScene{};

	// 遷移先シーン
	std::unique_ptr<Scene> _mNextScene{};

public:
	void Initialize(std::unique_ptr<Scene> scene);
	void Finalize();
	void Update(double deltaTime);
	void Draw();

	// シーン遷移
	template <class T>
	void SceneChange() {
		_mNextScene = std::make_unique<T>();
	}
};