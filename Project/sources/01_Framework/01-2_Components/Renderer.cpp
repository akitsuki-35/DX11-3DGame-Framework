/*============================================================
*	@file	 : Renderer.cpp
*	@brief	 : 描画コンポーネント基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/08/13
*============================================================*/
#include "Renderer.h"
#include "DeviceManager.h"
#include "ShaderManager.h"

void Renderer::Bind() const
{
	auto context = D3D11::DeviceManager::getInstance().GetContext();

	// 入力レイアウト設定
	context->IASetInputLayout(_mShader->GetLayout());

	// シェーダー設定
	context->VSSetShader(_mShader->GetVertexShader(), nullptr, 0);
	context->PSSetShader(_mShader->GetPixelShader(), nullptr, 0);
}

Renderer* Renderer::LoadShader(const std::string& keyName)
{
	_mShader = ShaderManager::getInstance().Get(keyName);
	return this;
}
