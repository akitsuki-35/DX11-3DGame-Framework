/*============================================================
*	@file	 : Particle.cpp
*	@brief	 : パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#include "Particle.h"

void Particle::update(double dt)
{
	float t = static_cast<float>(dt);

	if (!mEnable) {
		return;
	}

	Vector3 gravity{ 0.0f, -9.8f, 0.0f };
	mVelocity += gravity * t; // 重力
	mVelocity += mVelocity * -1.0f * t; // 抵抗
	mPosition += mVelocity * t;

	mLife--;

	if (mLife <= 0) {
		mEnable = false;
	}
}