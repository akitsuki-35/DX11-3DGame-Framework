/*============================================================
*	@file	 : bullet.h
*	@brief	 : 弾
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/06/02
*============================================================*/
#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"

/*============================================================
*	@class	: Bullet
*	@brief	: 弾
*============================================================*/
class Bullet : public GameObject
{
private:
	Vector3 velocity{ 0.0f, 0.0f, 0.0f };
	Vector3 accel{ 0.0f, 0.0f, 0.0f };
	float lifeTime{ 2.0f };

	ID3D11InputLayout* pVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* pVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* pPixelShader{}; // ピクセルシェーダー

public:
	Bullet() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;

	void SetVelocity(const Vector3& newVelocity) { velocity = newVelocity; }
};

#endif // BULLET_H