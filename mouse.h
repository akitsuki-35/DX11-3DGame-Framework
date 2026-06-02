/*============================================================
*	@file	 : mouse.h
*	@brief	 : マウスモジュール
*
* 　@Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@Date	 : 2026/04/13
*	@Updated : 2026/06/02
*============================================================*/
#ifndef MOUSE_H
#define MOUSE_H

#include <windows.h>
#include <memory>

// マウスモード
typedef enum MousePositionModeTag
{
    MODE_ABSOLUTE, // 絶対座標モード
    MODE_RELATIVE, // 相対座標モード
} MousePositionMode;

// マウス状態構造体
typedef struct MouseStateTag
{
    bool leftButton;
    bool middleButton;
    bool rightButton;
    bool xButton1;
    bool xButton2;
    int x;
    int y;
    int scrollWheelValue;
    MousePositionMode positionMode;
} MouseState;

// マウスモジュールの初期化
void MouseInitialize(HWND window);

// マウスモジュールの終了処理
void MouseFinalize();

// マウスの状態を取得する
void GetMouseState(MouseState* pState);

// 累積したマウススクロールホイール値をリセットする
void MouseResetScrollWheelValue();

// マウスのポジションモードを設定する（デフォルトは絶対座標モード）
void SetMouseMode(MousePositionMode mode);

// マウスの接続を検出する
bool MouseIsConnected();

// マウスカーソルが表示されているか確認する
bool MouseIsVisible();

// マウスカーソル表示を設定する
void MouseSetVisible(bool visible);

// マウス制御のためのウィンドウメッセージプロシージャフック関数
void MouseProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

#endif // MOUSE_H