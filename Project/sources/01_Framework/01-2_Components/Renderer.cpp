/*============================================================
*	@file	 : Renderer.cpp
*	@brief	 : 描画コンポーネント基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/09/16
*============================================================*/
#include "Renderer.h"
#include "Vector3.h"
#include "GameObject.h"
#include "DeviceManager.h"
#include "ShaderManager.h"
#include "D3D11Config.h"

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
	// シェーダー読み込み
	_mShader = ShaderManager::getInstance().Get(keyName);
	return this;
}

Renderer* Renderer::SetBlendState(const Blend& state)
{
	// ブレンドステート設定
	mBlendState = state;
	return this;
}

Renderer* Renderer::SetLayer(const Layer& layer)
{
	// レイヤー設定
	mSortKey.layer = layer;
	return this;
}

void Renderer::CalcCameraZ(Vector3 cameraPosition, Vector3 cameraForward) const
{
	// カメラからの距離を計算
	Vector3 dir = _mOwner->GetTransform().GetPosition() - cameraPosition;
	mSortKey.Zdepth = Vector3::Dot(dir, cameraForward);
}

Renderer* Renderer::SetColor(const DirectX::XMFLOAT4 color)
{
	// カラー設定
	mColor = color;
	return this;
}

Renderer* Renderer::SetParameter(const DirectX::XMFLOAT4 parameter)
{
	// 汎用パラメータ設定
	mParameter = parameter;
	return this;
}

void Renderer::Begin() const
{
	// ブレンドステートのセット
	// 描画関数の先頭で呼び出し

	switch (mBlendState)
	{
	case Blend::Default:
		D3D11::DeviceManager::getInstance().SetBlendState(D3D11::RenderState::Blend::Default);
		break;

	case Blend::Add:
		D3D11::DeviceManager::getInstance().SetBlendState(D3D11::RenderState::Blend::Add);
		break;

	case Blend::Multiply:
		D3D11::DeviceManager::getInstance().SetBlendState(D3D11::RenderState::Blend::Multiply);
		break;

	default:
		break;
	}
}

void Renderer::End() const
{
	// ブレンドステートをデフォルトに戻す
	// 描画関数の末尾で呼び出し

	D3D11::DeviceManager::getInstance().SetBlendState(D3D11::RenderState::Blend::Default);
}