/*============================================================
*	@file	 : SystemTimer.h
*	@brief	 : システムタイマー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/07/07
*============================================================*/
#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

#include <Windows.h>

namespace System {
	class Timer
	{
	private:
		DWORD mExecLastTime{};
		DWORD mCurrentTime{};

		Timer() = default;
		Timer(const Timer&) = delete;

		Timer& operator=(const Timer&) = delete;
		Timer(Timer&&) = delete;

		Timer& operator=(Timer&&) = delete;
		~Timer() {};

	public:
		static Timer& getInstance() {
			static Timer instance;
			return instance;
		}

		void Initialize();
		bool Tick(double frameRate);
	};
}

#endif // SYSTEMTIMER_H