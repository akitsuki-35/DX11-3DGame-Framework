/*============================================================
*	@file	 : SpriteDrawable.h
*	@brief	 : 板ポリゴン描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/07/27
*============================================================*/
#pragma once

#include "Drawable.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "ShaderManager.h"

/*============================================================
*	@class	: SpriteDrawable
*	@brief	: 板ポリゴン描画
*============================================================*/
class SpriteDrawable : public Drawable
{
private:
	Mesh mMesh{}; // メッシュ
	Element::MATERIAL mMaterial{}; // マテリアル
	Texture* _mTexture{ nullptr }; // テクスチャ

public:
	SpriteDrawable(GameObject* owner)
		: Drawable(owner){
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::World;
	};

	~SpriteDrawable() override = default;

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
	void LoadTexture(const char* fileName) {
		_mTexture = TextureManager::getInstance().Load(fileName);
	}

	// ゲッター
	Mesh& GetMesh() { return mMesh; }
	Element::MATERIAL GetMaterial() const { return mMaterial; }
	Texture* GetTexture() { return _mTexture; }
};