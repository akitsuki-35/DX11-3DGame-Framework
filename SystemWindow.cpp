/*============================================================
*	@file	 : SystemWindow.cpp
*	@brief	 : システムウィンドウ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/05
*	@updated : 2026/07/07
*============================================================*/
#include "SystemWindow.h"

void System::Window::Initialize(HINSTANCE hInstance, int width, int height)
{
	mHInstance = hInstance;
	mWidth = width;
	mHeigth = height;

	// ウィンドウクラス登録
	WNDCLASSEX wcex{};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	// ウィンドウ短形
	RECT rc = { 0, 0, (LONG)mWidth, (LONG)mHeigth };

	// ウィンドウのスタイル
	DWORD windowStyle = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	// 短形座標を計算
	AdjustWindowRect(&rc, windowStyle, FALSE);

	// ウィンドウの幅と高さを算出
	int windowWidth = rc.right - rc.left;
	int windowHeight = rc.bottom - rc.top;

	// プライマリモニターの画面解像度取得
	int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
	int desktopHeight = GetSystemMetrics(SM_CYSCREEN);

	// デスクトップ中央にウィンドウを表示
	int windowX = std::max((desktopWidth - windowWidth) / 2, 0);
	int windowY = std::max((desktopHeight - windowHeight) / 2, 0);

	// メインウィンドウ作成
	mHwnd = CreateWindowEx(
		0, 
		CLASS_NAME, 
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		rc.right - rc.left, 
		rc.bottom - rc.top, 
		nullptr, 
		nullptr, 
		hInstance, 
		nullptr
	);

	(void)CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

	// タイトルバーと枠を削除
	SetWindowLongPtr(mHwnd, GWL_STYLE, windowStyle &= ~(WS_CAPTION | WS_THICKFRAME));
}

void System::Window::Finalize()
{
	UnregisterClass(CLASS_NAME, mHInstance);
	CoUninitialize();
}

void System::Window::Show(int nCmdShow)
{
	ShowWindow(mHwnd, nCmdShow);
	UpdateWindow(mHwnd);
}

bool System::Window::ProcessMessage()
{
	// メッセージループ
	MSG msg{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return true;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return false;
}

LRESULT System::Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ウィンドウプロシージャ
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}