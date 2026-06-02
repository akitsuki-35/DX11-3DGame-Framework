/*============================================================
*	@file	 : player.h
*	@brief	 : プレイヤー
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/05/19
*	@Updated : 2026/06/02
*============================================================*/
#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"

/*============================================================
*	@class	: Player
*	@brief	: プレイヤー
*============================================================*/
class Player : public GameObject
{
private:
	Vector3 velocity{ 0.0f, 0.0f, 0.0f };
	Vector3 accel{ 0.0f, 0.0f, 0.0f };
	float rotationVel{ 0.0f };

	ID3D11InputLayout* pVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* pVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* pPixelShader{}; // ピクセルシェーダー

public:
	Player() = default;
	//Player(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // PLAYER_H