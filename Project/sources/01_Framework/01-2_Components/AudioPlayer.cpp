/*============================================================
*	@file	 : AudioPlayer.cpp
*	@brief	 : オーディオ再生
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/09
*	@updated : 2026/08/09
*============================================================*/
#include "AudioPlayer.h"
#include "AudioManager.h"
#include <cassert>

IXAudio2* AudioPlayer::mXaudio{ nullptr };
IXAudio2MasteringVoice* AudioPlayer::mMasteringVoice{ nullptr };

void AudioPlayer::InitializeMaster()
{
	// COM初期化
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	// XAudio生成
	hr = XAudio2Create(&mXaudio, 0);
	assert(SUCCEEDED(hr));

	// マスタリングボイス生成
	hr = mXaudio->CreateMasteringVoice(&mMasteringVoice);
	assert(SUCCEEDED(hr));
}


void AudioPlayer::FinalizeMaster()
{
	if (mMasteringVoice) {
		mMasteringVoice->DestroyVoice();
		mMasteringVoice = nullptr;
	}

	if (mXaudio) {
		mXaudio->Release();
		mXaudio = nullptr;
	}

	CoUninitialize();
}

void AudioPlayer::Finalize()
{
	if (mSourceVoice) {
		mSourceVoice->Stop();
		mSourceVoice->FlushSourceBuffers();
		mSourceVoice->DestroyVoice();
		mSourceVoice = nullptr;
	}
}

AudioPlayer* AudioPlayer::LoadAudio(const char* fileName)
{
	_mAudio = AudioManager::getInstance().Load(fileName);
	assert(_mAudio);

	// サウンドソース作成
	HRESULT hr = mXaudio->CreateSourceVoice(&mSourceVoice, _mAudio->GetFormat());
	assert(SUCCEEDED(hr));

	return this;
}

void AudioPlayer::Play(bool isLoop)
{
	if (!_mAudio || !mSourceVoice) return;

	mSourceVoice->Stop();
	mSourceVoice->FlushSourceBuffers();

	// バッファ設定
	XAUDIO2_BUFFER buf{};
	buf.AudioBytes = _mAudio->GetAudioBytes();
	buf.pAudioData = _mAudio->GetPCM();
	buf.PlayBegin = 0;
	buf.PlayLength = _mAudio->GetSamples();

	if (isLoop) {
		buf.LoopBegin = 0;
		buf.LoopLength = _mAudio->GetSamples();
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	mSourceVoice->SubmitSourceBuffer(&buf);
	mSourceVoice->Start();
}