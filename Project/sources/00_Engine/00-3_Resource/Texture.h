/*============================================================
*	@file	 : Texture.h
*	@brief	 : テクスチャリソース
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
*	@brief	: テクスチャリソース
*============================================================*/
class Texture
{
	friend class TextureManager;
	friend class AssimpLoader;

	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

protected:
	// サイズ
	DirectX::XMUINT2 mSize{};

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _mSRV{ nullptr };

public:
	void Bind(UINT slot = 0) const;

	const DirectX::XMUINT2& GetSize() const { return mSize; }
	const UINT& GetWidth() const { return mSize.x; }
	const UINT& GetHeight() const { return mSize.y; }
	ID3D11ShaderResourceView* GetSRV() { return _mSRV.Get(); }
};