/*============================================================
*	@file	 : field.h
*	@brief	 : 3Dポリゴン表示
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/28
*	@Updated : 2026/06/02
*============================================================*/
#ifndef FIELD_H
#define FIELD_H

#include "gameobject.h"

/*============================================================
*	@class	: Field
*	@brief	: フィールド
*============================================================*/
class Field : public GameObject
{
private:
	ID3D11Buffer* pVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* pVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* pVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* pPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* pTexture{}; // テクスチャ

public:
	Field() = default;
	Field(const wchar_t* pFileName);
	
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // FIELD_H