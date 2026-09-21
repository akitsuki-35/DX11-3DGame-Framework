/*============================================================
*	@file	 : Timer.h
*	@brief	 : タイマーコンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/08
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "Component.h"

/*============================================================
*	@class	: Timer
*	@brief	: タイマーコンポーネント
*============================================================*/
class Timer : public Component
{
private:
	// 現在の経過時間
	double mCurrentTime{};

	// タイマー最大時間
	double mMaxTime{};

	// タイマーのアクティブ状態
	bool mEnable{};

public:
	Timer() = default;

	Timer(GameObject* owner)
		: Component(owner){}

	// タイマー経過処理
	void Update(double deltaTime) override;

	// タイマースタート
	void Start(double time = 0);

	// タイマーリセット
	void Reset(bool isEnable = false);
	
	// タイマーストップ
	void Stop() { mEnable = false; }

	// タイマーセット
	// セットだけしてスタートはさせない場合に使う
	void Set(double time) { mCurrentTime = mMaxTime = time; }

	// ゲッター
	double GetTime() const { return mCurrentTime; }
	double GetMaxTime() const { return mMaxTime; }
	bool GetEnable() const { return mEnable; }

	// タイムアップしているか取得
	bool IsTimeUp() const { return mEnable && mCurrentTime <= 0.0; }

	// 現在のタイマー進行度取得
	float GetProgress() const { return static_cast<float>(mCurrentTime / mMaxTime); }
};