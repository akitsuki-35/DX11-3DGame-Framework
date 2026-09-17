/*============================================================
*	@file	 : SceneManager.cpp
*	@brief	 : シーン管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/09/16
*============================================================*/
#include "SceneManager.h"
#include "SystemTimer.h"
#include "Graphics.h"
#include "Transition.h"
#include "Input.h"
#include "Title.h"
#include "Game.h"
#include "Scene.h"
#include "AudioPlayer.h"

/*------------------------------------------------------------
	初期化
------------------------------------------------------------*/
void SceneManager::Initialize()
{
	// 各種初期化
	D3D11::Graphics::getInstance().Initialize();

	Transition::getInstance().Initialize();
	Input::Initialize();
	AudioPlayer::InitializeMaster();

	// 初期シーン設定
#if defined(DEBUG) || defined(_DEBUG)
	SceneChange<Game>();
#else
	SceneChange<Title>();
#endif

	mCurrentScene = std::move(mNextScene);
	mCurrentScene->Initialize();
}

/*------------------------------------------------------------
	終了
------------------------------------------------------------*/
void SceneManager::Finalize()
{
	if (mNextScene) {
		if (mCurrentScene) {
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
void SceneManager::Update(double deltaTime)
{
	Transition::getInstance().Update(deltaTime);
	Input::Update();

	// 現在シーン更新
	if (mCurrentScene) {
		mCurrentScene->Update(deltaTime);
	}

	// シーン遷移
	if (mNextScene) {
		if (mCurrentScene) {
			mCurrentScene->Finalize();
		}

		mCurrentScene.reset();

		mCurrentScene = std::move(mNextScene);

		mCurrentScene->Initialize();

		// ロード中の累積時間をリセット
		System::Timer::getInstance().Refresh();
	}
}

/*------------------------------------------------------------
	描画
------------------------------------------------------------*/
void SceneManager::Draw()
{
	D3D11::Graphics::getInstance().Begin();

	// 現在シーン描画
	if (mCurrentScene) {
		mCurrentScene->Draw();
	}

	// トランジションテクスチャを最後に描画
	Transition::getInstance().Draw();

	D3D11::Graphics::getInstance().End();
}