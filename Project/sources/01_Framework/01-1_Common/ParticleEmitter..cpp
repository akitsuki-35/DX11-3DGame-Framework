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
#include "MeshTypes.h"
#include "Input.h"

using namespace MeshType;
using namespace DirectX;

void ParticleEmitter::Initialize()
{
	ParticleRenderer* renderer = AddComponent<ParticleRenderer>(this)->SetEmitter(this);

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
	GameObject::Draw();
}