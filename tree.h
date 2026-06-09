/*============================================================
*	@file	 : tree.h
*	@brief	 : 木のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/06/02
*============================================================*/
#ifndef TREE_H
#define TREE_H

#include "gameobject.h"

class Tree : public GameObject
{
private:
	ID3D11Buffer* pVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* pVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* pVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* pPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* pTexture{}; // テクスチャ

public:
	Tree() = default;
	Tree(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // TREE_H