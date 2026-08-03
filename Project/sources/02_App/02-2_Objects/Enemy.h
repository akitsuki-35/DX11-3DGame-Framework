/*============================================================
*	@file	 : Enemy.h
*	@brief	 : エネミー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/08/03
*============================================================*/
#pragma once

#include "GameObject.h"
#include "Shader.h"

/*============================================================
*	@class	: Enemy
*	@brief	: エネミー
*============================================================*/
class Enemy : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };
	Shader* mShader{};

public:
	Enemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};