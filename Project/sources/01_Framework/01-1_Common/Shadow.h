/*============================================================
*	@file	 : Shadow.h
*	@brief	 : 
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 20XX/XX/XX
*	@updated : 20XX/XX/XX
*============================================================*/
#pragma once

#include "gameobject.h"

/*============================================================
*	@class	: Shadow
*	@brief	: フィールド
*============================================================*/
class Shadow: public GameObject
{
private:
	ID3D11Buffer* _mVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ

public:
	Shadow() = default;
	Shadow(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};