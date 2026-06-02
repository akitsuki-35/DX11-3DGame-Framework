/*============================================================
*	@file	 : audio.h
*	@brief	 : 音声ファイル管理
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/01
*	@Updated : 2026/06/02
*============================================================*/
#ifndef AUDIO_H
#define AUDIO_H

void AudioInitialize();
void AudioFinalize();

int AudioLoad(const char* fileName);
void AudioRelease(int index);
void AudioPlay(int index, bool loop = false);

#endif // AUDIO_H