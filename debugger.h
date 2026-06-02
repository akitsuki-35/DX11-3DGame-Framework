/*============================================================
*	@file	 : debugger.h
*	@brief	 : ImGuiデバッガー
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/05/21
*	@Updated : 2026/06/02
*============================================================*/
#ifndef DEBUGGER_H
#define DEBUGGER_H

#if defined(DEBUG) || defined(_DEBUG)

#include <Windows.h>

/*============================================================
*	@class	: Debugger
*	@brief	: デバッガークラス
*
* 　※Initialize, Fainalize, Draw変更厳禁！！
*============================================================*/
class Debugger
{
private:
	Debugger() {}
	Debugger(const Debugger&);
	Debugger& operator= (const Debugger&);
	~Debugger() {};

public:
	static Debugger& GetInstance() {
		static Debugger instance;
		return instance;
	}

	// ===== 初期化～描画 =====
	const void Initialize(HWND hwnd) const;
	const void Finalize() const;
	const void Update() const;
	const void Draw() const;

	// ===== デバッグウィンドウ関数をここに追加 =====
	const void CursorDebug();
	const void CursorColorDebug();
};
#endif // defined(DEBUG) || defined(_DEBUG)

#endif // DEBUGGER_H