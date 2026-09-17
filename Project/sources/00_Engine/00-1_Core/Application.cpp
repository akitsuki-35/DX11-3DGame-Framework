/*============================================================
*	@file	 : Application.cpp
*	@brief	 : アプリケーションループ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/07
*	@updated : 2026/09/16
*============================================================*/
#include "Application.h"
#include "SystemWindow.h"
#include "SystemTimer.h"
#include "SceneManager.h"

int Application::Run() const
{
	// アプリケーションループ
	while (1)
	{
		if (System::Window::getInstance().ProcessMessage()) {
			break;
		}
		else{
			// システムタイマー更新
			while (System::Timer::getInstance().Tick()) {
				// 更新
				SceneManager::getInstance().Update(System::Timer::getInstance().GetDeltaTime());
			}

			// 描画
			SceneManager::getInstance().Draw();
		}
	}

    return 0;
}