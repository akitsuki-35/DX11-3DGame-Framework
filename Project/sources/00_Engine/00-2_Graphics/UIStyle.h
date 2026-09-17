/*============================================================
*	@file	 : UIStyle.h
*	@brief	 : UIキャンバス設定定義
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/12
*	@updated : 2026/09/16
*============================================================*/
#pragma once

#include "Elements.h"
#include <array>

/*============================================================
*	@namespace	: UIStyle
*	@brief		: UIキャンバス設定定義
*============================================================*/
namespace UIStyle {
	// ピボット列挙体
	enum class Pivot : uint8_t
	{
		Center,
		CenterTop,
		CenterBottom,
		LeftTop,
		LeftBottom,
		RightTop,
		RightBottom,

		Count
	};

	std::array<Element::VERTEX3D, 4> Create(const Pivot& pivot);
}