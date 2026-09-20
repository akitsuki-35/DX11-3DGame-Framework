/*============================================================
*	@file	 : Timer.cpp
*	@brief	 : 時間計測用タイマー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/08
*	@updated : 2026/09/08
*============================================================*/
#include "Timer.h"
#include "SystemTimer.h"

void Timer::Update(double deltaTime)
{
	// ゲーム内の速度に同期せず、システムタイマーのdtで更新
	deltaTime = System::Timer::getInstance().GetDeltaTime();

	// タイマーが0以下ならタイマーを無効化する
	// タイムアップ判定のため時間超過→タイマー停止まで1フレーム猶予を設ける
	if (mEnable) {
		if (mCurrentTime <= 0.0) {
			mCurrentTime = 0.0;
			mEnable = false;
		}
	}

	// タイマーが有効な間は時間経過処理を行う
	if (mEnable) {
		mCurrentTime -= deltaTime;
	}
}

void Timer::Start(double time)
{
	// 引数ありの場合は引数の時間をセットしてタイマー開始
	// 引数なしの場合はそのままタイマー開始
	if (time != 0) {
		Set(time);
	}

	mEnable = true;
}

void Timer::Reset(bool isEnable)
{
	// タイマーを最大時間でリセット
	mCurrentTime = mMaxTime;

	// 引数に応じてタイマーを即時スタートするか決定
	if (isEnable) {
		mEnable = true;
	}
	else {
		mEnable = false;
	}
}