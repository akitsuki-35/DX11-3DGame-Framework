/*
*
*	ƒƒCƒ“[main.h]
*
* @Author  : Asuka Kuroda
* @Date	: 2026/04/21
* ----------------------------------------------------------------------------------------------------------
*
*/
#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <windows.h>
#include <assert.h>
#include <functional>
#include <list>

#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

#include <DirectXMath.h>
using namespace DirectX;

#include <DirectXTex.h>

#pragma comment (lib, "winmm.lib")

#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)

HWND GetWindow();

void Invoke(std::function<void()> Function, int Time);

#endif // FILENAME_H