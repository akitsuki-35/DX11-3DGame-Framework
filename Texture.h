/*============================================================
*	@file	 : Texture.h
*	@brief	 : テクスチャ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/07/27
*============================================================*/
#pragma once

#include <string>
#include <wrl/client.h>
#include <d3d11.h>
#include <DirectXMath.h>

/*============================================================
*	@class	: Texture
*	@brief	: テクスチャ
*============================================================*/
class Texture
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

protected:
	// サイズ
	DirectX::XMUINT2 mSize{};

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _mSRV{ nullptr };

public:
	bool Load(const std::wstring& filePath);
	void Bind(UINT slot = 0) const;

	const DirectX::XMUINT2& GetSize() { return mSize; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() { return _mSRV; }
};