/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	タイトルシーン[title.cpp]
*
* 　作成者 : @akitsuki-35（https://github.com/akitsuki-35）
* 　作成日 : 2026/03/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "title.h"
#include "scene.h"
#include "keylogger.h"
#include "texture.h"
#include "fade.h"
#include "audio.h"
#include "direct3d.h"
#include <math.h>

static double g_Accumulatedtime{ 0.0 };
static double g_KeyInputTime{};

enum TitleState
{
	TITLE_FADE_IN,
	TITLE_KEYINPUT_WAIT,
	TITLE_KEYINPUT_ACTION,
	TITLE_FADE_OUT
};

static TitleState g_State = TITLE_FADE_IN;

void TitleInitialize()
{
	FadeStart(1.0f, true);

	g_State = TITLE_FADE_IN;
}

void TitleFinalize()
{
}

void TitleUpdate(double elapsed_time)
{
	g_Accumulatedtime += elapsed_time;

	switch (g_State)
	{
	case TITLE_FADE_IN:
		if (GetFadeState() == FADE_IN_END) {
			g_State = TITLE_KEYINPUT_WAIT;
		}
		break;

	case TITLE_KEYINPUT_WAIT:
		if (KeyIsTrigger(KK_ENTER))
		{
			g_State = TITLE_KEYINPUT_ACTION;
			g_KeyInputTime = g_Accumulatedtime;
			//サウンド再生
			
		}
		break;

	case TITLE_KEYINPUT_ACTION:
		if (g_Accumulatedtime - g_KeyInputTime > 1.0){
			g_State = TITLE_FADE_OUT;
			FadeStart(1.0f, false);
		}
		break;

	case TITLE_FADE_OUT:
		if (GetFadeState() == FADE_OUT_END) {
			// ゲームシーンに遷移
			SetNextScene(SCENE_GAME);
		}
		break;

	default:
		break;
	}
}

void TitleDraw()
{
	if (g_State != TITLE_FADE_IN) {
		//float alpha = static_cast<float>((sin(g_Accumulatedtime)+ 1.0f)) * 0.5f;

	}
}