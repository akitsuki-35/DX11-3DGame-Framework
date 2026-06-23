/*============================================================
*	@file	 : result.h
*	@brief	 : リザルトシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/06/23
*============================================================*/
#ifndef RESULT_H
#define RESULT_H

#include "scene.h"
#include "gameobject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*============================================================
*	@class	: Result
*	@brief	: リザルトシーン（Sceneを継承）
*============================================================*/
class Result : public Scene
{
private:
	double accumulatedTime{ 0.0 };
	double keyInputTime{};
	Texture* pTexture{ nullptr };
	static std::list<GameObject*> resultObjects;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double elapsedTime) override;
	void Draw() const override;
};

#endif //  RESULT_H