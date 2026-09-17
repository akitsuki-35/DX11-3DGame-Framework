/*============================================================
*	@file	 : Transition.cpp
*	@brief	 : トランジション制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/09/16
*============================================================*/
#include "Transition.h"

using namespace::DirectX;

void Transition::Initialize()
{
	// タイマー初期化
	_mTimer = std::make_unique<Timer>();

	// レンダラー初期化
	_mRenderer = std::make_unique<UIRenderer>();
	_mRenderer->GetCanvas().CreateCanvas(UIStyle::Pivot::LeftTop);

	// トランスフォーム初期化
	mTransform.SetPosition({ 0.0f, 0.0f, 0.0f });
	mTransform.SetScale({ Screen::WIDTH, Screen::HEIGHT, 0.0f });

	// シェーダー読み込み
	_mRenderer->LoadShader("UI");
}

void Transition::Finalize()
{
	_mRenderer->Finalize();
	_mRenderer = nullptr;

	_mTimer->Finalize();
	_mTimer = nullptr;
}

void Transition::Update(double deltaTime)
{
	if (!_mTimer->GetEnable()) return;

	// トランジション進行度を取得
	float alpha = _mTimer->GetProgress();

	// 値をクランプ
	if (alpha > 1.0f) alpha = 1.0f;
	if (alpha < 0.0f) alpha = 0.0f;

	// 透明度更新
	XMFLOAT4 color = _mRenderer->GetColor();
	color.w = mFadeIn ? alpha : 1.0f - alpha;
	_mRenderer->SetColor({ color });

	_mTimer->Update(deltaTime);
}

void Transition::Draw() const
{
	if (!_mTimer->GetEnable()) return;

	// テクスチャが存在しない場合は白テクスチャを使用
	if (!_mRenderer->GetTexture()) {
		_mRenderer->LoadTexture("assets\\textures\\white.png");
	}

	_mRenderer->Draw(mTransform);
}

void Transition::Start(const double& fadeTime, const bool& isFadeIn, const Color::Index& color)
{
	// タイマーをセット
	_mTimer->Start(fadeTime);

	// フェードタイプに応じて初期の透明度を決定
	XMFLOAT4 initColor = Color::ConvertColor(static_cast<int>(color));
	initColor.w = isFadeIn ? 1.0f : 0.0f;
	_mRenderer->SetColor(initColor);

	mFadeIn = isFadeIn;
}

bool Transition::GetTransitionActive()
{
	// トランジション中かを判定
	return _mTimer->GetEnable();
}

float Transition::GetTransitionProgress()
{
	// トランジション進行度を取得
	return _mTimer->GetProgress();
}
