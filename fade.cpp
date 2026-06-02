/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	フェード制御[fade.cpp]
*
* 　作成者 : @akitsuki-35（https://github.com/akitsuki-35）
* 　作成日 : 2026/03/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "fade.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "direct3d.h"

#include "debug_memoryleak.h"

static FadeState g_FadeState = FADE_IN;
static double g_FadeTime;
static double g_Accumulatedtime = 0.0;
static double g_FadeStartTime = 0.0;
static XMFLOAT4 g_FadeColor = { 0.0f, 0.0f, 0.0f, 1.0f };
static int g_FadeTexID = -1;

Texture* g_FadeTexture{ nullptr };

void FadeInitialize()
{
	g_FadeState = FADE_IN;
	g_Accumulatedtime = 0.0;
	g_FadeTexture = new Texture(L"Resources/Texture/Common/white.png");
}

void FadeFinalize()
{
	delete g_FadeTexture;
}

void FadeUpdate(double elapsedTime)
{
	// 時間計測とステートの管理
	if (g_FadeState == NONE || g_FadeState == FADE_OUT_END || g_FadeState == FADE_IN_END) {
		return;
	}

	g_Accumulatedtime += elapsedTime;

	double lifeTime = g_Accumulatedtime - g_FadeStartTime;

	float alpha = (float)(lifeTime / g_FadeTime);

	g_FadeColor.w = g_FadeState == FADE_IN ? 1.0f - alpha : alpha;

	if (g_FadeTime <= lifeTime) {
		g_FadeState = g_FadeState == FADE_IN ? FADE_IN_END : FADE_OUT_END;
	}
}

void FadeDraw()
{
	if (g_FadeState == NONE || g_FadeState == FADE_IN_END) {
		return;
	}

	//SpriteDraw(g_FadeTexID, { 0.0f, 0.0f },
	//	{ static_cast<float>(Direct3DGetBackBufferWidth()),
	//	static_cast<float>(Direct3DGetBackBufferHeight()) },
	//	g_FadeColor);

	g_FadeTexture->Draw({ 0.0f, 0.0f }, { SCREEN_WIDTH, SCREEN_HEIGHT }, g_FadeColor);
}

void FadeStart(double fadeTime, bool isFadeIn, XMFLOAT4 fadeColor)
{
	g_FadeTime = fadeTime;
	g_FadeState = isFadeIn ? FADE_IN : FADE_OUT;

	g_FadeStartTime = g_Accumulatedtime;

	g_FadeColor = fadeColor;
}

const FadeState GetFadeState()
{
	return g_FadeState;
}
