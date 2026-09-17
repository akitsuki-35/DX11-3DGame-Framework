/*============================================================
*	@file	 : Model.cpp
*	@brief	 : モデルリソース
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/09/16
*============================================================*/
#include "Model.h"

void Model::AddMesh(ModelMesh&& mesh)
{
	// モデルメッシュ登録
	mMeshes.emplace_back(std::move(mesh));
}