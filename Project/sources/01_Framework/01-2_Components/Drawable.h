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
#include "Texture.h"
#include "Shader.h"
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
	Mesh mMesh{}; // メッシュ
	Element::MATERIAL mMaterial{}; // マテリアル
	Shader* _mShader{ nullptr }; // シェーダー
	//Texture* _mTexture{ nullptr }; // テクスチャ
	Texture _mTexture{}; // テクスチャ

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
	Drawable(GameObject* owner)
		: Component(owner){}

	// 描画
	virtual void Draw() const {

		Bind();

		D3D11::BufferManager::getInstance().SetWorldMatrix(GetWorldMatrix());

		// マテリアル設定
		Element::MATERIAL material{};
		material.Diffuse = XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
		//if (_mTexture)material.TextureEnable = true;
		//else material.TextureEnable = false;
		material.TextureEnable = true;
		D3D11::BufferManager::getInstance().SetMaterial(material);

		mMesh.Bind();
		_mTexture.Bind();
		mMesh.Draw();
	}

	// ワールド行列取得
	virtual DirectX::XMMATRIX GetWorldMatrix() const = 0;

	// シェーダー読み込み
	void LoadShader(const std::string& keyName) {
		_mShader = ShaderManager::getInstance().Get(keyName);
	}

	// ゲッター
	Mesh& GetMesh() { return mMesh; }
	Element::MATERIAL GetMaterial() const { return mMaterial; }
	Shader* GetShader() const { return _mShader; }
	Texture& GetTexture() { return _mTexture; }
	SORTKEY& GetSortKey() { return mSortKey; }
};