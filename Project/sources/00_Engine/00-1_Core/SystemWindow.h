/*============================================================
*	@file	 : SystemWindow.h
*	@brief	 : システムウィンドウ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/05
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "Config.h"
#include <Windows.h>

namespace System {
/*============================================================
*	@class	: System::Window
*	@brief	: メインウィンドウ
*============================================================*/
	class Window final
	{
	/*--------------------------------------------------
		Singleton用
	----------------------------------------------------*/
	public:
		static Window& getInstance() {
			static Window instance;
			return instance;
		}

	private:
		Window() = default;
		Window(const Window&) = delete;

		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;

		Window& operator=(Window&&) = delete;
		~Window() {};

	/*--------------------------------------------------
		メンバ変数・メンバ関数
	----------------------------------------------------*/
	private:
		HWND mHwnd{ nullptr };
		static constexpr char CLASS_NAME[] = "AppClass"; // ウィンドウクラス名
		static constexpr char WINDOW_NAME[] = "A.X.I.A"; // アプリケーション名
		HINSTANCE mHInstance{ nullptr };
		int mWidth{ Screen::WIDTH };
		int mHeigth{ Screen::HEIGHT };

		// ウィンドウプロシージャ
		static LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		void Initialize(HINSTANCE hInstance, int width = Screen::WIDTH, int height = Screen::HEIGHT);
		void Finalize() const;

		// ウィンドウ表示
		void Show(int nCmdShow) const;

		// Windowsメッセージ
		int ProcessMessage() const;

		// ウィンドウハンドル取得
		HWND GetHandle() const { return mHwnd; }

		// ゲーム終了
		void GameQuit() const;
	};
}