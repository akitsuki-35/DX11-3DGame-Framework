/*============================================================
*	@file	 : Drawable.h
*	@brief	 : 描画コンポーネント基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/27
*	@updated : 2026/07/27
*============================================================*/
#pragma once

#include "Component.h"
#include "Mesh.h"
#include "ShaderLoader.h"
#include "GraphicsTypes.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include <DirectXMath.h>

// 描画レイヤー
enum class Layer : uint8_t
{
	World,
	Alpha,
	UI,

	Count
};

/*============================================================
*	@class	: Drawable
*	@brief	: 描画コンポーネント基底クラス
*============================================================*/
class Drawable : public Component
{
	// 描画ソート用情報
	struct SORTKEY
	{
		Layer layer{};
		float Zdepth{};

		bool operator<(const SORTKEY& key) const
		{
			if (layer != key.layer)
				return layer < key.layer;

			return Zdepth > key.Zdepth;
		}
	};

protected:
	Mesh mMesh{}; // メッシュ
	Element::MATERIAL mMaterial{}; // マテリアル
	Shader* _mShader{ nullptr }; // シェーダー
	SORTKEY mSortKey{}; // ソート用情報

	void Bind() const {
		auto context = D3D11::DeviceManager::getInstance().GetContext();

		// 入力レイアウト設定
		context->IASetInputLayout(_mShader->GetLayout().Get());

		// シェーダー設定
		context->VSSetShader(_mShader->GetVertexShader().Get(), nullptr, 0);
		context->PSSetShader(_mShader->GetPixelShader().Get(), nullptr, 0);
	}
public:
	// 描画
	virtual void Draw() const {
		Bind();

		D3D11::BufferManager::getInstance().SetWorldMatrix(GetWorldMatrix());
		D3D11::BufferManager::getInstance().SetMaterial(mMaterial);

		mMesh.Bind();
		mMesh.Draw();
	}

	// ワールド行列取得
	virtual DirectX::XMMATRIX GetWorldMatrix() const = 0;

	// ゲッター
	Mesh GetMesh() const { return mMesh; }
	Element::MATERIAL GetMaterial() const { return mMaterial; }
	Shader* GetShader() const { return _mShader; }
};