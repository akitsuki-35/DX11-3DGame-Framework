/*============================================================
*	@file	 : systemtimer.cpp
*	@brief	 : システムタイマー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/06/02
*============================================================*/
#include "systemtimer.h"

/*------------------------------------------------------------
	メンバ変数定義
------------------------------------------------------------*/
bool SystemTimer::isTimerStopped = true;
LONGLONG SystemTimer::ticksPerSec = 0;
LONGLONG SystemTimer::stopTime;
LONGLONG SystemTimer::lastElapsedTime;
LONGLONG SystemTimer::baseTime;

void SystemTimer::Initialize()
{
    isTimerStopped = true;
    ticksPerSec = 0;
    stopTime = 0;
    lastElapsedTime = 0;
    baseTime = 0;

    // 高分解能パフォーマンスカウンタ周波数の取得
    LARGE_INTEGER tps = { 0 };
    QueryPerformanceFrequency(&tps);
    ticksPerSec = tps.QuadPart;
}

void SystemTimer::Reset()
{
    LARGE_INTEGER time = GetAdjustedCurrentTime();

    baseTime = lastElapsedTime = time.QuadPart;
    stopTime = 0;
    isTimerStopped = false;
}

void SystemTimer::Start()
{
    // 現在の時間を取得
    LARGE_INTEGER time = { 0 };
    QueryPerformanceCounter(&time);

    // 今まで計測がストップしていたら
    if (isTimerStopped) {
        // 止まっていた時間を差し引いて基本時間を更新
        baseTime += time.QuadPart - stopTime;
    }

    stopTime = 0;
    lastElapsedTime = time.QuadPart;
    isTimerStopped = false;
}

void SystemTimer::Stop()
{
    if (isTimerStopped) return;

    LARGE_INTEGER time = { 0 };
    QueryPerformanceCounter(&time);

    lastElapsedTime = stopTime = time.QuadPart; // 停止時間を記録
    isTimerStopped = true;
}

void SystemTimer::Advance()
{
    stopTime += ticksPerSec / 10;
}

double SystemTimer::GetTime()
{
    LARGE_INTEGER time = GetAdjustedCurrentTime();

    return (double)(time.QuadPart - baseTime) / (double)ticksPerSec;
}

double SystemTimer::GetAbsoluteTime()
{
    LARGE_INTEGER time = { 0 };
    QueryPerformanceCounter(&time);

    return time.QuadPart / (double)ticksPerSec;
}

float SystemTimer::GetElapsedTime()
{
    LARGE_INTEGER time = GetAdjustedCurrentTime();

    double elapsedTime = (float)((double)(time.QuadPart - lastElapsedTime) / (double)ticksPerSec);
    lastElapsedTime = time.QuadPart;

    // タイマーが正確であることを保証するために、更新時間を0にクランプする。
    // elapsed_timeは、プロセッサが節電モードに入るか、何らかの形で別のプロセッサにシャッフルされると、この範囲外になる可能性がある。
    // よって、メインスレッドはSetThreadAffinityMaskを呼び出して、別のプロセッサにシャッフルされないようにする必要がある。
    // 他のワーカースレッドはSetThreadAffinityMaskを呼び出すべきではなく、メインスレッドから収集されたタイマーデータの共有コピーを使用すること。
    if (elapsedTime < 0.0f) {
        elapsedTime = 0.0f;
    }

    return (float)elapsedTime;
}

bool SystemTimer::IsStoped()
{
    return isTimerStopped;
}

void SystemTimer::LimitThreadAffinityToCurrentProc()
{
    HANDLE hCurrentProcess = GetCurrentProcess();

    DWORD_PTR dwProcessAffinityMask = 0;
    DWORD_PTR dwSystemAffinityMask = 0;

    if (GetProcessAffinityMask(hCurrentProcess, &dwProcessAffinityMask, &dwSystemAffinityMask) != 0 && dwProcessAffinityMask) {
     
        DWORD_PTR dwAffinityMask = (dwProcessAffinityMask & ((~dwProcessAffinityMask) + 1));

        HANDLE hCurrentThread = GetCurrentThread();
        if (INVALID_HANDLE_VALUE != hCurrentThread) {
            SetThreadAffinityMask(hCurrentThread, dwAffinityMask);
            CloseHandle(hCurrentThread);
        }
    }

    CloseHandle(hCurrentProcess);
}

LARGE_INTEGER SystemTimer::GetAdjustedCurrentTime()
{
    LARGE_INTEGER time;
    if (stopTime != 0) {
        time.QuadPart = stopTime;
    }
    else {
        QueryPerformanceCounter(&time);
    }

    return time;
}