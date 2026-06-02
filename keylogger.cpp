/*============================================================
*	@file	 : keylogger.cpp
*	@brief	 : キーボード入力
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2025/06/27
*	@Updated : 2026/06/02
*============================================================*/
#include "keylogger.h"

/*------------------------------------------------------------
	メンバ変数定義
------------------------------------------------------------*/
KeyboardState KeyLogger::ptevState;
KeyboardState KeyLogger::triggerState;
KeyboardState KeyLogger::releaseState;

void KeyLogger::Initialize()
{
	KeyboardInitialize();
}

void KeyLogger::Update()
{
	const KeyboardState* currentState = GetKeyboardState();

	LPBYTE pt = (LPBYTE)&triggerState;
	LPBYTE pn = (LPBYTE)currentState;
	LPBYTE po = (LPBYTE)&ptevState;
	LPBYTE pr = (LPBYTE)&releaseState;

	for (int i = 0; i < sizeof(KeyboardState); i++) {
		pt[i] = (po[i] ^ pn[i]) & pn[i];
		pr[i] = (po[i] ^ pn[i]) & ~pn[i];
	}

	ptevState = *currentState;
}

/*------------------------------------------------------------
	キーが押されている間を判定
------------------------------------------------------------*/
bool KeyLogger::IsPressd(Keys key)
{
	return IsKeyDown(key);
}

/*------------------------------------------------------------
	キーが押された瞬間を判定
------------------------------------------------------------*/
bool KeyLogger::IsTrigger(Keys key)
{
	return IsKeyDown(key, &triggerState);
}

/*------------------------------------------------------------
	キーが離された瞬間を判定
------------------------------------------------------------*/
bool KeyLogger::IsRelease(Keys key)
{
	return IsKeyDown(key, &releaseState);
}