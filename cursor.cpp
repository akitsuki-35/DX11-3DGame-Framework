/*============================================================
*	@file	 : Cursor.cpp
*	@brief	 : マウスカーソル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/20
*	@updated : 2026/06/02
*============================================================*/
#include "Cursor.h"
#include "Mouse.h"
#include "Texture.h"
using namespace DirectX;

/*------------------------------------------------------------
	メンバ変数定義
------------------------------------------------------------*/
XMFLOAT2 Cursor::position{};
std::list<std::unique_ptr<Texture>> textures;
CursorState Cursor::cursorState{ NONE, { 0.0f, 0.0f, 0.0f, 0.0f } };

const void Cursor::Update(double elapsedTime)
{
    // マウス座標の取得
    MouseState state{};
    GetMouseState(&state);
    position.x = static_cast<float>(state.x);
	position.y = static_cast<float>(state.y);
}

void Cursor::SetColor(const DirectX::XMFLOAT4& color)
{
    cursorState.color = color;
}

/*------------------------------------------------------------
	左ボタンの判定
------------------------------------------------------------*/
bool Cursor::IsLeftButtonPressed()
{
    // 前フレームでボタンが押されていたか判定
    if (cursorState.current.leftButton) {
        // lastにtrueを格納
        cursorState.last.leftButton = true;
    }

    // マウス状態の取得
    MouseState state{};
    GetMouseState(&state);
    cursorState.current.leftButton = state.leftButton;

    return cursorState.current.leftButton;
}

bool Cursor::IsLeftButtonTrigger()
{
    // 前フレームでボタンが押されていたか判定
    if (cursorState.current.leftButton) {
        cursorState.last.leftButton = true;
        return false;
    }

    // マウス状態の取得
    MouseState state{};
    GetMouseState(&state);
    cursorState.current.leftButton = state.leftButton;

    return cursorState.current.leftButton;
}

bool Cursor::IsLeftButtonUp()
{
    // マウス状態の取得
    MouseState state{};
    GetMouseState(&state);
    cursorState.current.leftButton = state.leftButton;

    // 前フレームでボタンが押されていたか判定
    if (!cursorState.current.leftButton) {
        if (cursorState.last.leftButton) {
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}

/*------------------------------------------------------------
	右ボタンの判定
------------------------------------------------------------*/
bool Cursor::IsRightButtonPressed()
{
    // 前フレームでボタンが押されていたか判定
    if (cursorState.current.rightButton) {
        cursorState.last.rightButton = true;
    }

    // マウス状態の取得
    MouseState state{};
    GetMouseState(&state);
    cursorState.current.rightButton = state.rightButton;

    return cursorState.current.rightButton;
}

bool Cursor::IsRightButtonTrigger()
{
    // 前フレームでボタンが押されていたか判定
    if (cursorState.current.rightButton) {
        cursorState.last.rightButton = true;
        return false;
    }

    // マウス状態の取得
    MouseState state{};
    GetMouseState(&state);
    cursorState.current.rightButton = state.rightButton;

    return cursorState.current.rightButton;
}

bool Cursor::IsRightButtonUp()
{
    // マウス状態の取得
    MouseState state{};
    GetMouseState(&state);
    cursorState.current.rightButton = state.rightButton;

    // 前フレームでボタンが押されていたか判定
    if (!cursorState.current.rightButton) {
        if (cursorState.last.rightButton) {
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}