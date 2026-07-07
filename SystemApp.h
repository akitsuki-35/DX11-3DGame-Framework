/*============================================================
*	@file	 : SystemApp.h
*	@brief	 : アプリケーションループ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/07
*	@updated : 2026/07/07
*============================================================*/
#ifndef SYSTEMAPP_H
#define SYSTEMAPP_H

#include "Config.h"

namespace System {
/*============================================================
*	@class	: App
*	@brief	: アプリケーション
*============================================================*/
	class App
	{
	private:
		bool mPaused{ false }; // ポーズフラグ

		App() = default;
		App(const App&) = delete;

		App& operator=(const App&) = delete;
		App(App&&) = delete;

		App& operator=(App&&) = delete;
		~App() {};

	public:
		static App& getInstance() {
			static App instance;
			return instance;
		}

		void Init();

		int Run();
	};
}

#endif // SYSTEMAPP_H