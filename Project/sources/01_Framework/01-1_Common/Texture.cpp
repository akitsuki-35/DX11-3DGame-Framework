/*============================================================
*	@file	 : Texture.cpp
*	@brief	 : テクスチャ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/07/27
*============================================================*/
#include "Texture.h"
#include "DeviceManager.h"
#include <DirectXTex.h>
using namespace DirectX;

bool Texture::Load(const std::wstring& filePath)
{
	// テクスチャ読込
	TexMetadata metaData{};
	ScratchImage image{};
	LoadFromWICFile(filePath.c_str(), WIC_FLAGS_NONE, &metaData, image);

	CreateShaderResourceView(D3D11::DeviceManager::getInstance().GetDevice().Get(),
		image.GetImages(), image.GetImageCount(), metaData, _mSRV.GetAddressOf());
	assert(_mSRV);

	return true;
}

void Texture::Bind(UINT slot) const
{
	// テクスチャのセット
	if (_mSRV) {
		D3D11::DeviceManager::getInstance().GetContext()->PSSetShaderResources(slot, 1, _mSRV.GetAddressOf());
	}
}