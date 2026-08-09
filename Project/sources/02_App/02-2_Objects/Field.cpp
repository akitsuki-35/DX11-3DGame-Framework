/*============================================================
*	@file	 : field.cpp
*	@brief	 : 3Dポリゴン表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/08/04
*============================================================*/
#include "Field.h"
#include "SpriteRenderer.h"
#include "MeshTypes.h"
#include "AudioPlayer.h"
#include "Utility.h"

using namespace MeshType;

void Field::Initialize()
{
	SpriteRenderer* drawable = AddComponent<SpriteRenderer>(this);

	drawable->GetMesh().CreatePlane(Plane::Pivot::Center, Plane::Axis::XZ);
	mTransform.SetScale({ 30.0f, 30.0f, 30.0f });

	drawable->LoadTexture("assets\\textures\\glass.jpg");

	drawable->LoadShader("Unlit");

	AudioPlayer* bgm = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\tukito_break_out_in_the_middle.ogg");
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