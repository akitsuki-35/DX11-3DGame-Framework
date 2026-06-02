/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	スプライトアニメーション[animation.cpp]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/01
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "animation.h"
#include "sprite.h"
#include "texture.h"
#include <DirectXMath.h>
using namespace DirectX;

void Animation::Update(double elapsedTime)
{
	if (isStoped) return;

	accumulatedTime += elapsedTime;

	if (accumulatedTime >= perSecond) {
		patternNum = (patternNum + 1) % pSpriteSheet->GetPatternMax();

		if (patternNum == pSpriteSheet->GetPatternMax() - 1) {
			if (!isLoop) isStoped = true;
		}

		accumulatedTime -= perSecond;
	}
}

void Animation::Draw(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size, const DirectX::XMFLOAT4& color) const
{
	pSpriteSheet->Draw(position, patternNum, size, color);
}

void Animation::Draw(const DirectX::XMFLOAT2& position, const float& size, const DirectX::XMFLOAT4& color) const
{
	pSpriteSheet->Draw(position, patternNum, size, color);
}