/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	マウスモジュール[mouse.h]
*
* 　Author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　Date	: 2026/04/13
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
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


// 導入方法
//
// 対象のウィンドウが生成されたらそのウィンドウハンドルを引数に初期化関数を呼ぶ
//
// MouseInitialize(hwnd);
//
// ウィンドウメッセージプロシージャからマウス制御用フック関数を呼び出す
//
// LResult CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// {
//     switch (message)
//     {
//     case WM_ACTIVATEAPP:
//     case WM_INPUT:
//     case WM_MOUSEMOVE:
//     case WM_LBUTTONDOWN:
//     case WM_LBUTTONUP:
//     case WM_RBUTTONDOWN:
//     case WM_RBUTTONUP:
//     case WM_MBUTTONDOWN:
//     case WM_MBUTTONUP:
//     case WM_MOUSEWHEEL:
//     case WM_XBUTTONDOWN:
//     case WM_XBUTTONUP:
//     case WM_MOUSEHOVER:
//         Mouse_ProcessMessage(message, wParam, lParam);
//         break;
//
//     }
// }
//

#endif // HAL_YOUHEI_MOUSE_H