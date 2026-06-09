/*============================================================
*	@file	 : manager.cpp
*	@brief	 : マネージャー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/06/02
*============================================================*/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"

#include "field.h"
#include "polygon2d.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "tree.h"
#include "sky.h"

std::list<GameObject*> Manager::gameObjects;

/*------------------------------------------------------------
	初期化
------------------------------------------------------------*/
void Manager::Initialize()
{
	Renderer::Initialize();
	Input::Initialize();

	AddGameObject<Camera>();

	AddGameObject<Sky>();

	AddGameObject<Field>();

	AddGameObject<Player>();
	AddGameObject<Enemy>()->SetPosition({ 5.0f, 0.0f, 5.0f });
	AddGameObject<Enemy>()->SetPosition({-5.0f, 0.0f, 5.0f });
	AddGameObject<Enemy>()->SetPosition({ 0.0f, 0.0f, 5.0f });

	AddGameObject<Tree>()->SetPosition({ -10.0f, 0.0f, 5.0f });
	AddGameObject<Tree>()->SetPosition({ -10.0f, 0.0f, -5.0f });

	AddGameObject<Polygon2D>();
}

/*------------------------------------------------------------
	終了
------------------------------------------------------------*/
void Manager::Finalize()
{
	for (GameObject* obj : gameObjects) {
		obj->Finalize();
		delete obj;
	}

	Input::Finalize();
	Renderer::Finalize();
}

/*------------------------------------------------------------
	更新
------------------------------------------------------------*/
void Manager::Update()
{
	Input::Update();

	for (GameObject* obj : gameObjects) {
		obj->Update();
	}

	// ゲームオブジェクト削除
	gameObjects.remove_if([](GameObject* object) {
		return object->Destroy();
	});
}

/*------------------------------------------------------------
	描画
------------------------------------------------------------*/
void Manager::Draw()
{
	Renderer::Begin();

	for (int layer = 0; layer < 4; layer++)
	{
		for (GameObject* obj : gameObjects) {
			if (obj->GetLayer() == layer) {
				obj->Draw();
			}
		}
	}

	Renderer::End();
}