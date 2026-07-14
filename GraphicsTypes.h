/*============================================================
*	@file	 : GraphicsTypes.h 
*	@brief	 : 構造体定義
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/14
*	@updated : 2026/07/14
*============================================================*/
#pragma once

#include <DirectXMath.h>

/*============================================================
*	@namespace	: Element 
*	@brief		: 汎用構造体定義
*============================================================*/
namespace Element {

	/*--------------------------------------------------
		頂点構造体
	----------------------------------------------------*/
	struct VERTEX3D
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT4 Diffuse;
		DirectX::XMFLOAT2 TexCoord;
	};

	/*--------------------------------------------------
		マテリアル構造体
	----------------------------------------------------*/
	struct MATERIAL
	{
		DirectX::XMFLOAT4 Ambient;
		DirectX::XMFLOAT4 Diffuse;
		DirectX::XMFLOAT4 Specular;
		DirectX::XMFLOAT4 Emission;
		float Shininess;
		bool TextureEnable;
		float Dummy[2];
	};

	/*--------------------------------------------------
		ライト構造体
	----------------------------------------------------*/
	struct LIGHT
	{
		bool Enable;
		bool Dummy[3];
		DirectX::XMFLOAT4 Direction;
		DirectX::XMFLOAT4 Diffuse;
		DirectX::XMFLOAT4 Ambient;
	};
}