/*============================================================
*	@file	 : SpriteRenderer.h
*	@brief	 : 板ポリゴン描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "Renderer.h"
#include "Mesh.h"
#include "GameObject.h"
#include "BufferManager.h"
#include "TextureManager.h"

/*============================================================
*	@class	: SpriteRenderer
*	@brief	: 板ポリゴン描画
*============================================================*/
class SpriteRenderer : public Renderer
{
private:
	// メッシュ
	Mesh mMesh{};

	// マテリアル
	Element::MATERIAL mMaterial{};

	// テクスチャ
	Texture* _mTexture{ nullptr };

public:
	SpriteRenderer(GameObject* owner)
		: Renderer(owner){
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::World;
	};

	~SpriteRenderer() override = default;

	void Draw() const override{
		Bind();

		D3D11::BufferManager::getInstance().SetWorldMatrix(GetWorldMatrix());

		// マテリアル設定
		Element::MATERIAL material{};
		material.Diffuse = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
		material.TextureEnable = static_cast<bool>(_mTexture != nullptr);
		D3D11::BufferManager::getInstance().SetMaterial(material);

		mMesh.Bind();

		if (material.TextureEnable) {
			_mTexture->Bind();
		}

		mMesh.Draw();
	}

private:
	// ワールド行列取得
	DirectX::XMMATRIX GetWorldMatrix() const override {
		return _mOwner->GetTransform().GetWorldMatrix();
	}

public:
	// テクスチャ読み込み
	SpriteRenderer* LoadTexture(const char* fileName) {
		_mTexture = TextureManager::getInstance().Load(fileName);
		return this;
	}

	// ゲッター
	Mesh& GetMesh() { return mMesh; }
	Element::MATERIAL GetMaterial() const { return mMaterial; }
	Texture* GetTexture() { return _mTexture; }
};