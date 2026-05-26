/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	3Dポリゴン表示[field.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/28
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef FIELD_H
#define FIELD_H

#include "gameobject.h"

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