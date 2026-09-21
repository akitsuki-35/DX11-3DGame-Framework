/*============================================================
*	@file	 : SystemTimer.cpp
*	@brief	 : ゲーム内時間制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/09/16
*============================================================*/
#include "SystemTimer.h"

void System::Timer::Initialize()
{
    // タイマー初期化
    QueryPerformanceFrequency(&mFreq);
    QueryPerformanceCounter(&mExecLastTime);
}

bool System::Timer::Tick()
{
    // タイマー進行
    QueryPerformanceCounter(&mCurrentTime);

    // dt更新
    double dt = static_cast<double>(mCurrentTime.QuadPart - mExecLastTime.QuadPart)
        / static_cast<double>(mFreq.QuadPart);

    mExecLastTime = mCurrentTime;

    // 累積時間更新
    mAccumulator += dt;

    if (mAccumulator >= mFps) {
        mAccumulator -= mFps;
        return true;
    }

    return false;
}

void System::Timer::Refresh()
{
    // 累積時間を現在時間でリセット
    QueryPerformanceCounter(&mCurrentTime);

    mExecLastTime = mCurrentTime;

    mAccumulator = 0.0;
}