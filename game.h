/*============================================================
*	@file	 : game.h
*	@brief	 : ゲームシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/28
*	@updated : 2026/06/02
*============================================================*/
#ifndef GAME_H
#define GAME_H

#include "scene.h"

/*============================================================
*	@class	: Game
*	@brief	: ゲームシーン（Sceneを継承）
*============================================================*/
class Game : public Scene
{
private:

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double elapsed_time) override;
	void Draw() const override;
};

#endif // GAME_H
