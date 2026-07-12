/*============================================================
*	@file	 : SystemTimer.cpp
*	@brief	 : ゲーム内時間制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/07/07
*============================================================*/
#include "SystemTimer.h"

void System::Timer::Initialize()
{
    timeBeginPeriod(1);
    mExecLastTime = timeGetTime();
    mCurrentTime = 0;
}

bool System::Timer::Tick(double frameRate)
{
    mCurrentTime = timeGetTime();

    if ((mCurrentTime - mExecLastTime) >= (frameRate)) {
        mExecLastTime = mCurrentTime;

        return true;
    }

    return false;
}