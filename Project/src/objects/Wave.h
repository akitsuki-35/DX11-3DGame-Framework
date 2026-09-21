/*============================================================
*	@file	 : Wave.h
*	@brief	 : 波
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/17
*	@updated : 2026/09/17
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Wave
*	@brief	: 波
*============================================================*/
class Wave : public GameObject
{
public:
	Wave() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};