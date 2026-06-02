/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	シーン管理[scene.h]
*
* 　作成者 : @akitsuki-35（https://github.com/akitsuki-35）
* 　作成日 : 2025/9/17
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef SCENE_H
#define SCENE_H

void SceneInitialize();
void SceneFinalize();
void SceneUpdate(double elapsedTime);
void SceneDraw();

enum Scene
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT
};

void SetNextScene(Scene next);
void ChangeScene();

#endif // SCENE_H