/*============================================================
*	@file	 : Model.h
*	@brief	 : モデルリソース
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/07/30
*============================================================*/
#pragma once

#include "Texture.h"
#include "ModelMesh.h"
#include "GraphicsTypes.h"
#include <vector>

/*============================================================
*	@class	: Model
*	@brief	: モデルリソース
*============================================================*/
class Model
{
	friend class ModelManager;
	friend class ModelDrawable;
	friend class AssimpLoader;

private:

	// モデル用マテリアル
	struct MATERIAL
	{
		Element::MATERIAL material{};
		Texture texture{};
	};

	std::vector<ModelMesh> mMeshs{};
	std::vector<MATERIAL> mMaterials{};

public:
	void AddMesh(ModelMesh&& mesh){ mMeshs.emplace_back(std::move(mesh)); }
};