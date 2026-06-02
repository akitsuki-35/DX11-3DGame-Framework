/*============================================================
*	@file	 : texture.cpp
*	@brief	 : テクスチャ管理
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/13
*	@Updated : 2026/06/02
*============================================================*/
#include "texture.h"
#include "sprite.h"
#include "direct3d.h"
using namespace DirectX;
#include <string>
#include <DirectXTex.h>

Texture::Texture(const wchar_t* pFileName, const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size, const float& rotate, const DirectX::XMFLOAT4& color, bool isMipMap)
	: position(position), drawSize(size), rotate(rotate), color(color)
{
	//テクスチャからのファイルの読み込み
	TexMetadata metaData;
	ScratchImage image;

	//画像ファイルの読み込み
	LoadFromWICFile(pFileName, WIC_FLAGS_NONE, &metaData, image);

	//画像ファイルのサイズを取得
	originalSize.x = static_cast<unsigned int>(metaData.width);
	originalSize.y = static_cast<unsigned int>(metaData.height);

	if (drawSize.x == 0.0f && drawSize.y == 0.0f) {
		drawSize.x = static_cast<float>(originalSize.x);
		drawSize.y = static_cast<float>(originalSize.y);
	}

	if (isMipMap)
	{
		//ミップマップを作成する
		ScratchImage mipChain;
		GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), TEX_FILTER_DEFAULT, 0, mipChain);
		image = std::move(mipChain);
		metaData = image.GetMetadata();
	}

	//シェーダーリソースビューの生成
	HRESULT hr = CreateShaderResourceView(Direct3DGetDevice(), image.GetImages(), image.GetImageCount(),
		metaData, &pShaderResourceView);

	if (FAILED(hr))
	{
		MessageBox(nullptr, "テクスチャの読み込みに失敗しました", "エラー", MB_OK);
		return;
	}
}

Texture::~Texture()
{
	SAFE_RELEASE(pShaderResourceView);
}

void Texture::Draw()
{
	Sprite::GetInstance().Draw(this, position, drawSize, rotate, color);
}

void Texture::SetTexture()
{
	// テクスチャ設定
	Direct3DGetDeviceContext()->PSSetShaderResources(0, 1, &pShaderResourceView);
}

SpriteSheet::SpriteSheet(const wchar_t* pFileName, const DirectX::XMUINT2& patternMatrix, const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size, const float& rotate, const DirectX::XMFLOAT4& color, bool isMipMap)
	:Texture(pFileName, position, size, rotate, color, isMipMap), patternMatrix(patternMatrix)
{
	// 総パターン数とパターンサイズをセット
	patternMax = patternMatrix.x * patternMatrix.y;
	patternSize.x = originalSize.x / patternMatrix.x;
	patternSize.y = originalSize.y / patternMatrix.y;
}

void SpriteSheet::Draw()
{
	Sprite::GetInstance().Draw(this, CurrentPattern, position, drawSize, rotate, color);
}
