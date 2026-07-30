/*============================================================
*	@file	 : Tree.h
*	@brief	 : 木のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/07/26
*============================================================*/
#include "Main.h"
#include "Tree.h"
#include "Renderer.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "Audio.h"
#include "BillboardDrawable.h"

#include "GraphicsTypes.h"
#include "MeshTypes.h"
#include "DirectX11Config.h"

using namespace MeshType;

void Tree::Initialize()
{
	mLayer = 2;

	BillboardDrawable* drawable = AddComponent<BillboardDrawable>(this);

	drawable->GetMesh().CreatePlane(Plane::Pivot::CenterBottom, Plane::Axis::XY);

	mTransform.SetPosition({ 0.0f,0.0f, 0.0f });
	mTransform.SetScale({ 8.0f, 10.0f, 0.0f });

	drawable->LoadTexture("assets\\textures\\tree.png");

	drawable->LoadShader("Unlit");
}

void Tree::Finalize()
{
	GameObject::Finalize();
}

void Tree::Update()
{
	GameObject::Update();
}

void Tree::Draw() const
{
	GameObject::Draw();
}