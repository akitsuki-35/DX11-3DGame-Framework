/*============================================================
*	@file	 : ParticleEmitter.cpp
*	@brief	 : パーティクルエミッタ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/18
*	@updated : 2026/06/18
*============================================================*/
#include "ParticleEmitter.h"
#include "ParticleRenderer.h"
#include "Texture.h"
#include "MeshTypes.h"
#include "Input.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "D3D11Config.h"
#include "Camera.h"
#include "Scene.h"

using namespace MeshType;
using namespace DirectX;

void ParticleEmitter::Initialize()
{
	ParticleRenderer* renderer = AddComponent<ParticleRenderer>(this);

	renderer->GetMesh().CreatePlane(Plane::Pivot::Center, Plane::Axis::XY);

	renderer->LoadTexture("assets\\textures\\particle.png")->LoadShader("Unlit")
		->SetBlendState(Blend::Add)->SetLayer(Layer::Alpha);

	// 構造体初期化
	mParticles.resize(PARTICLE_MAX);
	for (int i = 0; i < PARTICLE_MAX; i++) {
		mParticles[i].mEnable = false;
	}
}

void ParticleEmitter::Finalize()
{
	GameObject::Finalize();
}

void ParticleEmitter::Update()
{
	float dt = 1.0f / 60.0f;
	Vector3 gravity{ 0.0f, -9.8f, 0.0f };

	int count = 100;

	if (Input::GetKeyTrigger(VK_SPACE)) {
		// パーティクル発射
		for (int i = 0; i < PARTICLE_MAX; i++) {
			if (!mParticles[i].mEnable) {
				mParticles[i].mEnable = true;
				mParticles[i].mLife = 60;
				mParticles[i].mPosition = mTransform.GetPosition();
				mParticles[i].mVelocity = { ((float)rand() / RAND_MAX - 0.5f) * 20.0f,
					((float)rand() / RAND_MAX) * 20.0f,
					((float)rand() / RAND_MAX - 0.5f) * 20.0f };

				float scale = ((float)rand() / RAND_MAX - 0.5f) * 5.0f;

				mParticles[i].mScale = { scale, scale, scale };

				count--;
				if (count <= 0) {
					break;
				}
			}
		}
	}

	// パーティクル更新
	for (int i = 0; i < PARTICLE_MAX; i++) {
		mParticles[i].update(dt);
	}
}

void ParticleEmitter::Draw() const
{
	auto renderer = this->GetComponent<ParticleRenderer>();

	if (!renderer || !renderer->GetTexture()) {
		return;
	}

	XMMATRIX world = renderer->getWorldMatrix();

	renderer->Begin();

	D3D11::DeviceManager::getInstance().SetDepthStencilState(D3D11::RenderState::Depth::Disable);

	renderer->Bind();
	renderer->GetTexture()->Bind();

	Camera* camera = Scene::GetGameObject<Camera>();
	XMMATRIX r = mTransform.createBillboardRotation(camera->GetViewMatrix());

	XMMATRIX view = camera->GetViewMatrix();

	GameObject::Draw();

	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (mParticles[i].mEnable) {

			// マトリクス設定
			XMMATRIX w, s, t;
			s = XMMatrixScaling(mParticles[i].mScale.x, mParticles[i].mScale.y,
				mParticles[i].mScale.z); // 拡大縮小	
			t = XMMatrixTranslation(mParticles[i].mPosition.x,
				mParticles[i].mPosition.y, mParticles[i].mPosition.z); // 平行移動
			w = s * r * t;

			// マテリアル設定
			Element::MATERIAL material{};
			material.Diffuse = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, mParticles[i].mAlpha };
			material.TextureEnable = true;
			D3D11::BufferManager::getInstance().SetMaterial(material);
			
			D3D11::BufferManager::getInstance().SetWorldMatrix(w);

			// 描画
			D3D11::DeviceManager::getInstance().GetContext()->Draw(4, 0);
		}
	}

	D3D11::DeviceManager::getInstance().SetDepthStencilState(D3D11::RenderState::Depth::Enable);

	renderer->End();
}