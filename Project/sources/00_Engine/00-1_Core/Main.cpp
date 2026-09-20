/*============================================================
*	@file	 : Main.cpp
*	@brief	 : メイン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/09/20
*============================================================*/
// System
#include "SystemWindow.h"
#include "SystemTimer.h"
#include "AppLoop.h"

#include "AppSetup.h"
#include <d3d11.h>

/*------------------------------------------------------------
	メイン
------------------------------------------------------------*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 未使用パラメータ明示（警告を消去）
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// DPIスケーリング対策
	SetProcessDPIAware();

	// ウィンドウ初期化
	System::Window::getInstance().Initialize(hInstance);

	AppSetup::Initialize();

	// ウィンドウ表示
	System::Window::getInstance().Show(nCmdShow);

	// タイマー初期化
	System::Timer::getInstance().Initialize();

	// ゲームループ
	int isQuit = AppLoop::getInstance().Run();

	timeEndPeriod(1);

	AppSetup::Finalize();

	return isQuit;
}