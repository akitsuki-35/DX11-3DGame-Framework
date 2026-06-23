/*============================================================
*	@file	 : direct3d.h
*	@brief	 : DirectX初期化
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/12
*	@updated : 2026/06/02
*============================================================*/
#ifndef DIRECT3D_H
#define DIRECT3D_H

#include <d3d11.h>
#include<Windows.h>

#define SAFE_RELEASE(o) if (o) { (o)->Release(); o = NULL; }

bool Direct3DInitialize(HWND hwnd);
void Direct3DFinalize();

void Direct3DClear(); //バックバッファのクリア
void Direct3DPresent(); //バックバッファの表示

unsigned int Direct3DGetBackBufferWidth();
unsigned int Direct3DGetBackBufferHeight();

ID3D11Device* Direct3DGetDevice();
ID3D11DeviceContext* Direct3DGetDeviceContext();
IDXGISwapChain* Direct3DGetSwapChain();

/*------------------------------------------------------------
	アルファブレンド設定
------------------------------------------------------------*/
enum AlphaBlendMode
{
	BLEND_MULTIPLY,
	BLEND_ADD
};

void Direct3DSetAlphaBlend(AlphaBlendMode blend);

#endif //DIRECT3D_H