/*============================================================
*	@file	 : field.cpp
*	@brief	 : 3Dポリゴン表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/06/09
*============================================================*/
#include "Main.h"
#include "Field.h"
#include "Renderer.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "Audio.h"

#include "GraphicsTypes.h"
#include "DirectX11Config.h"

void Field::Initialize()
{
	mLayer = 1;

	mMesh.CreatePlane();
	mTransform.SetScale({ 30.0f, 30.0f, 30.0f });

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
	//_mVertexBuffer->Release();

	GameObject::Finalize();
}

void Field::Update()
{
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

	// マトリクス設定
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

	// 描画
	mMesh.Bind();
	mMesh.Draw();

	GameObject::Draw();
}