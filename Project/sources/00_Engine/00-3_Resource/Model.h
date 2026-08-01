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

private:

	// モデル用マテリアル
	struct MATERIAL
	{
		Element::MATERIAL material{};
		Texture texture{};
	};

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mVertexBuffer{};

	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mIndexBuffer{};

	std::vector<ModelMesh> mMeshs;
	std::vector<MATERIAL> mMaterials;
};