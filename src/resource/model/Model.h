/*============================================================
*	@file	 : Model.h
*	@brief	 : モデルリソース
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "Texture.h"
#include "ModelMesh.h"
#include "Skeleton.h"
#include "Elements.h"
#include <memory>
#include <vector>

/*============================================================
*	@class	: Model
*	@brief	: モデルリソース
*============================================================*/
class Model
{
	friend class ModelManager;
	friend class ModelRenderer;
	friend class AssimpLoader;

private:
	// モデル用マテリアル
	struct MATERIAL
	{
		// マテリアル
		Element::MATERIAL Material{};

		// テクスチャ
		Texture* _Texture{};
	};

	// メッシュ
	std::vector<ModelMesh> mMeshes{};

	// マテリアル
	std::vector<MATERIAL> mMaterials{};
	
	// スケルトン
	Skeleton mSkeleton{};

	// 埋め込みテクスチャ
	std::vector<std::unique_ptr<Texture>> mTextures{};

public:
	// メッシュ登録
	void AddMesh(ModelMesh&& mesh);

	// スケルトン取得
	Skeleton& GetSkeleton() { return mSkeleton; }
};