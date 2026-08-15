/*============================================================
*	@file	 : ParticleRenderer.cpp
*	@brief	 : パーティクル描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#include "ParticleRenderer.h"
#include "ParticleEmitter.h"
#include "BufferManager.h"
#include "DeviceManager.h"
#include "Texture.h"
#include "D3D11Config.h"
#include "Camera.h"
#include "Scene.h"

using namespace DirectX;

void ParticleRenderer::Draw() const
{
	if (!_mTexture) {
		return;
	}

	XMMATRIX world = getWorldMatrix();

	Renderer::Begin();

	D3D11::DeviceManager::getInstance().SetDepthStencilState(D3D11::RenderState::Depth::Disable);

	Bind();
	_mTexture->Bind();

	Camera* camera = Scene::GetGameObject<Camera>();
	XMMATRIX r = _mEmitter->GetTransform().createBillboardRotation(camera->GetViewMatrix());

	XMMATRIX view = camera->GetViewMatrix();

	for (int i = 0; i < _mEmitter->PARTICLE_MAX; i++) {
		if (_mEmitter->mParticles[i].mEnable) {

			// マトリクス設定
			XMMATRIX w, s, t;
			s = XMMatrixScaling(_mEmitter->mParticles[i].mScale.x, _mEmitter->mParticles[i].mScale.y,
				_mEmitter->mParticles[i].mScale.z); // 拡大縮小	
			t = XMMatrixTranslation(_mEmitter->mParticles[i].mPosition.x,
				_mEmitter->mParticles[i].mPosition.y, _mEmitter->mParticles[i].mPosition.z); // 平行移動
			w = s * r * t;

			// マテリアル設定
			Element::MATERIAL material{};
			material.Diffuse = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, _mEmitter->mParticles[i].mAlpha };
			material.TextureEnable = true;
			D3D11::BufferManager::getInstance().SetMaterial(material);

			D3D11::BufferManager::getInstance().SetWorldMatrix(w);

			// 描画
			D3D11::DeviceManager::getInstance().GetContext()->Draw(4, 0);
		}
	}

	D3D11::DeviceManager::getInstance().SetDepthStencilState(D3D11::RenderState::Depth::Enable);

	Renderer::End();
}