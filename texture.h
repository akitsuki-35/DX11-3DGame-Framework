/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	テクスチャ管理[texture.h]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/13
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>
#include <string>
#include <DirectXMath.h>

class Animation;

/*----------------------------------------------------------------------------------------------------------
	テクスチャクラス
----------------------------------------------------------------------------------------------------------*/
class Texture
{
protected:
	std::wstring fileName{};
	DirectX::XMUINT2 imageSize{};
	ID3D11ShaderResourceView* pTexture{ nullptr };

public:
	Texture(const wchar_t* pFileName, bool isMipMap = true);
	virtual ~Texture();

	// 描画
	// サイズ指定方式でオーバーロード
	void Draw(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size, 
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	void Draw(const DirectX::XMFLOAT2& position, const float& size = 1.0f, 
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	virtual void SetTexture();
	const DirectX::XMUINT2& GetSize() { return imageSize; }
};

/*----------------------------------------------------------------------------------------------------------
	スプライトシートクラス（テクスチャを継承）
----------------------------------------------------------------------------------------------------------*/
class SpriteSheet : public Texture
{
private:
	int patternMax{};
	DirectX::XMUINT2 patternMatrix{};
	DirectX::XMUINT2 patternSize{};

public:
	SpriteSheet(const wchar_t* pFileName, const DirectX::XMUINT2& patternMatrix, bool isMipMap = true);

	// 描画
	// サイズ指定方式でオーバーロード

	// x, y番号でパターン指定
	void Draw(const DirectX::XMFLOAT2& position, const DirectX::XMUINT2& patternNum, const DirectX::XMFLOAT2& size,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	void Draw(const DirectX::XMFLOAT2& position, const DirectX::XMUINT2& patternNum, const float& size = 1.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// パターン番号でパターン指定
	void Draw(const DirectX::XMFLOAT2& position, const int& patternNum, const DirectX::XMFLOAT2& size,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	void Draw(const DirectX::XMFLOAT2& position, const int& patternNum, const float& size = 1.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	const int& GetPatternMax() { return patternMax; }
	const DirectX::XMUINT2& GetPatternMatrix() { return patternMatrix; }
	const DirectX::XMUINT2& GetPatternSize() { return patternSize; }
};

#endif // TEXTURE_H

