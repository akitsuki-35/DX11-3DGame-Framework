/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	シーン管理[scene.cpp]
*
* 　作成者 : @akitsuki-35（https://github.com/akitsuki-35）
* 　作成日 : 2025/9/17
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "scene.h"
#include "title.h"
#include "game.h"

static Scene g_CurrentScene = SCENE_GAME; // 現在シーン
static Scene g_NextScene = g_CurrentScene; // 次の遷移シーン

void SceneInitialize()
{
	switch (g_CurrentScene)
	{
	case SCENE_TITLE:
		TitleInitialize();
		break;

	case SCENE_GAME:
		GameInitialize();
		break;

	case SCENE_RESULT:
		//未実装
		break;

	default:
		break;
	}
}

void SceneFinalize()
{
	switch (g_CurrentScene)
	{
	case SCENE_TITLE:
		TitleFinalize();
		break;

	case SCENE_GAME:
		GameFinalize();
		break;

	case SCENE_RESULT:
		// 未実装
		break;
	
	default:
		break;
	}
}

void SceneUpdate(double elapsedTime)
{
	switch (g_CurrentScene)
	{
	case SCENE_TITLE:
		TitleUpdate(elapsedTime);
		break;

	case SCENE_GAME:
		GameUpdate(elapsedTime);
		break;

	case SCENE_RESULT:
		// 未実装
		break;

	default:
		break;
	}
}

void SceneDraw()
{
	switch (g_CurrentScene)
	{
	case SCENE_TITLE:
		TitleDraw();
		break;

	case SCENE_GAME:
		GameDraw();
		break;

	case SCENE_RESULT:
		// 未実装
		break;

	default:
		break;
	}
}

void SetNextScene(Scene next)
{
	g_NextScene = next;
}

void ChangeScene()
{
	if (g_CurrentScene != g_NextScene)
	{
		// 現在シーンの終了処理
		SceneFinalize();

		// シーンを次のシーンへ遷移
		g_CurrentScene = g_NextScene;

		//遷移先のシーンを初期化
		SceneInitialize();
	}
}