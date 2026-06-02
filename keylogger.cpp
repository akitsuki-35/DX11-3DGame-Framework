/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	キーボード入力[keylogger.cpp]
*
* 　作成者 : @akitsuki-35（https://github.com/akitsuki-35）
* 　作成日 : 2025/6/27
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "keylogger.h"

static KeyboardState g_PtevState = {};
static KeyboardState g_TriggerState = {};
static KeyboardState g_ReleaseState = {};

void KeyLoggerInitialize()
{
	KeyboardInitialize();
}

void KeyLoggerUpdate()
{
	const KeyboardState* currentState = GetKeyboardState();

	LPBYTE pt = (LPBYTE)&g_TriggerState;
	LPBYTE pn = (LPBYTE)currentState;
	LPBYTE po = (LPBYTE)&g_PtevState;
	LPBYTE pr = (LPBYTE)&g_ReleaseState;

	for (int i = 0; i < sizeof(KeyboardState); i++){
		pt[i] = (po[i] ^ pn[i]) & pn[i];
		pr[i] = (po[i] ^ pn[i]) & ~pn[i];
	}

	g_PtevState = *currentState;
}

bool KeyIsPressd(Keys key)
{
	return IsKeyDown(key);
}

bool KeyIsTrigger(Keys key)
{
	return IsKeyDown(key, &g_TriggerState);
}

bool KeyIsRelease(Keys key)
{
	return IsKeyDown(key, &g_ReleaseState);
}
