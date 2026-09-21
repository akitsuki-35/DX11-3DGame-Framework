/*============================================================
*	@file	 : Title.cpp
*	@brief	 : タイトルシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/09/16
*============================================================*/
#include "Title.h"

void Title::Initialize()
{
	_mGameObjects.clear();
}

void Title::Finalize()
{
	Scene::Finalize();
}

void Title::Update(double deltaTime)
{
	Scene::Update(deltaTime);
}

void Title::Draw() const
{
	Scene::Draw();
}