/*============================================================
*	@file	 : AppSetup.cpp
*	@brief	 : アプリケーション設定
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/20
*	@updated : 2026/09/20
*============================================================*/
#include "AppSetup.h"
#include "Graphics.h"
#include "Transition.h"
#include "Input.h"
#include "AudioPlayer.h"

#include "AnimationManager.h"
#include "AudioManager.h"
#include "FontManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "Application.h"
#include "Game.h"
#include <memory>

void AppSetup::Initialize()
{
	// 各種初期化
	D3D11::Graphics::getInstance().Initialize();

	// シェーダー読み込み
	ShaderInit::initialize();
	FontInit::initialize();

	Transition::getInstance().Initialize("assets\\textures\\white.png", "UI");
	Input::Initialize();
	AudioPlayer::InitializeMaster();

	// 初期シーン設定
	Application::getInstance().Initialize(std::make_unique<Game>());
}

void AppSetup::Finalize()
{
	Application::getInstance().Finalize();

	AnimationManager::getInstance().Clear();
	AudioManager::getInstance().Clear();
	ModelManager::getInstance().Clear();
	TextureManager::getInstance().Clear();
	FontManager::getInstance().Clear();
	ShaderManager::getInstance().Clear();

	AudioPlayer::FinalizeMaster();
	Input::Finalize();
	D3D11::Graphics::getInstance().Finalize();
}