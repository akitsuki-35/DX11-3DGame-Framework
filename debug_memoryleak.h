/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	メモリリークの検出[debug_memoryleak.h]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/11
* ----------------------------------------------------------------------------------------------------------
* 
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef DEBUG_MEMORYLEAK_H
#define DEBUG_MEMORYLEAK_H

// メモリリーク検出箇所を出力するマクロ
// 他ファイルにインクルードのみで導入可

// debugのみで動作
#if defined(DEBUG) || defined(_DEBUG)
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // defined(DEBUG) || defined(_DEBUG)

#endif // DEBUG_MEMORYLEAK_H