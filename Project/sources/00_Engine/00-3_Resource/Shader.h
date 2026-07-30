/*============================================================
*	@file	 : Shader.h
*	@brief	 : シェーダー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/07/30
*============================================================*/
#pragma once

#include <d3d11.h>
#include <wrl/client.h>

/*--------------------------------------------------
	前方宣言
----------------------------------------------------*/
class ShaderManager;

/*============================================================
*	@class	: Shader
*	@brief	: シェーダー・レイアウトセット
*============================================================*/
class Shader
{
	friend ShaderManager;
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> _mVertexShader{};
	Microsoft::WRL::ComPtr<ID3D11PixelShader> _mPixelShader{};
	Microsoft::WRL::ComPtr<ID3D11InputLayout> _mLayout{};

public:
	// ゲッター
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetVertexShader() const { return _mVertexShader; }
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetPixelShader() const { return _mPixelShader; }
	Microsoft::WRL::ComPtr<ID3D11InputLayout> GetLayout() const { return _mLayout; }
};