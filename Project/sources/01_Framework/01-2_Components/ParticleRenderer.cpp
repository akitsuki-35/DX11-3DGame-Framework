/*============================================================
*	@file	 : ParticleRenderer.cpp
*	@brief	 : パーティクル描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#include "ParticleRenderer.h"
#include "BufferManager.h"
#include "DeviceManager.h"
#include "D3D11Config.h"
#include "Texture.h"
#include "Elements.h"

//void ParticleRenderer::Draw() const
//{
//	Renderer::Begin();
//
//	Bind();
//
//	D3D11::BufferManager::getInstance().SetWorldMatrix(getWorldMatrix());
//
//	// マテリアル設定
//	Element::MATERIAL material{};
//	material.Diffuse = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
//	material.TextureEnable = static_cast<bool>(_mTexture != nullptr);
//	D3D11::BufferManager::getInstance().SetMaterial(material);
//
//	mMesh.Bind();
//
//	if (material.TextureEnable) {
//		_mTexture->Bind();
//	}
//
//	mMesh.Draw();
//
//	Renderer::End();
//}