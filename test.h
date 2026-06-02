/*============================================================
*	@file	 : test.h
*	@brief	 : テスト用シーン
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/29
*	@Updated : 2026/06/02
*============================================================*/
#ifndef TEST_H
#define TEST_H

#include "scene.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;
class SpriteSheet;

/*============================================================
*	@class	: Test
*	@brief	: テスト用シーン（Sceneクラスを継承）
*============================================================*/
class Test : public Scene
{
private:
	// テスト用のメンバ変数をここに追加

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double elapsed_time) override;
	void Draw() const override;
};

#endif // TEST_H