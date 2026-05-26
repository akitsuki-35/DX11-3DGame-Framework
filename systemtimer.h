/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	システムタイマー[systemtimer.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/13
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/
// システムタイマーの初期化
void SystemTimerInitialize();

// システムタイマーのリセット
void SystemTimerReset();

// システムタイマーのスタート
void SystemTimerStart();

// システムタイマーのストップ
void SystemTimerStop();

// システムタイマーを0.1秒進める
void SystemTimerAdvance();

// 計測時間の取得
double GetSystemTimer();

// 現在の時間を取得
double GetAbsoluteTime(void);

// 経過時間の取得
float GetElapsedTime(void);

// システムタイマーが止まっているか？
bool SystemTimerIsStoped(void);

// 現在のスレッドを1つのプロセッサ（現在のスレッド）に制限
void LimitThreadAffinityToCurrentProc(void);

#endif // SYSTEMTIMER_H