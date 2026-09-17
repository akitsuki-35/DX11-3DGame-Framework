/*============================================================
*	@file	 : Game.h
*	@brief	 : ゲームシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/28
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "Scene.h"
#include <list>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class GameObject;

/*============================================================
*	@class	: Game
*	@brief	: ゲームシーン
*============================================================*/
class Game : public Scene
{
private:
	// スローモーション中フラグ
	static inline bool mSlow{ false };

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	// スローモーション開始
	static void SetSlow(const bool& isSlow) { mSlow = isSlow; }
};