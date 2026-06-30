/*============================================================
*	@file	 : score.h
*	@brief	 : スコア表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/30
*	@updated : 2026/06/30
*============================================================*/
#ifndef SCORE_H
#define SCORE_H

#include "gameobject.h"

/*============================================================
*	@class	: Score
*	@brief	: スコア
*============================================================*/
class Score : public GameObject
{
private:
	ID3D11Buffer* _mVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ

	int mValue{};
	static constexpr int DIGIT{ 2 };

public:
	Score() = default;
	Score(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;

	void Add(int value) { mValue += value; }
};

#endif // SCORE_H