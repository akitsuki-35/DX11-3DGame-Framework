/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	フェード制御[fade.h]
*
* 　作成者 : @akitsuki-35（https://github.com/akitsuki-35）
* 　作成日 : 2026/03/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef FADE_H
#define FADE_H

#include <DirectXMath.h>
using namespace::DirectX;

enum FadeState
{
	NONE,
	FADE_OUT,
	FADE_OUT_END,
	FADE_IN,
	FADE_IN_END
};

void FadeInitialize();
void FadeFinalize();
void FadeUpdate(double elapsedTime);
void FadeDraw();

void FadeStart(double fadeTime, bool isFadeIn, XMFLOAT4 fadeColor = { 0.0f,0.0f,0.0f,1.0f });

const FadeState GetFadeState();

#endif // !FADE_H