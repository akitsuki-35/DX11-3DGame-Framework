/*============================================================
*	@file	 : AppLoop.h
*	@brief	 : アプリケーションループ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/07
*	@updated : 2026/09/20
*============================================================*/
#pragma once

/*============================================================
*	@class	: AppLoop
*	@brief	: アプリケーションループ制御
*============================================================*/
class AppLoop final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static AppLoop& getInstance() {
		static AppLoop instance;
		return instance;
	}

private:
	AppLoop() = default;
	AppLoop(const AppLoop&) = delete;

	AppLoop& operator=(const AppLoop&) = delete;
	AppLoop(AppLoop&&) = delete;

	AppLoop& operator=(AppLoop&&) = delete;
	~AppLoop() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
public:
	int Run() const;
};