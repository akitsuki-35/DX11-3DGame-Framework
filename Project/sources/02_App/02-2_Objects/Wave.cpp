/*============================================================
*	@file	 : Wave.cpp
*	@brief	 : 波
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/17
*	@updated : 2026/09/17
*============================================================*/
#include "Wave.h"
#include "SpriteRenderer.h"
#include "MeshTypes.h"

using namespace MeshType;

void Wave::Initialize()
{
	auto renderer = AddComponent<SpriteRenderer>(this);

	renderer->GetMesh().CreatePlane(Plane::Pivot::Center, Plane::Axis::XZ);
	mTransform.SetScale({ 30.0f, 30.0f, 30.0f });

	renderer->LoadTexture("assets\\textures\\water.jpg")->LoadShader("Unlit");
}

void Wave::Finalize()
{
	GameObject::Finalize();
}

void Wave::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Wave::Draw() const
{
	GameObject::Draw();
}
