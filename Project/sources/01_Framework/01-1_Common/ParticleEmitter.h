/*============================================================
*	@file	 : ParticleEmitter.h
*	@brief	 : パーティクルエミッタ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/18
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "GameObject.h"
#include "Particle.h"

/*============================================================
*	@class	: ParticleEmitter
*	@brief	: パーティクルエミッタ
*============================================================*/
class ParticleEmitter : public GameObject
{
	friend class ParticleRenderer;

private:
	static constexpr int PARTICLE_MAX{ 10000 };
	std::vector<Particle> mParticles{};

public:
	ParticleEmitter() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};