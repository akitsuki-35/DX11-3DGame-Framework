/*============================================================
*	@file	 : ModelResource.h
*	@brief	 : モデル内リソース
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/07/30
*============================================================*/
#pragma once

#include "Texture.h"
#include "Mesh.h"
#include "GraphicsTypes.h"
#include <vector>

class ModelResource
{
private:

	// モデル内マテリアル
	struct MATERIAL
	{
		Element::MATERIAL material{};
		Texture texture{};
	};

	// サブセット
	struct SUBSET
	{
		uint32_t startIndex{};
		uint32_t indexNum{};
		uint32_t materialIndex;
	};

	// モデル内メッシュ
	struct MESH
	{
		Mesh mesh{};
		std::vector<SUBSET> subsets;
	};

	std::vector<MESH> mMeshes;
	std::vector<MATERIAL> mMaterials;
};