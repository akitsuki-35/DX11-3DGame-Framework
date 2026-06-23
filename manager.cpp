/*============================================================
*	@file	 : manager.cpp
*	@brief	 : マネージャー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/06/16
*============================================================*/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "scene.h"

Scene* Manager::mCurrentScene{ nullptr };
Scene* Manager::mNextScene{ nullptr };

/*------------------------------------------------------------
	初期化
------------------------------------------------------------*/
void Manager::Initialize()
{
	Renderer::Initialize();
	Input::Initialize();

	//mCurrentScene = mNextScene = new Title();
	//mCurrentScene->Initialize();

	SceneChange<Title>();
	mCurrentScene = mNextScene;
    mNextScene = nullptr;
    mCurrentScene->Initialize();
}

/*------------------------------------------------------------
	終了
------------------------------------------------------------*/
void Manager::Finalize()
{
	mCurrentScene->Finalize();
	if (mNextScene) {
		if (mCurrentScene) {
			delete mCurrentScene;
		}
		mCurrentScene = mNextScene;
		mNextScene = nullptr;
	}

	Input::Finalize();
	Renderer::Finalize();
}

/*------------------------------------------------------------
	更新
------------------------------------------------------------*/
void Manager::Update()
{
	Input::Update();

	if(mCurrentScene) mCurrentScene->Update(1.0/60.0);

	if (mNextScene != nullptr) {
		if (mCurrentScene) {
			mCurrentScene->Finalize();
			delete mCurrentScene;
		}

		mCurrentScene = mNextScene;
		mNextScene = nullptr;
		mCurrentScene->Initialize();
	}
}

/*------------------------------------------------------------
	描画
------------------------------------------------------------*/
void Manager::Draw()
{
	if(mCurrentScene) mCurrentScene->Draw();
}