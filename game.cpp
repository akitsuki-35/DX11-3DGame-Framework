/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	ゲームシーン[game.cpp]
*
* 　作成者 : Asuka Kuroda
* 　作成日 : 2026/03/28
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "game.h"
#include "audio.h"
#include "keylogger.h"
#include "fade.h"

#include "sprite.h"
#include "texture.h"
#include "animation.h"
#include "collision.h"

#include "debug_memoryleak.h"

Texture* g_BackGround{ nullptr };
SpriteSheet* g_RunningMan{ nullptr };
Animation* g_Animation{ nullptr };
Collision::Circle* g_Collision[2]{ nullptr };

XMFLOAT2 g_position[2]{};
XMFLOAT4 g_color{ 1.0f, 1.0f, 1.0f, 1.0f };

void GameInitialize()
{
	FadeStart(1.0, true);

	g_position[0] = { 0.0f, 0.0f };
	g_position[1] = { 500.0f, 500.0f };

	g_BackGround = new Texture(L"Resources/Texture/background1.jpg");
	g_RunningMan = new SpriteSheet(L"Resources/Texture/runningman001.png", { 5, 2 });
	g_Animation = new Animation(g_RunningMan, { 0, 0 }, 0.05);
	g_Collision[0] = new Collision::Circle(g_position[0], { 100.0f, 160.0f }, { 140.0f, 200.0f });
	g_Collision[1] = new Collision::Circle(g_position[1], { 100.0f, 160.0f }, { 140.0f, 200.0f });
}

void GameFinalize()
{
	delete g_Collision[1];
	delete g_Collision[0];

	delete g_Animation;
	delete g_RunningMan;
	delete g_BackGround;
}

void GameUpdate(double elapsedTime)
{
	g_Animation->Update(elapsedTime);

	if (KeyIsPressd(KK_A)) {
		g_position[0].x -= 3.0f;
	}
	if (KeyIsPressd(KK_D)) {
		g_position[0].x += 3.0f;
	}
	if (KeyIsPressd(KK_W)) {
		g_position[0].y -= 3.0f;
	}
	if (KeyIsPressd(KK_S)) {
		g_position[0].y += 3.0f;
	}

	g_Collision[0]->Move(g_position[0], { 140.0f, 200.0f });

	if (g_Collision[0]->IsOverlap(g_Collision[1])) {
		g_color = { 1.0f, 0.0f, 0.0f, 1.0f };
	}
	else
	{
		g_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}
}

void GameDraw()
{
	g_BackGround->Draw({ 0.0f, 0.0f });
	g_RunningMan->Draw(g_position[0], {1, 0}, { 140, 200 }, g_color);
	g_Animation->Draw(g_position[1]);

	g_Collision[0]->Draw();
	g_Collision[1]->Draw();
}