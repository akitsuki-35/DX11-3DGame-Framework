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
#include "Graphics.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "scene.h"
#include "audio.h"

/*------------------------------------------------------------
	初期化
------------------------------------------------------------*/
void Manager::Initialize()
{
	D3D11::Graphics::getInstance().Initialize();
	Input::Initialize();
	Audio::InitMaster();

	SceneChange<Game>();
	mCurrentScene = std::move(mNextScene);
	mCurrentScene->Initialize();
}

/*------------------------------------------------------------
	終了
------------------------------------------------------------*/
void Manager::Finalize()
{
	if (mNextScene)
	{
		if (mCurrentScene)
		{
			mCurrentScene->Finalize();
		}

		mCurrentScene = std::move(mNextScene);

		mCurrentScene->Initialize();
	}

	Audio::UninitMaster();
	Input::Finalize();
	D3D11::Graphics::getInstance().Finalize();
}

/*------------------------------------------------------------
	更新
------------------------------------------------------------*/
void Manager::Update()
{
	Input::Update();

	if(mCurrentScene) mCurrentScene->Update(1.0/60.0);

	if (mNextScene)
	{
		if (mCurrentScene)
		{
			mCurrentScene->Finalize();
		}

		mCurrentScene.reset();

		mCurrentScene = std::move(mNextScene);

		mCurrentScene->Initialize();
	}
}

/*------------------------------------------------------------
	描画
------------------------------------------------------------*/
void Manager::Draw()
{
	D3D11::Graphics::getInstance().Begin();

	if(mCurrentScene) mCurrentScene->Draw();

	D3D11::Graphics::getInstance().End();
}