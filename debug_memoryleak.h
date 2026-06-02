/*============================================================
*	@file	 : debug_memoryleak.h
*	@brief	 : メモリリークの検出
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/11
*	@Updated : 2026/06/02
*============================================================*/
#ifndef DEBUG_MEMORYLEAK_H
#define DEBUG_MEMORYLEAK_H

// メモリリーク検出箇所を出力するマクロ
// 他ファイルにインクルードのみで導入可

// debugのみで動作
#if defined(DEBUG) || defined(_DEBUG)

#include <memory>

#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // defined(DEBUG) || defined(_DEBUG)

#endif // DEBUG_MEMORYLEAK_H