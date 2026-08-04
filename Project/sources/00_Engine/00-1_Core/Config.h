/*============================================================
*	@file	 : Config.h
*	@brief	 : システム設定・定数定義
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/05
*	@updated : 2026/08/04
*============================================================*/
#pragma once

/*============================================================
*	@namespace	: Screen
*	@brief		: スクリーン関連パラメータ定義
*============================================================*/
namespace Screen {
	// 画面解像度
	static constexpr int WIDTH{ 1920 };
	static constexpr int HEIGHT{ 1080 };

	// X・Y中心座標
	static constexpr int CENTER_X{ WIDTH / 2 };
	static constexpr int CENTER_Y{ HEIGHT / 2 };

	// スクリーン端座標
	static constexpr int TOP{ 0 };
	static constexpr int BOTTOM{ HEIGHT };
	static constexpr int LEFT{ 0 };
	static constexpr int RIGHT{ WIDTH };
}