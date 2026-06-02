/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	スプライトアニメーション[animation.h]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/01
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef ANIMATION_H
#define ANIMATION_H

#include <d3d11.h>
#include <DirectXMath.h>

class SpriteSheet;

class Animation
{
private:
	SpriteSheet* pSpriteSheet;
	int patternNum{ 0 };
	DirectX::XMUINT2 startPos{};
	double perSecond{};
	double accumulatedTime{ 0.0f };
	bool isLoop{ true };
	bool isStoped{ false };

public:
	Animation(SpriteSheet* pSpriteSheet, DirectX::XMUINT2 startPos, double perSecond, bool isLoop = true)
		: pSpriteSheet(pSpriteSheet), startPos(startPos), perSecond(perSecond), isLoop(isLoop) {}

	void Update(double elapsedTime);
	void Draw(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size,
		const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f }) const;
	void Draw(const DirectX::XMFLOAT2& position, const float& size = 1.0f,
		const DirectX::XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f }) const;

	bool IsLoop() { return isLoop; }
	bool IsStoped() const { return isStoped; }
};

#endif // ANIMATION_H