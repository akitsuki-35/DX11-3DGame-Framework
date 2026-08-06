/*============================================================
*	@file	 : Explosion.cpp
*	@brief	 : 爆発エフェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/09
*	@updated : 2026/08/06
*============================================================*/
#include "Explosion.h"
#include "DeviceManager.h"
#include "TextureManager.h"
#include "BillboardRenderer.h"
#include "MeshTypes.h"

using namespace MeshType;

void Explosion::Initialize()
{
	mLayer = 2;

	BillboardRenderer* drawable = AddComponent<BillboardRenderer>(this);

	drawable->GetMesh().CreatePlane(Plane::Pivot::Center, Plane::Axis::XY);

	mTransform.SetPosition({ 0.0f,0.0f, 0.0f });
	mTransform.SetScale({ 1.0f, 1.0f, 0.0f });

	drawable->LoadTexture("assets\\textures\\Effects\\Explosion.png");

	drawable->LoadShader("Unlit");
}

void Explosion::Finalize()
{
	if (pTexture) pTexture->Release();
}

void Explosion::Update()
{
	mFrame++;

	if (mFrame >= 16) {
		SetDestroy();
	}
}

void Explosion::Draw() const
{
	// UV座標書き換え
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		D3D11::DeviceManager::getInstance().GetContext()->Map(pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		float tx = 1.0f / 4.0f * (frame % 4);
		float ty = 1.0f / 4.0f * (frame / 4);
		float tw = 1.0f / 4.0f;
		float th = 1.0f / 4.0f;

		vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(tx, ty);

		vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(tx + tw, ty);

		vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(tx, ty + th);

		vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(tx + tw, ty + th);

		Renderer::GetDeviceContext()->Unmap(pVertexBuffer, 0);
	}

	// ビルボード用マトリクス
	Camera* camera = Game::GetGameObject<Camera>();
	XMMATRIX view = camera->GetViewMatrix();
	XMMATRIX invView = XMMatrixInverse(NULL, view);
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	// マトリクス設定
	XMMATRIX w, s, r, t;
	s = XMMatrixScaling(mScale.x, mScale.y, mScale.z); // 拡大縮小	
	t = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z); // 平行移動
	w = s * invView * t;
	Renderer::SetWorldMatrix(w);

	// マテリアル設定
	MATERIAL material{};
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	if (pTexture)material.TextureEnable = true;
	else material.TextureEnable = false;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	if (pTexture) {
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &pTexture);
	}

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}
