/*============================================================
*	@file	 : keylogger.h
*	@brief	 : キーボード入力
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2025/06/27
*	@Updated : 2026/06/02
*============================================================*/
#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include "keyboard.h"

/*============================================================
*	@class	: KeyLogger
*	@brief	: キーボード入力状態取得
*============================================================*/
class KeyLogger
{
private:
	static KeyboardState ptevState;
	static KeyboardState triggerState;
	static KeyboardState releaseState;

public:
	static void Initialize();
	static void Update();

	static bool IsPressd(Keys key);
	static bool IsTrigger(Keys key);
	static bool IsRelease(Keys key);
};

#endif // KEYLOGGER_H