/*============================================================
*	@file	 : title.cpp
*	@brief	 : タイトルシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/06/23
*============================================================*/
#include "title.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "fade.h"
#include "audio.h"
#include "direct3d.h"

#include "polygon2d.h"
#include "game.h"
#include "input.h"

#include <math.h>

std::list<GameObject*> Title::titleObjects;

void Title::Initialize()
{
	Title::titleObjects.clear();

	AddTitleObject<Polygon2D>()->Initialize({ 0.0f, 0.0f }, { 1280.0f, 720.0f }, L"Resources\\Textures\\Title.png");
}

void Title::Finalize()
{
}

void Title::Update(double elapsedTime)
{
	for (GameObject* obj : titleObjects) {
		obj->Update();
	}

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::SceneChange<Game>();
	}
}

void Title::Draw() const
{
	Renderer::Begin();

	for (GameObject* obj : titleObjects) {
		obj->Draw();
	}

	Renderer::End();
}