/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	タイトルシーン[title.h]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2026/03/29
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
/*============================================================
*	@file	 : title.h
*	@brief	 : タイトルシーン
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/03/29
*	@Updated : 2026/06/02
*============================================================*/
#ifndef TITLE_H
#define TITLE_H

#include "scene.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*------------------------------------------------------------
	タイトルシーンの状態
------------------------------------------------------------*/
enum TitleState
{
	TITLE_FADE_IN,
	TITLE_KEYINPUT_WAIT,
	TITLE_KEYINPUT_ACTION,
	TITLE_FADE_OUT
};

/*============================================================
*	@class	: Title
*	@brief	: タイトルシーン（Sceneを継承）
*============================================================*/
class Title : public Scene
{
private:
	TitleState state{ TitleState::TITLE_FADE_IN };
	double accumulatedTime{ 0.0 };
	double keyInputTime{};
	Texture* pTexture{ nullptr };

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double elapsedTime) override;
	void Draw() const override;
};

#endif // TITLE_H