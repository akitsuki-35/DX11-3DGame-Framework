/*============================================================
*	@file	 : polygon2d.h
*	@brief	 : 2Dポリゴン表示
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/28
*	@Updated : 2026/06/02
*============================================================*/
#ifndef POLYGON2D_H
#define POLYGON2D_H

#include "gameobject.h"

/*============================================================
*	@class	: Polygon2D
*	@brief	: 2Dポリゴン
*============================================================*/
class Polygon2D : public GameObject
{
private:
	ID3D11Buffer* pVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* pVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* pVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* pPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* pTexture{}; // テクスチャ

public:
	Polygon2D() = default;
	Polygon2D(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // POLYGON2D_H