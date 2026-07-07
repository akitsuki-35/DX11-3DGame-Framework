/*============================================================
*	@file	 : result.cpp
*	@brief	 : リザルトシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/06/23
*============================================================*/
#include "result.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "fade.h"
#include "audio.h"
#include "direct3d.h"

#include "polygon2d.h"
#include "title.h"
#include "input.h"

#include <math.h>

std::list<GameObject*> Result::resultObjects;

void Result::Initialize()
{
	Result::resultObjects.clear();

	AddResultObject<Polygon2D>()->Initialize({ 0.0f, 0.0f }, { 1280.0f, 720.0f }, L"Resources\\Textures\\Result.png");
}

void Result::Finalize()
{}

void Result::Update(double elapsedTime)
{
	for (GameObject* obj : resultObjects) {
		obj->Update();
	}

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::SceneChange<Title>();
	}
}

void Result::Draw() const
{
	Renderer::Begin();

	for (GameObject* obj : resultObjects) {
		obj->Draw();
	}

	Renderer::End();
}