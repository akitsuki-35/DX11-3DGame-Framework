/*============================================================
*	@file	 : polygon2d.h
*	@brief	 : 2Dポリゴン表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/06/02
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
	ID3D11Buffer* _mVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ

public:
	Polygon2D() = default;
	Polygon2D(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // POLYGON2D_H