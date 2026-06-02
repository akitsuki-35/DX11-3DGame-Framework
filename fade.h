/*============================================================
*	@file	 : fade.h
*	@brief	 : フェード制御
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/03/29
*	@Updated : 2026/06/02
*============================================================*/
#ifndef FADE_H
#define FADE_H

#include <DirectXMath.h>
using namespace::DirectX;

/*============================================================
*	@class	: Fade
*	@brief	: フェード制御
*============================================================*/
class Fade
{
public:
	// フェードの推移状態
	enum State
	{
		NONE,
		FADE_OUT,
		FADE_OUT_END,
		FADE_IN,
		FADE_IN_END
	};

private:
	static class Texture* texture;
	static State fadeState;
	static double time; // フェード総時間
	static double accumulatedtime; // 総経過時間
	static double startTime; // フェード開始時間
	static XMFLOAT4 color;

	Fade() {}
	Fade(const Fade&);
	Fade& operator=(const Fade&);
	~Fade() {};

public:
	static Fade& GetInstance() {
		static Fade instance;
		return instance;
	}

	const void Initialize();
	const void Finalize();
	const void Update(double elapsedTime);
	const void Draw();

	// フェード開始
	const void Start(const double& fadeTime, const bool& isFadeIn,
		const XMFLOAT4& fadeColor = { 0.0f,0.0f,0.0f,1.0f });
	const Fade::State GetState() { return fadeState; }
};

#endif // !FADE_H