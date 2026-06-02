/*============================================================
*	@file	 : polygon2d.cpp
*	@brief	 : 2Dポリゴン表示
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/28
*	@Updated : 2026/06/02
*============================================================*/
#include "main.h"
#include "polygon2d.h"
#include "renderer.h"

Polygon2D::Polygon2D(const wchar_t* pFileName)
{
	// テクスチャ読込
	TexMetadata metaData;
	ScratchImage image;
	LoadFromWICFile(pFileName, WIC_FLAGS_NONE, &metaData, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metaData, &pTexture);
	assert(pTexture);
}

void Polygon2D::Initialize()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(200.0f, 0.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, 200.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(200.0f, 200.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &pVertexBuffer);

	// テクスチャ読込
	TexMetadata metaData;
	ScratchImage image;
	LoadFromWICFile(L"Resources\\Textures\\rock.jpg", WIC_FLAGS_NONE, &metaData, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metaData, &pTexture);
	assert(pTexture);

	// シェーダー読込
	Renderer::CreateVertexShader(&pVertexShader, &pVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&pPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");
}

void Polygon2D::Finalize()
{
	if(pTexture) pTexture->Release();

	pPixelShader->Release();
	pVertexShader->Release();
	pVertexLayout->Release();
	pVertexBuffer->Release();
}

void Polygon2D::Update()
{
}

void Polygon2D::Draw() const
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(pVertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(pVertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(pPixelShader, NULL, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	XMMATRIX w, s, r, t;
	s = XMMatrixScaling(1.0f, 1.0f, 1.0f); // 拡大縮小
	r = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f); // 回転
	t = XMMatrixTranslation(0.0f, 0.0f, 0.0f); // 平行移動
	w = s * r * t;
	Renderer::SetWorldMatrix(w);

	// マテリアル設定
	MATERIAL material{};
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	if(pTexture)material.TextureEnable = true;
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