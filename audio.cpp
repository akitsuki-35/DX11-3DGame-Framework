/*============================================================
*	@file	 : audio.cpp
*	@brief	 : 音声ファイル管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/01
*	@updated : 2026/06/02
*============================================================*/
#include <xaudio2.h>
#include <assert.h>
#include "audio.h"

#pragma comment(lib, "winmm.lib")

/*------------------------------------------------------------
	グローバル変数定義
------------------------------------------------------------*/
static IXAudio2* g_Xaudio{};
static IXAudio2MasteringVoice* g_MasteringVoice{};

/*------------------------------------------------------------
	オーディオ構造体
------------------------------------------------------------*/
struct Audio
{
public:
	IXAudio2SourceVoice* sourceVoice{};
	BYTE* soundData{};

	int	length{};
	int	playLength{};
};

/*------------------------------------------------------------
	マクロ定義
------------------------------------------------------------*/
#define AUDIO_MAX 100
static Audio g_Audio[AUDIO_MAX]{};

void AudioInitialize()
{
	// XAudio生成
	XAudio2Create(&g_Xaudio, 0);

	// マスタリングボイス生成
	g_Xaudio->CreateMasteringVoice(&g_MasteringVoice);
}

void AudioFinalize()
{
	g_MasteringVoice->DestroyVoice();
	g_Xaudio->Release();
}

int AudioLoad(const char *fileName)
{
	int index = -1;

	for (int i = 0; i < AUDIO_MAX; i++)
	{
		if (g_Audio[i].sourceVoice == nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
		return -1;

	// サウンドデータ読込
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioInfo = { 0 };
		MMCKINFO riffChunkInfo = { 0 };
		MMCKINFO dataChunkInfo = { 0 };
		MMCKINFO mmckInfo = { 0 };
		UINT32 bufLen;
		LONG readLen;

		hmmio = mmioOpen((LPSTR)fileName, &mmioInfo, MMIO_READ);
		assert(hmmio);

		riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffChunkInfo, NULL, MMIO_FINDRIFF);

		mmckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckInfo, &riffChunkInfo, MMIO_FINDCHUNK);

		if (mmckInfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckInfo, 0);

		dataChunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &dataChunkInfo, &riffChunkInfo, MMIO_FINDCHUNK);

		bufLen = dataChunkInfo.cksize;
		g_Audio[index].soundData = new unsigned char[bufLen];
		readLen = mmioRead(hmmio, (HPSTR)g_Audio[index].soundData, bufLen);

		g_Audio[index].length = readLen;
		g_Audio[index].playLength = readLen / wfx.nBlockAlign;

		mmioClose(hmmio, 0);
	}

	// サウンドソース生成
	g_Xaudio->CreateSourceVoice(&g_Audio[index].sourceVoice, &wfx);
	assert(g_Audio[index].sourceVoice);

	return index;
}

void AudioRelease(int index)
{
	g_Audio[index].sourceVoice->Stop();
	g_Audio[index].sourceVoice->DestroyVoice();

	delete[] g_Audio[index].soundData;
	g_Audio[index].soundData = nullptr;
}

void AudioPlay(int index, bool loop)
{
	g_Audio[index].sourceVoice->Stop();
	g_Audio[index].sourceVoice->FlushSourceBuffers();

	// バッファ設定
	XAUDIO2_BUFFER bufInfo;

	memset(&bufInfo, 0x00, sizeof(bufInfo));
	bufInfo.AudioBytes = g_Audio[index].length;
	bufInfo.pAudioData = g_Audio[index].soundData;
	bufInfo.PlayBegin = 0;
	bufInfo.PlayLength = g_Audio[index].playLength;

	// ループ設定
	if (loop)
	{
		bufInfo.LoopBegin = 0;
		bufInfo.LoopLength = g_Audio[index].playLength;
		bufInfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	g_Audio[index].sourceVoice->SubmitSourceBuffer(&bufInfo, NULL);

	// 再生
	g_Audio[index].sourceVoice->Start();
}