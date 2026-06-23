/*============================================================
*	@file	 : result.cpp
*	@brief	 : リザルトシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/06/23
*============================================================*/
#include "result.h"
#include "manager.h"
//#include "keylogger.h"
#include "texture.h"
#include "fade.h"
#include "audio.h"
#include "direct3d.h"

#include "polygon2d.h"
#include "title.h"
#include "input.h"

#include <math.h>

std::list<GameObject*> Result::resultObjects;

void Result::Initialize()
{
	//Fade::GetInstance().Start(1.0f, true);
	//state = TITLE_FADE_IN;
	Result::resultObjects.clear();

}

void Result::Finalize()
{}

void Result::Update(double elapsedTime)
{
	//accumulatedTime += elapsed_time;

	//switch (state)
	//{
	//case TITLE_FADE_IN:
	//	if (Fade::GetInstance().GetState() == Fade::FADE_IN_END) {
	//		state = TITLE_KEYINPUT_WAIT;
	//	}
	//	break;

	//case TITLE_KEYINPUT_WAIT:
	//	if (KeyLogger::IsTrigger(KK_ENTER))
	//	{
	//		state = TITLE_KEYINPUT_ACTION;
	//		keyInputTime = accumulatedTime;
	//		//サウンド再生

	//	}
	//	break;

	//case TITLE_KEYINPUT_ACTION:
	//	if (accumulatedTime - keyInputTime > 1.0) {
	//		state = TITLE_FADE_OUT;
	//		Fade::GetInstance().Start(1.0f, false);
	//	}
	//	break;

	//case TITLE_FADE_OUT:
	//	if (Fade::GetInstance().GetState() == Fade::FADE_OUT_END) {
	//		// ゲームシーンに遷移
	//		//Manager::SetNextScene(new Game);
	//	}
	//	break;

	//default:
	//	break;
	//}

	//Manager::SceneChange<Game>();

	if (Input::GetKeyTrigger(VK_RETURN)) {
		Manager::SceneChange<Title>();
	}
}

void Result::Draw() const
{
	//if (state != TITLE_FADE_IN) {
	//	float alpha = static_cast<float>((sin(accumulatedTime) + 1.0f)) * 0.5f;

	//}


}