/*============================================================
*	@file	 : Title.h
*	@brief	 : タイトルシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "Scene.h"

/*============================================================
*	@class	: Title
*	@brief	: タイトルシーン
*============================================================*/
class Title : public Scene
{
public:
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};