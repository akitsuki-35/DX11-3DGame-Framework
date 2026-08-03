/*============================================================
*	@file	 : field.cpp
*	@brief	 : 3Dポリゴン表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/06/09
*============================================================*/
#include "Main.h"
#include "Field.h"
#include "Renderer.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "Audio.h"
#include "SpriteDrawable.h"

#include "GraphicsTypes.h"
#include "MeshTypes.h"
#include "DirectX11Config.h"

using namespace MeshType;

void Field::Initialize()
{
	SpriteDrawable* drawable = AddComponent<SpriteDrawable>(this);

	drawable->GetMesh().CreatePlane(Plane::Pivot::Center, Plane::Axis::XZ);
	mTransform.SetScale({ 30.0f, 30.0f, 30.0f });

	drawable->LoadTexture("assets\\textures\\glass.jpg");

	drawable->LoadShader("Unlit");

	Audio* bgm = AddComponent<Audio>(this);
	bgm->Load("assets\\audio\\bgm.wav");
	bgm->Play(true);
}

void Field::Finalize()
{
	GameObject::Finalize();
}

void Field::Update()
{
	GameObject::Update();
}

void Field::Draw() const
{
	GameObject::Draw();
}