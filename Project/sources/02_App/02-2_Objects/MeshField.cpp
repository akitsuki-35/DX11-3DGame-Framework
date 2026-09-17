/*============================================================
*	@file	 : MeshField.cpp
*	@brief	 : メッシュフィールド
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/08
*	@updated : 2026/09/08
*============================================================*/
#include "MeshField.h"
#include "SpriteRenderer.h"
#include "MeshTypes.h"
#include "AudioPlayer.h"
#include "input.h"

using namespace MeshType;

void MeshField::Initialize()
{
	SpriteRenderer* renderer = AddComponent<SpriteRenderer>(this);

	renderer->GetMesh().CreatePlane(Plane::Pivot::Center, Plane::Axis::XZ);
	mTransform.SetScale({ 30.0f, 30.0f, 30.0f });

	renderer->LoadTexture("assets\\textures\\glass.jpg")->LoadShader("Unlit");

	AudioPlayer* bgm = AddComponent<AudioPlayer>(this)->LoadAudio("assets\\audio\\tukito_break_out_in_the_middle.ogg");
	bgm->SetVolume(0.1f);
	bgm->Play(true);
}

void MeshField::Finalize()
{
	GameObject::Finalize();
}

void MeshField::Update(double deltaTime)
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

	GameObject::Update(deltaTime);
}

void MeshField::Draw() const
{
	GameObject::Draw();
}