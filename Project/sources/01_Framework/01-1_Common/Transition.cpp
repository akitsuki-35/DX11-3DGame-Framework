/*============================================================
*	@file	 : Transition.cpp
*	@brief	 : トランジション制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/08/16
*============================================================*/
#include "Transition.h"
#include "UIRenderer.h"

using namespace::DirectX;

void Transition::Initialize()
{

}

void Transition::Finalize()
{
	_mRenderer->Finalize();
	_mRenderer = nullptr;
}

void Transition::Update()
{
	double dt = 1.0f / 60.0f;

	// 時間計測とステートの管理
	if (mState == State::None || mState == State::FadeOutEnd || mState == State::FadeInEnd) {
		return;
	}

	mAccumulatedtime += dt;

	double lifeTime = mAccumulatedtime - mStartTime;

	float alpha = (float)(lifeTime / mTime);

	XMFLOAT4 color = _mRenderer->GetColor();
	color.w = mState == State::FadeIn ? 1.0f - alpha : alpha;
	_mRenderer->SetColor({ color });

	if (mTime <= lifeTime) {
		mState == State::FadeIn ? State::FadeInEnd : State::FadeOutEnd;
	}
}

void Transition::Draw() const
{
	if (mState == State::None || mState == State::FadeInEnd) {
		return;
	}

	_mRenderer->Draw();
}

void Transition::Start(const double& fadeTime, const bool& isFadeIn, const Color::Index& color)
{
	mTime = fadeTime;
	mState = isFadeIn ? State::FadeIn : State::FadeOut;

	mStartTime = mAccumulatedtime;

	_mRenderer->SetColor(Color::ConvertColor(static_cast<int>(color)));
}