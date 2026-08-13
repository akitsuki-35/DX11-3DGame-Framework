/*============================================================
*	@file	 : Score.cpp
*	@brief	 : スコア表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/30
*	@updated : 2026/08/12
*============================================================*/
#include "Score.h"
#include "TextRenderer.h"
#include "FontLoader.h"

void Score::Initialize()
{
	mLayer = 3;

	TextRenderer* renderer = AddComponent<TextRenderer>(this);

	mTransform.SetPosition({ 0.0f, 0.0f, 0.0f });

	renderer->SetFont("MPLUS_Regular")->
		SetText("あのイーハトーヴォのすきとおった風、夏でも底に冷たさをもつ青いそら、うつくしい森で飾られたモリーオ市、郊外のぎらぎらひかる草の波")
		->LoadShader("FontOutline");

	mValue = 0;
}

void Score::Finalize()
{
	GameObject::Finalize();
}

void Score::Update()
{
	GameObject::Update();
}

void Score::Draw() const
{
	GameObject::Draw();
}