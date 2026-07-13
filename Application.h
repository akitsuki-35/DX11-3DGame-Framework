/*============================================================
*	@file	 : Application.h
*	@brief	 : アプリケーションループ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/07
*	@updated : 2026/07/07
*============================================================*/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Config.h"
/*============================================================
*	@class	: Application
*	@brief	: アプリケーション
*============================================================*/
	class Application
	{
	private:
		bool mPaused{ false }; // ポーズフラグ

		Application() = default;
		Application(const Application&) = delete;

		Application& operator=(const Application&) = delete;
		Application(Application&&) = delete;

		Application& operator=(Application&&) = delete;
		~Application() {};

	public:
		static Application& getInstance() {
			static Application instance;
			return instance;
		}

		int Run() const;
	};

#endif // APPLICATION_H