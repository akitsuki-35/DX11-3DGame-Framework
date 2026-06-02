/*============================================================
*	@file	 : transform.cpp
*	@brief	 : トランスフォーム
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/05/19
*	@Updated : 2026/06/02
*============================================================*/
#include "main.h"
#include "renderer.h"
#include "transform.h"

void Transform::Initialize()
{
}

void Transform::Finalize()
{
}

void Transform::Update()
{
}

void Transform::Draw()
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
}