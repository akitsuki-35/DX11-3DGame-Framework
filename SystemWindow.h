/*============================================================
*	@file	 : SystemWindow.h
*	@brief	 : システムウィンドウ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/05
*	@updated : 2026/07/07
*============================================================*/
#ifndef SYSTEMWINDOW_H
#define SYSTEMWINDOW_H

#include "Config.h"
#include <Windows.h>
#include <mutex>

namespace System {
/*============================================================
*	@class	: Window
*	@brief	: メインウィンドウ
*============================================================*/
	class Window
	{
	private:
		HWND mHwnd{ nullptr };
		static constexpr char CLASS_NAME[] = "AppClass";
		static constexpr char WINDOW_NAME[] = "Game Window";
		HINSTANCE mHInstance{ nullptr };
		int mWidth{ Screen::WIDTH };
		int mHeigth{ Screen::HEIGHT };

		std::mutex mMutex;

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		Window() = default;
		Window(const Window&) = delete;

		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;

		Window& operator=(Window&&) = delete;
		~Window() {};

	public:
		static Window& getInstance() {
			static Window instance;
			return instance;
		}

		void Initialize(HINSTANCE hInstance, int width = Screen::WIDTH, int height = Screen::HEIGHT);
		void Finalize();
		void Show(int nCmdShow);
		bool ProcessMessage();

		HWND GetHandle() const { return mHwnd; }
	};
}

#endif // SYSTEMWINDOW_H