/*============================================================
*	@file	 : transform.h
*	@brief	 : トランスフォーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/06/02
*============================================================*/
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include "vector3.h"

/*============================================================
*	@class	: Transform
*	@brief	: トランスフォームコンポーネント
*============================================================*/
class Transform : public Component
{
private:
	Vector3 position{ 0.0f, 0.0f, 0.0f };
	Vector3 rotation{ 0.0f, 0.0f, 0.0f };
	Vector3 scale{ 1.0f, 1.0f, 1.0f };

	ID3D11InputLayout* pVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* pVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* pPixelShader{}; // ピクセルシェーダー

public:
	Transform(Vector3 position, Vector3 rotation = { 0.0f, 0.0f, 0.0f }, Vector3 scale = { 1.0f, 1.0f, 1.0f })
		: position(position), rotation(rotation), scale(scale) {}

	using Component::Component;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};

#endif // TRANSFORM_H