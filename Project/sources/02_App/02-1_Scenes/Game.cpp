/*============================================================
*	@file	 : game.cpp
*	@brief	 : ゲームシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/28
*	@updated : 2026/06/23
*============================================================*/
#include "main.h"
#include "game.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "gameobject.h"

#include "field.h"
#include "polygon2d.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "tree.h"
#include "sky.h"
#include "box.h"

#include "particle.h"

#include "result.h"

#include "score.h"

#include "DeviceManager.h"
#include "D3D11Config.h"

std::list<GameObject*> Game::gameObjects;

void Game::Initialize()
{
	//Fade::GetInstance().Start(1.0, true);

	gameObjects.clear();

	AddGameObject<Camera>();

	//AddGameObject<Sky>();

	AddGameObject<Field>();
	AddGameObject<Player>();
	AddGameObject<Enemy>()->SetPosition({ 5.0f, 0.0f, 5.0f });
	//AddGameObject<Enemy>()->SetPosition({ -5.0f, 0.0f, 5.0f });
	//AddGameObject<Enemy>()->SetPosition({ 0.0f, 0.0f, 5.0f });
	//Box* box = AddGameObject<Box>();
	//box->SetPosition({ 0.0f, 0.0f, -5.0f });
	//box->SetScale({ 1.0f, 1.0f, 1.0f });

	AddGameObject<Tree>()->SetPosition({ -5.0f,0.0f, 5.0f });

	//AddGameObject<Particle>()->SetPosition({ 0.0f, 0.0f, 0.0f });

	//AddGameObject<Score>()->SetPosition({ 120.0f, 32.0f, 0.0f });

	//AddGameObject<Polygon2D>()->Initialize({0.0f, 0.0f}, { 100.0f, 100.0f }, L"Resources\\Textures\\rock.jpg");
}

void Game::Finalize()
{
	for (GameObject* obj : gameObjects) {
		obj->Finalize();
		delete obj;
	}

	gameObjects.clear();
}

void Game::Update(double elapsedTime)
{
	for (GameObject* obj : gameObjects) {
		obj->Update();
	}

	// ゲームオブジェクト削除
	gameObjects.remove_if([](GameObject* object) {
		return object->Destroy();
		});

	//if (Input::GetKeyTrigger(VK_RETURN)) {
	//	Manager::SceneChange<Result>();
	//}
}

void Game::Draw() const
{
	// Zソート
	{
		Camera* camera = GetGameObject<Camera>();

		if (camera) {

			Vector3 forward = camera->GetForward();
			Vector3 position = camera->GetTransform().GetPosition();

			for (GameObject* obj : gameObjects) {
				obj->CalcCameraZ(position, forward);
			}

			gameObjects.sort([](GameObject* a, GameObject* b) {
				return a->GetCameraZ() > b->GetCameraZ();
				});
		}
	}

		D3D11::DeviceManager::getInstance().SetSamplerState(D3D11::RenderState::Sampler::Anisotropic);

		for (int layer = 0; layer < 4; layer++)
		{
			for (GameObject* obj : gameObjects) {
				if (obj->GetLayer() == layer) {
					obj->Draw();
				}
			}
		}
}