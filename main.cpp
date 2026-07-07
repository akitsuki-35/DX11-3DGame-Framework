/*============================================================
*	@file	 : Main.cpp
*	@brief	 : メイン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/07/07
*============================================================*/
#include "Main.h"

// System
#include "SystemWindow.h"
#include "SystemTimer.h"
#include "SystemApp.h"

#include "Manager.h"
#include "Debugger.h"
#include <thread>

// ImGui
#include <imgui_impl_win32.h>

/*------------------------------------------------------------
	ウィンドウ情報
------------------------------------------------------------*/
const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "Game Window";

/*------------------------------------------------------------
	ローカル関数 プロトタイプ宣言
------------------------------------------------------------*/
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*------------------------------------------------------------
	メイン
------------------------------------------------------------*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 未使用パラメータ明示（警告を消去）
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// ウィンドウ初期化
	System::Window::getInstance().Initialize(hInstance);

	Manager::Initialize();

#if defined(DEBUG) || defined(_DEBUG)
	//Debugger::GetInstance().Initialize(g_Window);
#endif // defined(DEBUG) || defined(_DEBUG)

	// ウィンドウ表示
	System::Window::getInstance().Show(nCmdShow);

	// タイマー初期化
	System::Timer::getInstance().Initialize();

	// ゲームループ
	int isQuit = System::App::getInstance().Run();

	//	#if defined(DEBUG) || defined(_DEBUG)
	//			//Debugger::GetInstance().Update();
	//			//Debugger::GetInstance().Draw();
	//	#endif // defined(DEBUG) || defined(_DEBUG)
	//		}
	//	}
	//}

	timeEndPeriod(1);

#if defined(DEBUG) || defined(_DEBUG)
	//Debugger::GetInstance().Finalize();
#endif // defined(DEBUG) || defined(_DEBUG)

	Manager::Finalize();
	System::Window::getInstance().Finalize();

	return isQuit;
}