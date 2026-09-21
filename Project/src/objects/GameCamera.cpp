/*============================================================
*	@file	 : Camera.cpp
*	@brief	 : カメラオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/26
*	@updated : 2026/08/06
*============================================================*/
#include "GameCamera.h"
#include "Game.h"
#include "Input.h"
#include "Player.h"
#include "BufferManager.h"
#include "Config.h"

using namespace DirectX;

void GameCamera::Initialize()
{
	mTransform.SetPosition({ 0.0f, 5.0f, -10.0f });

	mTarget = Vector3(0.0f, 0.0f, 0.0f);
}

void GameCamera::Finalize()
{
	Camera::Finalize();
}

void GameCamera::Update(double deltaTime)
{
	float dt = static_cast<float>(deltaTime);

	Player* player = Game::GetGameObject<Player>();
	Vector3 playerPos = player->GetTransform().GetPosition();

	Vector3 rotation = mTransform.GetRotation();

	if (Input::GetKeyPress(VK_LEFT)) {
		mTransform.SetRotation({ rotation.x, rotation.y -= 3.0f * dt, rotation.z });
	}
	else if (Input::GetKeyPress(VK_RIGHT)) {
		mTransform.SetRotation({ rotation.x, rotation.y += 3.0f * dt, rotation.z });
	}

	rotation = mTransform.GetRotation();

	float t = 0.1f;
	mTarget = mTarget * (1.0f - t) + (playerPos + Vector3(0.0f, 2.0f, 0.0f)) * t;
	mTransform.SetPosition(mTarget + Vector3(-sinf(rotation.y) * 10.0f, 5.0f, -cosf(rotation.y) * 10.0f));

	Camera::Update(deltaTime);
}