/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	プレイヤー[player.cpp]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/05/19
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "manager.h"
#include "player.h"
#include "camera.h"
#include "bullet.h"

void Player::Initialize()
{
	position = { 0.0f, 0.0f, 0.0f };
	velocity = { 0.0f, 0.0f, 0.0f };
	accel = { 50.0f, 0.0f, 50.0f };

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->Load("Resources\\Models\\player.obj");

	// シェーダー読込
	Renderer::CreateVertexShader(&pVertexShader, &pVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&pPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");
}

void Player::Finalize()
{
	pPixelShader->Release();
	pVertexShader->Release();
	pVertexLayout->Release();

	GameObject::Finalize();
}

void Player::Update()
{
	float dt = 1.0f / 60.0f; // 経過時間
	float j = 15.0f; // ジャンプ力
	float g = 30.0f; // 重力加速度
	float r = 5.0f; // 抵抗力

	Camera* camera = Manager::GetGameObject<Camera>();
	Vector3 forward = camera->GetForward();
	Vector3 right = camera->GetRight();

	forward.y = 0.0f;
	forward.Normalize();

	right.y = 0.0f;
	right.Normalize();

	//Vector3 forward = GetForward();
	//Vector3 right = GetRight();

	// キー入力移動処理
	if (Input::GetKeyPress('D')) {
		velocity += right * 50.0f * dt;
	}
	if (Input::GetKeyPress('A')) {
		velocity -= right * 50.0f * dt;
	}
	if (Input::GetKeyPress('W')) {
		velocity += forward * 50.0f * dt;
	}
	if (Input::GetKeyPress('S')) {
		velocity -= forward * 50.0f * dt;
	}

	rotation.y = atan2f(velocity.x, velocity.z);

	// ジャンプ
	if (Input::GetKeyTrigger('K')) {
		velocity.y += j; // 撃力
	}

	// 重力加速度
	velocity.y += -g * dt;

	// 摩擦抵抗
	velocity.x += -velocity.x * r * dt;
	velocity.z += -velocity.z * r * dt;

	// 移動処理
	position += velocity * dt;

	// 地面との衝突判定
	if (position.y < 0.0f) {
		position.y = 0.0f;
		velocity.y = 0.0f;
	}

	// 弾の発射
	if (Input::GetKeyTrigger('J')) {

		Bullet* bullet = Manager::AddGameObject<Bullet>();
		bullet->SetPosition({ position.x, position.y, position.z });
		bullet->SetVelocity(GetForward() * 50.0f);
	}

	GameObject::Update();
}

void Player::Draw() const
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(pVertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(pVertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(pPixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX w, s, r, t;
	s = XMMatrixScaling(scale.x, scale.y, scale.z); // 拡大縮小
	r = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y + XM_PI, rotation.z); // 回転
	t = XMMatrixTranslation(position.x, position.y, position.z); // 平行移動
	w = s * r * t;
	Renderer::SetWorldMatrix(w);

	GameObject::Draw(); // 継承元のDrawを呼び出す
}