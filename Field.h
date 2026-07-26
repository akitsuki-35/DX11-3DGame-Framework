/*============================================================
*	@file	 : Field.h
*	@brief	 : フィールド
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/07/26
*============================================================*/
#pragma once

#include "GameObject.h"
#include "Mesh.h"
#include "ShaderLoader.h"

/*============================================================
*	@class	: Field
*	@brief	: フィールド
*============================================================*/
class Field : public GameObject
{
private:
	Mesh mMesh{};
	Shader* mShader{};

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ

public:
	Field() = default;
	
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};