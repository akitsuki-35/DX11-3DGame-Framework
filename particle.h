/*============================================================
*	@file	 : particle.h
*	@brief	 : パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/18
*	@updated : 2026/06/18
*============================================================*/
#ifndef PARTICLE_H
#define PARTICLE_H

#include "gameobject.h"

/*============================================================
*	@class	: Particle
*	@brief	: パーティクルシステム
*============================================================*/
class Particle : public GameObject
{
private:
	// パーティクル構造体
	struct PARTICLE
	{
		Vector3 position;
		Vector3 velocity;
		Vector3 scale{ 1.0f, 1.0f, 1.0f };
		int life;
		bool enable;
	};

	static constexpr int PARTICLE_MAX{ 10000 };
	PARTICLE mParticle[PARTICLE_MAX]{};
	XMFLOAT4 mColor{ 1.0f, 1.0f, 0.6f, 1.0f };

	ID3D11Buffer* _mVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ

public:
	Particle() = default;
	Particle(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // PARTICLE_H