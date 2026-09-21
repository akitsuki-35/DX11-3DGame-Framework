/*============================================================
*	@file	 : Camera.h
*	@brief	 : カメラオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/26
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "Camera.h"
#include <DirectXMath.h>

/*============================================================
*	@class	: Camera
*	@brief	: カメラ
*============================================================*/
class GameCamera final : public Camera
{
public:
	virtual ~GameCamera() = default;
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
};