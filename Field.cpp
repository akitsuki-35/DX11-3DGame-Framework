/*============================================================
*	@file	 : field.cpp
*	@brief	 : 3Dポリゴン表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/06/09
*============================================================*/
#include "main.h"
#include "field.h"
#include "renderer.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "keylogger.h"
#include "audio.h"

#include "GraphicsTypes.h"

void Field::Initialize()
{
	mLayer = 1;

	Element::VERTEX3D vertex[4]{};

	vertex[0].Position = XMFLOAT3(-30.0f, 0.0f, 30.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(30.0f, 0.0f, 30.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-30.0f, 0.0f, -30.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(30.0f, 0.0f, -30.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Element::VERTEX3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	D3D11::DeviceManager::getInstance().GetDevice()->CreateBuffer(&bd, &sd, &_mVertexBuffer);

	// テクスチャ読込
	TexMetadata metaData;
	ScratchImage image;
	LoadFromWICFile(L"Resources\\Textures\\glass.jpg", WIC_FLAGS_NONE, &metaData, image);
	CreateShaderResourceView(D3D11::DeviceManager::getInstance().GetDevice().Get(),
		image.GetImages(), image.GetImageCount(), metaData, &_mTexture);
	assert(_mTexture);

	// シェーダー読込
	Renderer::getInstance().CreateVertexShader(&_mVertexShader, &_mVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::getInstance().CreatePixelShader(&_mPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");

	Audio* bgm = AddComponent<Audio>(this);
	bgm->Load("Resources\\Audios\\bgm.wav");
	bgm->Play(true);
}

void Field::Finalize()
{
	if (_mTexture) _mTexture->Release();

	_mPixelShader->Release();
	_mVertexShader->Release();
	_mVertexLayout->Release();
	_mVertexBuffer->Release();

	GameObject::Finalize();
}

void Field::Update()
{
	//if (KeyLogger::IsPressd(KK_A)) {
	//	mScale.x -= 10.0f;
	//}
	//if (KeyLogger::IsPressd(KK_D)) {
	//	mScale.x += 10.0f;
	//}

	GameObject::Update();
}

void Field::Draw() const
{
	// 入力レイアウト設定
	D3D11::DeviceManager::getInstance().GetContext()->IASetInputLayout(_mVertexLayout);

	// シェーダー設定
	D3D11::DeviceManager::getInstance().GetContext()->VSSetShader(_mVertexShader, NULL, 0);
	D3D11::DeviceManager::getInstance().GetContext()->PSSetShader(_mPixelShader, NULL, 0);

	assert(_mVertexLayout);   // null ならレイアウト未生成
	assert(_mVertexShader);   // null なら VS 未生成
	assert(_mPixelShader);    // null なら PS 未生成
	assert(_mVertexBuffer);   // null なら VB 未生成

	// マトリクス設定
	//XMMATRIX w, s, r, t;
	//s = XMMatrixScaling(mScale.x, mScale.y, mScale.z); // 拡大縮小
	//r = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z); // 回転
	//t = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z); // 平行移動
	//w = s * r * t;
	D3D11::BufferManager::getInstance().SetWorldMatrix(mTransform.GetWorldMatrix());

	// マテリアル設定
	Element::MATERIAL material{};
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	if (_mTexture)material.TextureEnable = true;
	else material.TextureEnable = false;
	D3D11::BufferManager::getInstance().SetMaterial(material);

	// テクスチャ設定
	if (_mTexture) {
		D3D11::DeviceManager::getInstance().GetContext()->PSSetShaderResources(0, 1, &_mTexture);
	}

	// 頂点バッファ設定
	UINT stride = sizeof(Element::VERTEX3D);
	UINT offset = 0;
	D3D11::DeviceManager::getInstance().GetContext()->IASetVertexBuffers(0, 1, &_mVertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	D3D11::DeviceManager::getInstance().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 描画
	D3D11::DeviceManager::getInstance().GetContext()->Draw(4, 0);

	GameObject::Draw();
}