/*============================================================
*	@file	 : PolygonDrawable.h
*	@brief	 : 板ポリゴン描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/07/24
*============================================================*/
#pragma once

#include "Component.h"
#include <d3d11.h>

/*============================================================
*	@class	: PolygonDrawable
*	@brief	: 板ポリゴン描画
*============================================================*/
class PolygonDrawable : public Component
{
private:
	ID3D11Buffer* _mVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ
};