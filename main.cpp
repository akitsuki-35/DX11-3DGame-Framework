/*============================================================
*	@file	 : Main.cpp
*	@brief	 : メイン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/07/07
*============================================================*/
#include "Main.h"
#include "SystemWindow.h"
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*------------------------------------------------------------
	グローバル変数定義
------------------------------------------------------------*/
HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}

/*------------------------------------------------------------
	メイン
------------------------------------------------------------*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 未使用パラメータ明示（警告を消去）
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	System::Window::getInstance().Initialize(hInstance);

	Manager::Initialize();

#if defined(DEBUG) || defined(_DEBUG)
	//Debugger::GetInstance().Initialize(g_Window);
#endif // defined(DEBUG) || defined(_DEBUG)

	System::Window::getInstance().Show(nCmdShow);

	System::App::getInstance().Init();

	//DWORD dwExecLastTime;
	//DWORD dwCurrentTime;
	//timeBeginPeriod(1);
	//dwExecLastTime = timeGetTime();
	//dwCurrentTime = 0;

/*------------------------------------------------------------
	ゲームループ
------------------------------------------------------------*/
	int r = System::App::getInstance().Run();
	//MSG msg;
	//while(1)
	//{
 //       if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	//	{
	//		if(msg.message == WM_QUIT)
	//		{
	//			break;
	//		}
	//		else
	//		{
	//			TranslateMessage(&msg);
	//			DispatchMessage(&msg);
	//		}
 //       }
	//	else
	//	{
	//		dwCurrentTime = timeGetTime();

	//		if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
	//		{
	//			dwExecLastTime = dwCurrentTime;

	//			Manager::Update();
	//			Manager::Draw();

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

	return r;
}