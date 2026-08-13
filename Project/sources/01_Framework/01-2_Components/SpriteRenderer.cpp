/*============================================================
*	@file	 : SpriteRenderer.cpp
*	@brief	 : 板ポリゴン描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/08/13
*============================================================*/
#include "SpriteRenderer.h"
#include "Texture.h"
#include "TextureManager.h"
#include "BufferManager.h"
#include "GameObject.h"

void SpriteRenderer::Draw() const
{
	Bind();

	D3D11::BufferManager::getInstance().SetWorldMatrix(GetWorldMatrix());

	// マテリアル設定
	Element::MATERIAL material{};
	material.Diffuse = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
	material.TextureEnable = static_cast<bool>(_mTexture != nullptr);
	D3D11::BufferManager::getInstance().SetMaterial(material);

	mMesh.Bind();

	if (material.TextureEnable) {
		_mTexture->Bind();
	}

	mMesh.Draw();
}

DirectX::XMMATRIX SpriteRenderer::GetWorldMatrix() const
{
	return _mOwner->GetTransform().GetWorldMatrix();
}

SpriteRenderer* SpriteRenderer::LoadTexture(const char* fileName)
{
	_mTexture = TextureManager::getInstance().Load(fileName);
	return this;
}
