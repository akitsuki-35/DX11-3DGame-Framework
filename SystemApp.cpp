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
#include "SystemTimer.h"
#include "Manager.h"
#include <Windows.h>

int System::App::Run()
{
	// アプリケーションループ
	while (1)
	{
		if (System::Window::getInstance().ProcessMessage()) {
			break;
		}
		else{
			if (System::Timer::getInstance().Tick(1000 / 60))
			{
				Manager::Update();
				Manager::Draw();
			}
		}
	}

    return 0;
}
