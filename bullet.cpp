/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	弾[bullet.cpp]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/06/02
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "main.h"
#include "manager.h"
#include "bullet.h"
#include "input.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "enemy.h"

void Bullet::Initialize()
{
	position = { 0.0f, 0.0f, 0.0f };
	velocity = { 0.0f, 0.0f, 0.0f };
	accel = { 0.0f, 0.0f, 0.0f };

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->Load("Resources\\Models\\bullet.obj");

	// シェーダー読込
	Renderer::CreateVertexShader(&pVertexShader, &pVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&pPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");
}

void Bullet::Finalize()
{
	pPixelShader->Release();
	pVertexShader->Release();
	pVertexLayout->Release();

	GameObject::Finalize();
}

void Bullet::Update()
{
	float dt = 1.0f / 60.0f;

	position += velocity * dt;

	// 敵との衝突判定
	auto enemys = Manager::GetGameObjects<Enemy>();
	for (auto enemy : enemys) {
		Vector3 dir = enemy->GetPosition() - position;
		float length = dir.Length();

		if (length < 1.0f) {
			enemy->SetDestroy();
			SetDestroy();
			break;
		}
	}


	lifeTime -= dt;
	if (lifeTime <= 0.0f) {
		// 一定時間経過で弾を削除
		SetDestroy();
	}

	GameObject::Update();
}

void Bullet::Draw() const
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(pVertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(pVertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(pPixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX w, s, r, t;
	s = XMMatrixScaling(scale.x, scale.y, scale.z); // 拡大縮小
	r = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); // 回転
	t = XMMatrixTranslation(position.x, position.y, position.z); // 平行移動
	w = s * r * t;
	Renderer::SetWorldMatrix(w);

	GameObject::Draw(); // 継承元のDrawを呼び出す
}