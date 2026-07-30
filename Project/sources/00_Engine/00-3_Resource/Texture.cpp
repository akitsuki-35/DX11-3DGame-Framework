/*============================================================
*	@file	 : Texture.cpp
*	@brief	 : テクスチャリソース
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/07/27
*============================================================*/
#include "Texture.h"
#include "DeviceManager.h"
#include <DirectXTex.h>
using namespace DirectX;

void Texture::Bind(UINT slot) const
{
	// テクスチャのセット
	if (_mSRV) {
		D3D11::DeviceManager::getInstance().GetContext()->PSSetShaderResources(slot, 1, _mSRV.GetAddressOf());
	}
}