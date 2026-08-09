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
#include "input.h"

using namespace MeshType;

void Field::Initialize()
{
	SpriteRenderer* drawable = AddComponent<SpriteRenderer>(this);

	drawable->GetMesh().CreatePlane(Plane::Pivot::Center, Plane::Axis::XZ);
	mTransform.SetScale({ 30.0f, 30.0f, 30.0f });

	drawable->LoadTexture("assets\\textures\\glass.jpg");

	drawable->LoadShader("Unlit");

	AudioPlayer* bgm = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\tukito_break_out_in_the_middle.ogg");
	bgm->SetVolume(0.1f);
	bgm->Play(true);
}

void Field::Finalize()
{
	GameObject::Finalize();
}

void Field::Update()
{
	if (Input::GetKeyTrigger('Z')) {
		GameObject::GetComponent<AudioPlayer>()->Pause();
	}
	if (Input::GetKeyTrigger('X')) {
		GameObject::GetComponent<AudioPlayer>()->Resume();
	}
	if (Input::GetKeyTrigger('C')) {
		GameObject::GetComponent<AudioPlayer>()->Stop();
	}


	GameObject::Update();
}

void Field::Draw() const
{
	GameObject::Draw();
}