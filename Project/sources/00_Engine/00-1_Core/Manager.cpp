/*============================================================
*	@file	 : manager.cpp
*	@brief	 : マネージャー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/06/16
*============================================================*/
#include "main.h"
#include "Manager.h"
#include "Renderer.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "scene.h"
#include "audio.h"

Scene* Manager::mCurrentScene{ nullptr };
Scene* Manager::mNextScene{ nullptr };

/*------------------------------------------------------------
	初期化
------------------------------------------------------------*/
void Manager::Initialize()
{
	Renderer::getInstance().Initialize();
	Input::Initialize();
	Audio::InitMaster();

	SceneChange<Game>();
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

	Audio::UninitMaster();
	Input::Finalize();
	Renderer::getInstance().Finalize();
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