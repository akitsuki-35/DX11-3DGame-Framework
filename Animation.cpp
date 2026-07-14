/*============================================================
*	@file	 : animation.cpp
*	@brief	 : スプライトアニメーション
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/01
*	@updated : 2026/06/02
*============================================================*/
#include "animation.h"
#include "sprite.h"
#include "texture.h"
#include <DirectXMath.h>
using namespace DirectX;

void Animation::Update(double elapsedTime)
{
	// 停止中なら何もしない
	if (isStoped) return;

	accumulatedTime += elapsedTime;

	// 現在のパターンIDとパターン総数を取得
	int currentPattern = pSpriteSheet->GetCurrentPattern();
	int patternMax = pSpriteSheet->GetPatternMax();

	if (accumulatedTime >= perSecond) {
		// パターン更新
		pSpriteSheet->SetPattern((currentPattern += 1) % patternMax);

		// 最後のパターンに到達
		if (currentPattern == patternMax - 1) {
			// ループフラグがoffならアニメーション停止
			if (!isLoop) isStoped = true;
		}

		accumulatedTime -= perSecond;
	}
}

void Animation::Draw() const
{
	pSpriteSheet->Draw();
}