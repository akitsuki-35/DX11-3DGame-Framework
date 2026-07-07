/*============================================================
*	@file	 : SystemTimer.cpp
*	@brief	 : システムタイマー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/07/07
*============================================================*/
#include "SystemTimer.h"
#include <Windows.h>
#include <xmmintrin.h>

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