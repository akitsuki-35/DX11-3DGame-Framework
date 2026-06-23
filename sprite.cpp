/*============================================================
*	@file	 : sprite.cpp
*	@brief	 : スプライト描画
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/01
*	@updated : 2026/06/02
*============================================================*/
#include "sprite.h"
#include "shader2d.h"
#include "texture.h"
#include "debug_ostream.h"
using namespace DirectX;

/*------------------------------------------------------------
	メンバ変数定義
------------------------------------------------------------*/
ID3D11Buffer* Sprite::pVertexBuffer{ nullptr };

/*------------------------------------------------------------
	頂点構造体
------------------------------------------------------------*/
struct Vertex
{
	XMFLOAT3 position; // 頂点座標
	XMFLOAT4 color;	   // 色
	XMFLOAT2 texCoord; // UV座標
};

const void Sprite::Initialize()
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Direct3DGetDevice()->CreateBuffer(&bd, NULL, &pVertexBuffer);
}

const void Sprite::Finalize()
{
	SAFE_RELEASE(pVertexBuffer);
}

/*------------------------------------------------------------
	テクスチャ描画
------------------------------------------------------------*/
const void Sprite::Draw(Texture* pTexture, const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& size, const float& rotate, const DirectX::XMFLOAT4& color)
{
	pTexture->SetTexture();

	// シェーダーを描画パイプラインに設定
	Shader2DBeginLinear();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	Direct3DGetDeviceContext()->Map(pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	const float SCREEN_WIDTH = static_cast<float>(Direct3DGetBackBufferWidth());
	const float SCREEN_HEIGHT = static_cast<float>(Direct3DGetBackBufferHeight());

	//四角形の描画
	v[0].position = { position.x, position.y, 0.0f };
	v[1].position = { position.x + size.x, position.y, 0.0f };
	v[2].position = { position.x, position.y + size.y, 0.0f };
	v[3].position = { position.x + size.x, position.y + size.y, 0.0f };

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		v[i].color = color;
	}

	// テクスチャ座標設定
	v[0].texCoord = { 0.0f, 0.0f };
	v[1].texCoord = { 1.0f, 0.0f };
	v[2].texCoord = { 0.0f, 1.0f };
	v[3].texCoord = { 1.0f, 1.0f };

	// 頂点バッファのロックを解除
	Direct3DGetDeviceContext()->Unmap(pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Direct3DGetDeviceContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	// 中心座標を算出
	float centerX = position.x + size.x / 2;
	float centerY = position.y + size.y / 2;

	// 中心座標に平行移動→回転→元の座標に平行移動
	XMMATRIX transToCenter = XMMatrixTranslation(-centerX, -centerY, 0.0f);
	XMMATRIX rot = XMMatrixRotationZ(-rotate);
	XMMATRIX transBack = XMMatrixTranslation(centerX, centerY, 0.0f);

	// 頂点シェーダーにワールド変換行列を設定
	Shader2DSetWorldMatrix(transToCenter * rot * transBack);

	// 頂点シェーダーにプロジェクション変換行列を設定
	Shader2DSetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	Shader2DSetColor({ 1.0f,1.0f,1.0f,1.0f });

	// プリミティブトポロジ設定
	Direct3DGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画命令発行
	Direct3DGetDeviceContext()->Draw(NUM_VERTEX, 0);
}

/*------------------------------------------------------------
	スプライト描画
------------------------------------------------------------*/
const void Sprite::Draw(SpriteSheet* pSpriteSheet, const int& patternNum, const DirectX::XMFLOAT2& position, DirectX::XMFLOAT2 size, const float& rotate, const DirectX::XMFLOAT4& color)
{
	pSpriteSheet->SetTexture();

	// シェーダーを描画パイプラインに設定
	Shader2DBeginPoint();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	Direct3DGetDeviceContext()->Map(pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	const float SCREEN_WIDTH = static_cast<float>(Direct3DGetBackBufferWidth());
	const float SCREEN_HEIGHT = static_cast<float>(Direct3DGetBackBufferHeight());

	// UVパターンのサイズ取得
	float patternWidth = static_cast<float>(pSpriteSheet->GetPatternSize().x);
	float patternHeight = static_cast<float>(pSpriteSheet->GetPatternSize().y);

	//四角形の描画
	v[0].position = { position.x, position.y, 0.0f };
	v[1].position = { position.x + size.x, position.y, 0.0f };
	v[2].position = { position.x, position.y + size.y, 0.0f };
	v[3].position = { position.x + size.x, position.y + size.y, 0.0f };

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		v[i].color = color;
	}

	// テクスチャのサイズ取得
	float texWidth = static_cast<float>(pSpriteSheet->GetSize().x);
	float texHeight = static_cast<float>(pSpriteSheet->GetSize().y);

	float offsetX = patternWidth * (patternNum % pSpriteSheet->GetPatternMatrix().x);
	float offsetY = patternHeight * (patternNum / pSpriteSheet->GetPatternMatrix().x);

	float u0 = offsetX / texWidth;
	float v0 = offsetY / texHeight;
	float u1 = (offsetX + patternWidth) / texWidth;
	float v1 = (offsetY + patternHeight) / texHeight;

	// テクスチャ座標設定
	v[0].texCoord = { u0, v0 };
	v[1].texCoord = { u1, v0 };
	v[2].texCoord = { u0, v1 };
	v[3].texCoord = { u1, v1 };

	// 頂点バッファのロックを解除
	Direct3DGetDeviceContext()->Unmap(pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Direct3DGetDeviceContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	// 中心座標を算出
	float centerX = position.x + size.x / 2;
	float centerY = position.y + size.y / 2;

	// 中心座標に平行移動→回転→元の座標に平行移動
	XMMATRIX transToCenter = XMMatrixTranslation(-centerX, -centerY, 0.0f);
	XMMATRIX rot = XMMatrixRotationZ(-rotate);
	XMMATRIX transBack = XMMatrixTranslation(centerX, centerY, 0.0f);

	// 頂点シェーダーにワールド変換行列を設定
	Shader2DSetWorldMatrix(transToCenter * rot * transBack);

	// 頂点シェーダーにプロジェクション変換行列を設定
	Shader2DSetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	Shader2DSetColor({ 1.0f,1.0f,1.0f,1.0f });

	// プリミティブトポロジ設定
	Direct3DGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画命令発行
	Direct3DGetDeviceContext()->Draw(NUM_VERTEX, 0);
}