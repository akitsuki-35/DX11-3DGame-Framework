/*============================================================
*	@file	 : UIRenderer.h
*	@brief	 : UI描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/12
*	@updated : 2026/08/12
*============================================================*/
#pragma once

#include "Renderer.h"
#include "UICanvas.h"
#include "GameObject.h"
#include "BufferManager.h"
#include "TextureManager.h"
#include "DeviceManager.h"
#include "D3D11Config.h"

/*============================================================
*	@class	: UIRenderer
*	@brief	: UI描画コンポーネント
*============================================================*/
class UIRenderer : public Renderer
{
private:
	// キャンバス
	UICanvas mCanvas{};

	// マテリアル
	Element::MATERIAL mMaterial{};

	// テクスチャ
	Texture* _mTexture{ nullptr };

public:
	UIRenderer(GameObject* owner)
		: Renderer(owner) {
		// 2Dレイヤーに描画
		mSortKey.layer = Layer::UI;
	};

	~UIRenderer() override = default;

	void Draw() const override {
		// 深度ステート無効
		D3D11::DeviceManager::getInstance().SetDepthStencilState(D3D11::RenderState::Depth::Disable);

		Bind();

		D3D11::BufferManager::getInstance().Set2DMatrix();
		D3D11::BufferManager::getInstance().SetWorldMatrix(GetWorldMatrix());

		// マテリアル設定
		Element::MATERIAL material{};
		material.Diffuse = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
		material.TextureEnable = static_cast<bool>(_mTexture != nullptr);
		D3D11::BufferManager::getInstance().SetMaterial(material);

		mCanvas.Bind();

		if (material.TextureEnable) {
			_mTexture->Bind();
		}

		mCanvas.Draw();

		// 深度ステート有効
		D3D11::DeviceManager::getInstance().SetDepthStencilState(D3D11::RenderState::Depth::Enable);
	}

private:
	// ワールド行列取得
	DirectX::XMMATRIX GetWorldMatrix() const override {
		return _mOwner->GetTransform().GetWorldMatrix();
	}

public:
	// テクスチャ読み込み
	UIRenderer* LoadTexture(const char* fileName) {
		_mTexture = TextureManager::getInstance().Load(fileName);
		return this;
	}

	// ゲッター
	UICanvas& GetCanvas() { return mCanvas; }
	Element::MATERIAL GetMaterial() const { return mMaterial; }
	Texture* GetTexture() { return _mTexture; }
};