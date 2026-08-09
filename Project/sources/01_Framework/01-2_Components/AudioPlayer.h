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

public:
	static void InitializeMaster();
	static void FinalizeMaster();

	using Component::Component;

	void Finalize() override;

	AudioPlayer* LoadAudio(const char* fileName);

	void Play(bool isLoop = false);
};

