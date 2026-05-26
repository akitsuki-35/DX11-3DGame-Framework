/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	エネミー[enemy.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/05/19
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "enemy.h"

void Enemy::Initialize()
{
	position = { 0.0f, 0.0f, 0.0f };
	velocity = { 0.0f, 0.0f, 0.0f };
	accel = { 0.0f, 0.0f, 0.0f };

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->Load("Resources\\Models\\player.obj");

	// シェーダー読込
	Renderer::CreateVertexShader(&pVertexShader, &pVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&pPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");
}

void Enemy::Finalize()
{
	pPixelShader->Release();
	pVertexShader->Release();
	pVertexLayout->Release();

	GameObject::Finalize();
}

void Enemy::Update()
{
	GameObject::Update();
}

void Enemy::Draw() const
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
