/*============================================================
*	@file	 : MeshField.h
*	@brief	 : メッシュフィールド
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/08
*	@updated : 2026/09/08
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: MeshField
*	@brief	: メッシュフィールド
*============================================================*/
class MeshField : public GameObject
{
public:
	MeshField() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};