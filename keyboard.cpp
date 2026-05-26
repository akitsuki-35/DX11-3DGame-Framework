/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	キーボードモジュール[keyboard.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/13
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "keyboard.h"

#include <assert.h>

static_assert(sizeof(KeyboardState) == 256 / 8, "キーボード状態構造体のサイズ不一致");

static KeyboardState g_State = {};

static void keyDown(int key)
{
    if (key < 0 || key > 0xfe) { return; }

    unsigned int* p = (unsigned int*)&g_State;
    unsigned int bf = 1u << (key & 0x1f);
    p[(key >> 5)] |= bf;
}

static void keyUp(int key)
{
    if (key < 0 || key > 0xfe) { return; }

    unsigned int* p = (unsigned int*)&g_State;
    unsigned int bf = 1u << (key & 0x1f);
    p[(key >> 5)] &= ~bf;
}

void KeyboardInitialize()
{
    KeyboardReset();
}

bool IsKeyDown(Keys key, const KeyboardState* pState)
{
    if (key <= 0xfe)
    {
        unsigned int* p = (unsigned int*)pState;
        unsigned int bf = 1u << (key & 0x1f);
        return (p[(key >> 5)] & bf) != 0;
    }
    return false;
}


bool IsKeyUp(Keys key, const KeyboardState* pState)
{
    if (key <= 0xfe)
    {
        unsigned int* p = (unsigned int*)pState;
        unsigned int bf = 1u << (key & 0x1f);
        return (p[(key >> 5)] & bf) == 0;
    }
    return false;
}

bool IsKeyDown(Keys key)
{
    return IsKeyDown(key, &g_State);
}

bool IsKeyUp(Keys key)
{
    return IsKeyUp(key, &g_State);
}

// キーボードの現在の状態を取得する
const KeyboardState* GetKeyboardState(void)
{
    return &g_State;
}

void KeyboardReset()
{
    ZeroMemory(&g_State, sizeof(KeyboardState));
}

// キーボード制御のためのウォンどうメッセージプロシージャフック関数
void KeyboardProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    bool down = false;

    switch (message)
    {
    case WM_ACTIVATEAPP:
        KeyboardReset();
        return;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        down = true;
        break;

    case WM_KEYUP:
    case WM_SYSKEYUP:
        break;

    default:
        return;
    }

    int vk = (int)wParam;
    switch (vk)
    {
    case VK_SHIFT:
        vk = (int)MapVirtualKey(((unsigned int)lParam & 0x00ff0000) >> 16u, MAPVK_VSC_TO_VK_EX);
        if (!down)
        {
            // 左シフトと右シフトの両方が同時に押された場合にクリアされるようにするための回避策
            keyUp(VK_LSHIFT);
            keyUp(VK_RSHIFT);
        }
        break;

    case VK_CONTROL:
        vk = ((UINT)lParam & 0x01000000) ? VK_RCONTROL : VK_LCONTROL;
        break;

    case VK_MENU:
        vk = ((UINT)lParam & 0x01000000) ? VK_RMENU : VK_LMENU;
        break;
    }

    if (down)
    {
        keyDown(vk);
    }
    else
    {
        keyUp(vk);
    }
}