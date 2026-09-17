/*============================================================
*	@file	 : Particle.cpp
*	@brief	 : パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/09/16
*============================================================*/
#include "Particle.h"
#include "ParticleEmitter.h"

void Particle::Update(double deltaTime)
{
	// 発射後パーティクル更新

	float dt = static_cast<float>(deltaTime);

	if (!mEnable) {
		return;
	}

	Vector3 gravity{ 0.0f, -mGravity, 0.0f };
	mVelocity += mAccel * dt;
	mVelocity += gravity * dt;
	mVelocity += mVelocity * mDrag * dt;
	mPosition += mVelocity * dt;

	mLife--;

	if (mLife <= 0) {
		mEnable = false;
	}
}

void Particle::SetParameter(const Vector3& position, const Vector3& velocity, const Vector3& accel, const Vector3& scale, const float& gravity, const float& drag, const int& life)
{
	// 外部からメンバ変数を初期化
	mPosition = position;
	mVelocity = velocity;
	mAccel = accel;
	mScale = scale;
	mGravity = gravity;
	mDrag = drag;
	mLife = life;
}