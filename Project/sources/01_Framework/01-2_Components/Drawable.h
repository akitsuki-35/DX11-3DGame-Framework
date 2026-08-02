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
#include "ShaderManager.h"
#include "GraphicsTypes.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include <sstream>
#include <DirectXMath.h>

// 描画レイヤー
enum class Layer : uint8_t
{
	World,
	Alpha,
	UI,

	Count
};

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

/*============================================================
*	@class	: Drawable
*	@brief	: 描画コンポーネント基底クラス
*============================================================*/
class Drawable : public Component
{
protected:
	Shader* _mShader{ nullptr }; // シェーダー
	SORTKEY mSortKey{}; // ソート用情報

	void Bind() const {
		auto context = D3D11::DeviceManager::getInstance().GetContext();

		// 入力レイアウト設定
		context->IASetInputLayout(_mShader->GetLayout());

		// シェーダー設定
		context->VSSetShader(_mShader->GetVertexShader(), nullptr, 0);
		context->PSSetShader(_mShader->GetPixelShader(), nullptr, 0);
	}

public:
	Drawable(GameObject* owner)
		: Component(owner){}

	// 描画
	virtual void Draw() const = 0;

	// シェーダー読み込み
	void LoadShader(const std::string& keyName) {
		_mShader = ShaderManager::getInstance().Get(keyName);
	}

	// ゲッター
	Shader* GetShader() const { return _mShader; }
	SORTKEY& GetSortKey() { return mSortKey; }

private:
	// ワールド行列取得
	virtual DirectX::XMMATRIX GetWorldMatrix() const = 0;
};