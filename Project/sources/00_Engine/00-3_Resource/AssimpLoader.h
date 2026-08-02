/*============================================================
*	@file	 : AssimpLoader.h
*	@brief	 : assimpによるモデルロード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/02
*	@updated : 2026/08/02
*============================================================*/
#pragma once

#include "ModelMesh.h"
#include "GraphicsTypes.h"
#include <string>

/*--------------------------------------------------
	前方宣言
----------------------------------------------------*/
class Model;
struct aiScene;
struct aiMesh;

/*============================================================
*	@class	: AssimpLoader
*	@brief	: assimpによるモデルロード・生成
*============================================================*/
class AssimpLoader final 
{
	friend class ModelManager;
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static AssimpLoader& getInstance() {
		static AssimpLoader  instance;
		return instance;
	}

private:
	AssimpLoader() = default;
	AssimpLoader(const AssimpLoader&) = delete;

	AssimpLoader& operator=(const AssimpLoader&) = delete;
	AssimpLoader(AssimpLoader&&) = delete;

	AssimpLoader& operator=(AssimpLoader&&) = delete;
	~AssimpLoader() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// モデル生成
	bool generateModel(Model& model, const std::string& path);

	// 頂点データ取得
	Element::VERTEX3D convertVertex(const aiMesh* mesh, int v);

	// サブセット生成
	ModelMesh::SUBSET createSubset(const aiMesh* mesh, uint32_t startIndex, uint32_t indexNum);

	// マテリアル取得
	void convertMaterial(const aiScene* scene, Model& model);
};