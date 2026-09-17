/*============================================================
*	@file	 : Result.h
*	@brief	 : リザルトシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/08/16
*============================================================*/
#pragma once

#include "Scene.h"

/*============================================================
*	@class	: Result
*	@brief	: リザルトシーン
*============================================================*/
class Result : public Scene
{
public:
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};