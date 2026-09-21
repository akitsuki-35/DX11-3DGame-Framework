/*============================================================
*	@file	 : Result.cpp
*	@brief	 : リザルトシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/09/16
*============================================================*/
#include "Result.h"

void Result::Initialize()
{
	_mGameObjects.clear();
}

void Result::Finalize()
{
	Scene::Finalize();
}

void Result::Update(double deltaTime)
{
	Scene::Update(deltaTime);
}

void Result::Draw() const
{
	Scene::Draw();
}