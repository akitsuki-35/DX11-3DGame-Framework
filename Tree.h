/*============================================================
*	@file	 : Tree.h
*	@brief	 : 木のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/07/26
*============================================================*/
#pragma once

#include "GameObject.h"
#include "Mesh.h"
#include "ShaderLoader.h"

/*============================================================
*	@class	: Tree
*	@brief	: 木のビルボード描画
*============================================================*/
class Tree : public GameObject
{
private:
public:
	Tree() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};