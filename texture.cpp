/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	テクスチャ管理[texture.cpp]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/13
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
using namespace DirectX;
#include <string>
#include <DirectXTex.h>

Texture::Texture(const wchar_t* pFileName, bool isMipMap)
	: fileName(pFileName)
{
	//テクスチャからのファイルの読み込み
	TexMetadata metaData;
	ScratchImage image;

	//画像ファイルの読み込み
	LoadFromWICFile(pFileName, WIC_FLAGS_NONE, &metaData, image);

	//画像ファイルのサイズを取得
	imageSize.x = static_cast<unsigned int>(metaData.width);
	imageSize.y = static_cast<unsigned int>(metaData.height);

	if (isMipMap)
	{
		//ミップマップを作成する
		ScratchImage mipChain;
		GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), TEX_FILTER_DEFAULT, 0, mipChain);
		image = std::move(mipChain);
		metaData = image.GetMetadata();
	}

	//シェーダーリソースビューの生成
	HRESULT hr = CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metaData, &pTexture);

	if (FAILED(hr))
	{
		MessageBox(nullptr, "テクスチャの読み込みに失敗しました", "エラー", MB_OK);
		return;
	}

	//ファイル名を保存
	fileName = pFileName;
}

Texture::~Texture()
{
	pTexture->Release();
}

void Texture::Draw(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size, const DirectX::XMFLOAT4& color)
{
	SpriteDraw(this, position, size, color);
}

void Texture::Draw(const DirectX::XMFLOAT2& position, const float& size, const DirectX::XMFLOAT4& color)
{
	SpriteDraw(this, position, size, color);
}

void Texture::SetTexture()
{
	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &pTexture);
}

SpriteSheet::SpriteSheet(const wchar_t* pFileName, const DirectX::XMUINT2& patternMatrix, bool isMipMap)
	: Texture(pFileName, isMipMap), patternMatrix(patternMatrix)
{
	patternMax = patternMatrix.x * patternMatrix.y;
	patternSize.x = imageSize.x / patternMatrix.x;
	patternSize.y = imageSize.y / patternMatrix.y;
}

void SpriteSheet::Draw(const DirectX::XMFLOAT2& position, const DirectX::XMUINT2& patternNum, const DirectX::XMFLOAT2& size, const DirectX::XMFLOAT4& color)
{
	SpriteDraw(this, position, patternNum, size, color);
}

void SpriteSheet::Draw(const DirectX::XMFLOAT2& position, const DirectX::XMUINT2& patternNum, const float& size, const DirectX::XMFLOAT4& color)
{
	SpriteDraw(this, position, patternNum, size, color);
}

void SpriteSheet::Draw(const DirectX::XMFLOAT2& position, const int& patternNum, const DirectX::XMFLOAT2& size, const DirectX::XMFLOAT4& color)
{
	SpriteDraw(this, position, patternNum, size, color);
}

void SpriteSheet::Draw(const DirectX::XMFLOAT2& position, const int& patternNum, const float& size, const DirectX::XMFLOAT4& color)
{
	SpriteDraw(this, position, patternNum, size, color);
}
