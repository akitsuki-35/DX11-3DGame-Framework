/*============================================================
*	@file	 : ModelDrawable.h
*	@brief	 : モデル描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/31
*	@updated : 2026/07/31
*============================================================*/
#pragma once

#include "Drawable.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Utility.h"

/*--------------------------------------------------
	前方宣言
----------------------------------------------------*/
class Texture;

/*============================================================
*	@class	: ModelDrawable
*	@brief	: モデル描画
*============================================================*/
class ModelDrawable : public Drawable
{
	// テクスチャ
	struct ModelTextures
	{
		Texture* Diffuse{};
		Texture* Normal{};
		Texture* Roughness{};
		Texture* Metalness{};
		Texture* Rump{};
	};

public:
	// テクスチャタイプ
	enum class TextureType
	{
		Diffuse,
		Normal,
		Roughness,
		Metalness,
		Ramp
	};

private:
	Model* _mModel{};
	ModelTextures mTextures{};
	
	// ディレクトリ(テクスチャ検索用)
	std::filesystem::path mDirectory{};

public:
	ModelDrawable(GameObject* owner)
		: Drawable(owner) {
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::World;
	};

	~ModelDrawable() override = default;

	void Draw() const override;

private:
	// ワールド行列取得
	DirectX::XMMATRIX GetWorldMatrix() const override {
		return _mOwner->GetTransform().GetWorldMatrix();
	}

public:
	// モデル読み込み
	ModelDrawable* LoadModel(const char* fileName) {
		_mModel = ModelManager::getInstance().Load(fileName);

		// モデルディレクトリ取得
		//mDirectory = fileName;
		//mDirectory = mDirectory.parent_path();

		mDirectory = Utility::File::getDirectoryPath(fileName);

		return this;
	}

	ModelDrawable* LoadTexture(std::string textureName, TextureType type) {
		switch (type)
		{
		case TextureType::Diffuse:
			mTextures.Diffuse = TextureManager::getInstance().Load(
				converttoTexturePath(textureName).c_str());
			break;
		
		case TextureType::Normal:
			mTextures.Normal = TextureManager::getInstance().Load(
				converttoTexturePath(textureName).c_str());
			break;
		
		case TextureType::Roughness:
			mTextures.Roughness = TextureManager::getInstance().Load(
				converttoTexturePath(textureName).c_str());
			break;

		case TextureType::Metalness:
			mTextures.Metalness = TextureManager::getInstance().Load(
				converttoTexturePath(textureName).c_str());
			break;

		case TextureType::Ramp:
			mTextures.Rump = TextureManager::getInstance().Load(
				converttoTexturePath(textureName).c_str());
			break;

		default:
			break;
		}

		return this;
	}

private:
	// 外部テクスチャのパスを生成
	std::string converttoTexturePath(const std::string& textureName) {
		// テクスチャファイル名からパスを生成

		// モデルと同ディレクトリから参照
		// モデル用テクスチャを1ディレクトリに集結するため、複数ディレクトリの参照は原則不可
		std::string texturePath = mDirectory.string() + textureName;

		return texturePath;
	}
};