/*============================================================
*	@file	 : AppSetup.h
*	@brief	 : アプリケーション設定
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/09/20
*	@updated : 2026/09/20
*============================================================*/
#pragma once

#include "ShaderManager.h"
#include "FontManager.h"
#include "FontLoader.h"

namespace AppSetup {
	extern inline void Initialize();
	extern inline void Finalize();
}

// フォントロード
// ゲーム起動時に一度だけ呼ぶ
namespace FontInit {
	inline void initialize() {
		FontManager::getInstance().Register("Kaisotai", "assets\\fonts\\Kaisotai-Next-UP-B.ttf");
	}
}

// シェーダー登録
// ゲーム起動時に1度だけ呼ぶ
namespace ShaderInit {
	inline void initialize() {
		ShaderManager::getInstance().Register("UI",
			"assets\\shaders\\UISpriteVS.cso", "assets\\shaders\\UnlitPS.cso");

		ShaderManager::getInstance().Register("Font",
			"assets\\shaders\\UISpriteVS.cso", "assets\\shaders\\FontPS.cso");

		ShaderManager::getInstance().Register("Unlit",
			"assets\\shaders\\UnlitVS.cso", "assets\\shaders\\UnlitPS.cso");
	}
}