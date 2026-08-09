/*============================================================
*	@file	 : AudioManager.cpp
*	@brief	 : オーディオ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/09
*	@updated : 2026/08/09
*============================================================*/
#include "AudioManager.h"
#include "Utility.h"
#include <cassert>

// minimp3
#define MINIMP3_IMPLEMENTATION
#include "minimp3/minimp3.h"
#define MINIMP3_EX_IMPLEMENTATION
#include "minimp3/minimp3_ex.h"

// stb_vorbis
#pragma warning(push, 0)
#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis/stb_vorbis.c"
#pragma warning(pop)

Audio* AudioManager::Load(const char* audioPath)
{
	// キャッシュ取得用にパスを正規化
	std::string key = Utility::File::normalizePath(audioPath);

	// キャッシュが存在すれば返す
	auto it = mAudios.find(key);

	if (it != mAudios.end()) {
		return it->second.get();
	}

	// オーディオリソース生成
	std::unique_ptr<Audio> audio = std::make_unique<Audio>();

	if (!generateAudio(*audio, key)) {
		return nullptr;
	}

	// オーディオを一時変数に格納
	Audio* a = audio.get();

	// コンテナへ登録
	mAudios.emplace(key, std::move(audio));

    return a;
}

bool AudioManager::generateAudio(Audio& audio, const std::string& path)
{
	std::string ext = Utility::File::getFileExtension(path);

	AudioType type = getType(ext);

	switch (type)
	{
	case AudioManager::AudioType::wav:
		return loadWav(audio, path);
		break;
	
	case AudioManager::AudioType::mp3:
		return loadMp3(audio, path);
		break;

	case AudioManager::AudioType::ogg:
		return loadOgg(audio, path);
		break;

	default:
		break;
	}

	return false;
}

AudioManager::AudioType AudioManager::getType(const std::string& ext)
{
	if (ext == "wav") {
		return AudioType::wav;
	}
	else if (ext == "mp3") {
		return AudioType::mp3;
	}
	else if (ext == "ogg") {
		return AudioType::ogg;
	}

	return AudioType();
}

bool AudioManager::loadWav(Audio& audio, const std::string& path)
{
	HMMIO hmmio{ nullptr };
	MMIOINFO mmioInfo = {};
	MMCKINFO riffChunk = {}; // RIFFチャンク用
	MMCKINFO dataChunk = {}; // 音声データチャンク用
	MMCKINFO fmtChunk = {}; // フォーマットチャンク用

	// ファイルを読み取り専用でオープン
	hmmio = mmioOpen((LPSTR)path.c_str(), &mmioInfo, MMIO_READ);
	if (!hmmio) { 
		return false;
	}

	// RIFFからWAVEを検索
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hmmio, &riffChunk, NULL, MMIO_FINDRIFF);

	// RIFFからフォーマット情報を検索
	fmtChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hmmio, &fmtChunk, &riffChunk, MMIO_FINDCHUNK);

	// フォーマット情報読み込み
	if (fmtChunk.cksize >= sizeof(WAVEFORMATEX)) {
		mmioRead(hmmio, (HPSTR)&audio.mFormat, sizeof(audio.GetFormat()));
	}
	else {
		PCMWAVEFORMAT pcmwf = { 0 };
		mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
		memset(&audio.mFormat, 0, sizeof(audio.mFormat));
		memcpy(&audio.mFormat, &pcmwf, sizeof(pcmwf));
		audio.mFormat.cbSize = 0;
	}

	mmioAscend(hmmio, &fmtChunk, 0);

	// データチャンクを検索
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hmmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);

	// PCMデータ読み込み
	audio.mBytes = dataChunk.cksize;
	audio.mPCM.resize(audio.mBytes);

	// 波形をバッファへ読み込み
	LONG readlen = mmioRead(hmmio, (HPSTR)audio.mPCM.data(), audio.mBytes);

	// サンプル数算出
	audio.mSamples = readlen / audio.mFormat.nBlockAlign;

	// ファイルを閉じる
	mmioClose(hmmio, 0);

	return true;
}

bool AudioManager::loadMp3(Audio& audio, const std::string& path)
{
	mp3dec_t mp3d;
	mp3dec_init(&mp3d);

	mp3dec_file_info_t info{};
	int ret = mp3dec_load(&mp3d, path.c_str(), &info, nullptr, nullptr);

	if (ret != 0 || info.buffer == nullptr) {
		return false;
	}

	// PCMをコピー
	audio.mPCM.resize(info.samples * sizeof(short));
	memcpy(audio.mPCM.data(), info.buffer, audio.mPCM.size());

	// フォーマット設定
	audio.mFormat.wFormatTag = WAVE_FORMAT_PCM;
	audio.mFormat.nChannels = info.channels;
	audio.mFormat.nSamplesPerSec = info.hz;
	audio.mFormat.wBitsPerSample = 16;
	audio.mFormat.nBlockAlign = (audio.mFormat.nChannels * audio.mFormat.wBitsPerSample) / 8;
	audio.mFormat.nAvgBytesPerSec = audio.mFormat.nSamplesPerSec * audio.mFormat.nBlockAlign;
	audio.mFormat.cbSize = 0;

	audio.mBytes = (UINT)audio.mPCM.size();
	audio.mSamples = audio.mBytes / audio.mFormat.nBlockAlign;

	free(info.buffer);

	return true;
}

bool AudioManager::loadOgg(Audio& audio, const std::string& path)
{
	int channels = 0;
	int sampleRate = 0;
	short* pcm = nullptr;

	int samples = stb_vorbis_decode_filename(path.c_str(), &channels, &sampleRate, &pcm);
	
	if (samples <= 0 || pcm == nullptr) {
		return false;
	}

	// 総サンプル数を算出
	int total = samples * channels;

	// PCMをコピー
	audio.mPCM.resize(total * sizeof(short));
	memcpy(audio.mPCM.data(), pcm, audio.mPCM.size());

	// フォーマット設定
	audio.mFormat.wFormatTag = WAVE_FORMAT_PCM;
	audio.mFormat.nChannels = channels;
	audio.mFormat.nSamplesPerSec = sampleRate;
	audio.mFormat.wBitsPerSample = 16;
	audio.mFormat.nBlockAlign = (channels * 16) / 8;
	audio.mFormat.nAvgBytesPerSec = sampleRate * audio.mFormat.nBlockAlign;
	audio.mFormat.cbSize = 0;

	audio.mBytes = (UINT)audio.mPCM.size();
	audio.mSamples = audio.mBytes / audio.mFormat.nBlockAlign;

	free(pcm);

	return true;
}
