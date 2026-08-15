/*============================================================
*	@file	 : Particle.h
*	@brief	 : パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "Vector3.h"

/*============================================================
*	@class	: Particle
*	@brief	: パーティクルの粒子構造体
*============================================================*/
class Particle
{
	friend class ParticleEmitter;

private:
	Vector3 mPosition{ 0.0f, 0.0f, 0.0f };
	Vector3 mScale{ 1.0f, 1.0f, 1.0f };
	float mAlpha{ 1.0f };

	Vector3 mVelocity{};

	bool mEnable{ false };
	int mLife{ 0 };
	int mMaxLife{ 0 };

public:
	Particle() = default;

	void update(double dt);
};