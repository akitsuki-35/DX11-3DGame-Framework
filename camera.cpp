/*============================================================
*	@file	 : camera.cpp
*	@brief	 : カメラ
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/26
*	@Updated : 2026/06/02
*============================================================*/
#include "main.h"
#include "manager.h"
#include "camera.h"
#include "renderer.h"
#include "input.h"
#include "player.h"

void Camera::Initialize()
{
	position = Vector3(0.0f, 5.0f, -10.0f);
	target = Vector3(0.0f, 0.0f, 0.0f);
}

void Camera::Finalize()
{
}

void Camera::Update()
{
	Player* player = Manager::GetGameObject<Player>();
	Vector3 playerPos = player->GetPosition();

	float dt = 1.0f / 60.0f;

	if (Input::GetKeyPress(VK_LEFT)) {
		rotation.y -= 3.0f * dt;
	}
	else if (Input::GetKeyPress(VK_RIGHT)) {
		rotation.y += 3.0f * dt;
	}

	float t = 0.1f;
	target = target * (1.0f - t) + (playerPos + Vector3(0.0f, 2.0f, 0.0f)) * t;
	position = target + Vector3(-sinf(rotation.y) * 10.0f, 5.0f, -cosf(rotation.y) * 10.0f);

	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	viewMatrix = XMMatrixLookAtLH(XMLoadFloat3((XMFLOAT3*)&position),
		XMLoadFloat3((XMFLOAT3*)&target), XMLoadFloat3(&up));
}

void Camera::Draw() const
{
	// プロジェクション行列設定
	XMMATRIX projection = XMMatrixPerspectiveFovLH(1.0f,
		static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 1.0f, 1000.0f);
	Renderer::SetProjectionMatrix(projection);

	// ビュー行列設定
	Renderer::SetViewMatrix(viewMatrix);
}

void TopCamera::Initialize()
{
	position = Vector3(0.0f, 10.0f, 0.0f);
	target = Vector3(0.0f, 0.0f, 0.0f);
}

void TopCamera::Update()
{
	Player* player = Manager::GetGameObject<Player>();
	Vector3 playerPos = player->GetPosition();
	Vector3 playerForward = player->GetForward();

	target = { playerPos.x, playerPos.y, playerPos.z };
	position = playerPos + Vector3(0.0f, 10.0f, 1.0f);
}