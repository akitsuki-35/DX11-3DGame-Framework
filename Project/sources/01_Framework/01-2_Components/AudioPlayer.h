/*============================================================
*	@file	 : AudioPlayer.h
*	@brief	 : オーディオ再生
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/09
*	@updated : 2026/08/09
*============================================================*/
#pragma once

#include "Component.h"
#include <xaudio2.h>
#include <iostream>
#include <algorithm>

/*--------------------------------------------------
	前方宣言
----------------------------------------------------*/
class Audio;

/*============================================================
*	@class	: AudioPlayer
*	@brief	: オーディオ再生コンポーネント
*============================================================*/
class AudioPlayer : public Component
{
private:
	static IXAudio2* mXaudio;
	static IXAudio2MasteringVoice* mMasteringVoice;

	IXAudio2SourceVoice* mSourceVoice{ nullptr };
	Audio* _mAudio{ nullptr };

	// ボリューム
	float mVolume = { 1.0f };

public:
	static void InitializeMaster();
	static void FinalizeMaster();

	using Component::Component;

	void Finalize() override;

	AudioPlayer* LoadAudio(const char* fileName);

	// 再生
	void Play(bool isLoop = false);

	// 一時停止
	void Pause() {
		if (mSourceVoice) {
			mSourceVoice->Stop();
		}
	}

	// 再開
	void Resume() {
		if (mSourceVoice) {
			mSourceVoice->Start();
		}
	}

	// 停止
	void Stop() {
		if (mSourceVoice) {
			mSourceVoice->Stop();
			mSourceVoice->FlushSourceBuffers();
		}
	}

	// ボリューム変更
	void SetVolume(float Volume) {
		// 0.0f～1.0f間で補間
		mVolume = std::clamp(Volume, 0.0f, 1.0f);

		if (mSourceVoice) {
			mSourceVoice->SetVolume(mVolume);
		}
	}
};

