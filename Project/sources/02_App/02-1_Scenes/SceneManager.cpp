/*============================================================
*	@file	 : SceneManager.cpp
*	@brief	 : シーン管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/08/04
*============================================================*/
#include "SceneManager.h"
#include "Graphics.h"
#include "Input.h"
#include "Game.h"
#include "Title.h"
#include "Scene.h"
#include "AudioPlayer.h"

/*------------------------------------------------------------
	初期化
------------------------------------------------------------*/
void SceneManager::Initialize()
{
	D3D11::Graphics::getInstance().Initialize();
	Input::Initialize();
	AudioPlayer::InitializeMaster();

	SceneChange<Game>();
	mCurrentScene = std::move(mNextScene);
	mCurrentScene->Initialize();
}

/*------------------------------------------------------------
	終了
------------------------------------------------------------*/
void SceneManager::Finalize()
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

	AudioPlayer::FinalizeMaster();
	Input::Finalize();
	D3D11::Graphics::getInstance().Finalize();
}

/*------------------------------------------------------------
	更新
------------------------------------------------------------*/
void SceneManager::Update()
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
void SceneManager::Draw()
{
	D3D11::Graphics::getInstance().Begin();

	if(mCurrentScene) mCurrentScene->Draw();

	D3D11::Graphics::getInstance().End();
}