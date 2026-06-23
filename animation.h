/*============================================================
*	@file	 : animation.h
*	@brief	 : スプライトアニメーション
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/01
*	@updated : 2026/06/02
*============================================================*/
#ifndef ANIMATION_H
#define ANIMATION_H

#include <d3d11.h>
#include <DirectXMath.h>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class SpriteSheet;

/*============================================================
*	@class	: Animation
*	@brief	: スプライトアニメーション再生
*============================================================*/
class Animation
{
private:
	SpriteSheet* pSpriteSheet;
	double perSecond{};
	double accumulatedTime{ 0.0f };
	bool isLoop{ true };
	bool isStoped{ false };

public:
	Animation(SpriteSheet* pSpriteSheet, double perSecond, bool isLoop = true)
		: pSpriteSheet(pSpriteSheet), perSecond(perSecond), isLoop(isLoop) {}

	void Update(double elapsedTime);
	void Draw() const;

	bool IsLoop() const { return isLoop; }
	bool IsStoped() const { return isStoped; }
};

#endif // ANIMATION_H