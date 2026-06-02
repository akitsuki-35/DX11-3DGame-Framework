/*============================================================
*	@file	 : game.cpp
*	@brief	 : ゲームシーン
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/03/28
*	@Updated : 2026/06/02
*============================================================*/
#include "game.h"
#include "audio.h"
#include "keylogger.h"
#include "fade.h"

#include "debug_memoryleak.h"

void Game::Initialize()
{
	Fade::GetInstance().Start(1.0, true);
}

void Game::Finalize()
{
}

void Game::Update(double elapsed_time)
{
}

void Game::Draw() const
{
}