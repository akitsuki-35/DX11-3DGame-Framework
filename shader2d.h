/*============================================================
*	@file	 : shader.h
*	@brief	 : 2D用シェーダー
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/01
*	@Updated : 2026/06/02
*============================================================*/
#ifndef SHADER_H
#define	SHADER_H

#include <DirectXMath.h>

bool Shader2DInitialize();
void Shader2DFinalize();

void Shader2DSetProjectionMatrix(const DirectX::XMMATRIX& matrix);
void Shader2DSetWorldMatrix(const DirectX::XMMATRIX& matrix);
void Shader2DSetColor(const DirectX::XMFLOAT4& color);

void Shader2DBeginLinear();
void Shader2DBeginPoint();

#endif // SHADER_H
