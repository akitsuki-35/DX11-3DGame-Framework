/*============================================================
*	@file	 : Transition.h
*	@brief	 : トランジション
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "Timer.h"
#include "UIRenderer.h"
#include "Transform.h"
#include "Config.h"
#include <DirectXMath.h>
#include <memory>

/*============================================================
*	@class	: Transition
*	@brief	: トランジション
*============================================================*/
class Transition
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static Transition& getInstance() {
		static Transition instance;
		return instance;
	}

private:
	Transition() = default;
	Transition(const Transition&) = delete;

	Transition& operator=(const Transition&) = delete;
	Transition(Transition&&) = delete;

	Transition& operator=(Transition&&) = delete;
	~Transition() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// タイマー
	std::unique_ptr<Timer> _mTimer{};

	// レンダラー
	std::unique_ptr<UIRenderer> _mRenderer{};

	// トランスフォーム
	Transform mTransform{};

	// フェードインorフェードアウト？
	bool mFadeIn{};

public:
	void Initialize(const char* texturePath, std::string shaderName);
	void Finalize();
	void Update(double deltaTime);
	void Draw() const;

	// トランジション開始
	void Start(const double& fadeTime, const bool& isFadeIn,
		const Color::Index& color = Color::Index::Black);

	// トランジション中か判定
	bool GetTransitionActive();

	// トランジション進行度取得
	float GetTransitionProgress();
};