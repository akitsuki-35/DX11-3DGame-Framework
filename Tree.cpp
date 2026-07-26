/*============================================================
*	@file	 : Tree.h
*	@brief	 : 木のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/07/26
*============================================================*/
#include "Main.h"
#include "Tree.h"
#include "Renderer.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "Game.h"
#include "Camera.h"

#include "MeshTypes.h"

using namespace MeshType;

void Tree::Initialize()
{
	mLayer = 2;

	mMesh.CreatePlane(Plane::Pivot::CenterBottom, Plane::Axis::XY);
	mTransform.SetPosition({ -5.0f,0.0f, 0.0f });
	mTransform.SetScale({ 8.0f, 10.0f, 0.0f });

	// テクスチャ読込
	TexMetadata metaData;
	ScratchImage image;
	LoadFromWICFile(L"Resources\\Textures\\Background\\tree.png", WIC_FLAGS_NONE, &metaData, image);
	CreateShaderResourceView(D3D11::DeviceManager::getInstance().GetDevice().Get(),
		image.GetImages(), image.GetImageCount(), metaData, &_mTexture); 
	assert(_mTexture);

	// シェーダー読込
	mShader = ShaderLoader::getInstance().Get("Unlit");
}

void Tree::Finalize()
{
	if (_mTexture) _mTexture->Release();
}

void Tree::Update()
{
}

void Tree::Draw() const
{
	// 入力レイアウト設定
	D3D11::DeviceManager::getInstance().GetContext()->IASetInputLayout(mShader->_mLayout.Get());

	// シェーダー設定
	D3D11::DeviceManager::getInstance().GetContext()->VSSetShader(mShader->_mVertexShader.Get(), NULL, 0);
	D3D11::DeviceManager::getInstance().GetContext()->PSSetShader(mShader->_mPixelShader.Get(), NULL, 0);

	// ビルボード用マトリクス
	Camera* camera = Game::GetGameObject<Camera>();
	XMMATRIX view = camera->GetViewMatrix();
	XMMATRIX invView = XMMatrixInverse(NULL, view);
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

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
}