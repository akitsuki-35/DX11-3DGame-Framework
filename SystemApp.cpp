/*============================================================
*	@file	 : SystemApp.cpp
*	@brief	 : アプリケーションループ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/07
*	@updated : 2026/07/07
*============================================================*/
#include "SystemApp.h"
#include "SystemWindow.h"
#include "Manager.h"

void System::App::Init()
{
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;
}

int System::App::Run()
{
	// アプリケーションループ
	while (1)
	{
		if (System::Window::getInstance().ProcessMessage()) {
			break;
		}
		else{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				Manager::Update();
				Manager::Draw();
			}
		}
	}

    return 0;
}
