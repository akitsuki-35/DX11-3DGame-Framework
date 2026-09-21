/*============================================================
*	@file	 : Game.cpp
*	@brief	 : ゲームシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/28
*	@updated : 2026/09/16
*============================================================*/
#include "Game.h"

// オブジェクト群
#include "GameCamera.h"
#include "Wave.h"
#include "Player.h"
#include "Bullet.h"
#include "Sky.h"

void Game::Initialize()
{
	// 配列を初期化
	_mGameObjects.clear();

	// カメラ
	AddGameObject<GameCamera>();

	// スカイドーム
	AddGameObject<Sky>();

	// フィールド
	AddGameObject<Wave>()->SetPosition({ 0.0f, 0.0f, 0.0f });

	// オブジェクト
	AddGameObject<Player>();
}

void Game::Finalize()
{
	Scene::Finalize();
}

void Game::Update(double deltaTime)
{
	// スロー中は通常の半分の時間で更新
	if (mSlow) {
		deltaTime *= 0.5;
	}

	Scene::Update(deltaTime);
}

void Game::Draw() const
{
	Scene::Draw();
}