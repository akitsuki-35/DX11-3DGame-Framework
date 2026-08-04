/*============================================================
*	@file	 : AssimpLoader.h
*	@brief	 : assimpによるモデルロード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/02
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "ModelMesh.h"
#include <string>
#include <unordered_map>

/*--------------------------------------------------
	前方宣言
----------------------------------------------------*/
class Model;
class Texture;
struct aiScene;
struct aiMesh;

/*============================================================
*	@class	: AssimpLoader
*	@brief	: assimpによるモデルロード・生成
*============================================================*/
class AssimpLoader final 
{
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
	// 埋め込みテクスチャ検索用
	std::unordered_map<std::string, Texture*> mTextureMap{};

public:
	// モデル生成
	bool GenerateModel(Model& model, const std::string& path);

private:
	// メッシュ生成
	bool loadMeshes(const aiScene* scene, Model& model);

	// 頂点データ取得
	Element::VERTEX3D convertVertex(const aiMesh* mesh, int v);

	// サブセット生成
	ModelMesh::SUBSET createSubset(const aiMesh* mesh, uint32_t startIndex, uint32_t indexNum);

	// 埋め込みテクスチャ取得
	bool loadTextures(const aiScene* scene, Model& model);

	// マテリアル取得
	void loadMaterials(const aiScene* scene, Model& model);
};