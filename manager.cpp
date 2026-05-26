/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	マネージャー[manager.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/21
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "field.h"
#include "polygon2d.h"
#include "player.h"
#include "enemy.h"

std::list<GameObject*> Manager::gameObjects;

/*----------------------------------------------------------------------------------------------------------
	初期化
----------------------------------------------------------------------------------------------------------*/
void Manager::Init()
{
	Renderer::Init();
	Input::Init();

	AddGameObject<Camera>();

	AddGameObject<Field>();
	//gameObjects.push_back(new Field(L"Resources\\Textures\\glass.jpg"));
	//gameObjects.back()->Initialize();

	AddGameObject<Player>();
	//AddGameObject<Enemy>()->SetPosition({ 5.0f, 0.0f, 5.0f });
	//AddGameObject<Enemy>()->SetPosition({-5.0f, 0.0f, 5.0f });
	//AddGameObject<Enemy>()->SetPosition({ 0.0f, 0.0f, 5.0f });

	AddGameObject<Polygon2D>();

	//gameObjects.push_back(new Polygon2D(L"Resources\\Textures\\rock.jpg"));
	//gameObjects.back()->Initialize();
}

/*----------------------------------------------------------------------------------------------------------
	終了
----------------------------------------------------------------------------------------------------------*/
void Manager::Uninit()
{
	for (GameObject* obj : gameObjects) {
		obj->Finalize();
		delete obj;
	}

	Input::Uninit();
	Renderer::Uninit();
}

/*----------------------------------------------------------------------------------------------------------
	更新
----------------------------------------------------------------------------------------------------------*/
void Manager::Update()
{
	Input::Update();

	for (GameObject* obj : gameObjects) {
		obj->Update();
	}
}

/*----------------------------------------------------------------------------------------------------------
	描画
----------------------------------------------------------------------------------------------------------*/
void Manager::Draw()
{
	Renderer::Begin();

	for (GameObject* obj : gameObjects) {
		obj->Draw();
	}

	Renderer::End();
}