/*============================================================
*	@file	 : fade.cpp
*	@brief	 : フェード制御
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/03/29
*	@Updated : 2026/06/02
*============================================================*/
#include "fade.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "direct3d.h"

#include "debug_memoryleak.h"

/*------------------------------------------------------------
	メンバ変数定義
------------------------------------------------------------*/
Texture* Fade::texture{ nullptr };
Fade::State Fade::fadeState{ Fade::State::FADE_IN };
double Fade::time{};
double Fade::accumulatedtime{ 0.0 };
double Fade::startTime{ 0.0 };
XMFLOAT4 Fade::color{ 0.0f, 0.0f, 0.0f, 1.0f };

const void Fade::Initialize()
{
	// テクスチャと変数のセット
	texture = new Texture(L"Resources/Textures/Common/white.png", { 0.0f, 0.0f },
		{ 1920.0f, 1080.0f }, 0, color);
	fadeState = Fade::State::FADE_IN;
	accumulatedtime = 0.0;
}

const void Fade::Finalize()
{
	delete texture;
}

const void Fade::Update(double elapsedTime)
{
	// 時間計測とステートの管理
	if (fadeState == NONE || fadeState == FADE_OUT_END || fadeState == FADE_IN_END) {
		return;
	}

	accumulatedtime += elapsedTime;

	double lifeTime = accumulatedtime - startTime;

	float alpha = (float)(lifeTime / time);

	color.w = fadeState == FADE_IN ? 1.0f - alpha : alpha;
	texture->SetColor(color);

	if (time <= lifeTime) {
		fadeState = fadeState == FADE_IN ? FADE_IN_END : FADE_OUT_END;
	}
}

const void Fade::Draw()
{
	if (fadeState == NONE || fadeState == FADE_IN_END) {
		return;
	}

	texture->Draw();
}

const void Fade::Start(const double& fadeTime, const bool& isFadeIn, const XMFLOAT4& fadeColor)
{
	time = fadeTime;
	fadeState = isFadeIn ? FADE_IN : FADE_OUT;

	startTime = accumulatedtime;

	texture->SetColor(color = fadeColor);
}
