/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
*	マウスモジュール[mouse.cpp]
*
* 　Author  : Asuka Kuroda
* 　Date	: 2026/04/13
* ----------------------------------------------------------------------------------------------------------
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#include "mouse.h"

#include <windowsx.h>
#include <assert.h>

#define SAFE_CLOSEHANDLE(h) if(h){CloseHandle(h); h = NULL;}

static MouseState g_State = {};
static HWND g_Window = NULL;
static MousePositionMode  g_Mode = MODE_ABSOLUTE;
static HANDLE g_ScrollWheelValue = NULL;
static HANDLE g_RelativeRead = NULL;
static HANDLE g_AbsoluteMode = NULL;
static HANDLE g_RelativeMode = NULL;
static int g_LastX = 0;
static int g_LastY = 0;
static int g_RelativeX = INT32_MAX;
static int g_RelativeY = INT32_MAX;
static bool g_InFocus = true;

static void ClipToWindow();

void MouseInitialize(HWND window)
{
    RtlZeroMemory(&g_State, sizeof(g_State));

    assert(window != NULL);

    RAWINPUTDEVICE Rid;
    Rid.usUsagePage = 0x01 /* HID_USAGE_PAGE_GENERIC */;
    Rid.usUsage = 0x02     /* HID_USAGE_GENERIC_MOUSE */;
    Rid.dwFlags = RIDEV_INPUTSINK;
    Rid.hwndTarget = window;
    RegisterRawInputDevices(&Rid, 1, sizeof(RAWINPUTDEVICE));

    g_Window = window;
    g_Mode = MODE_ABSOLUTE;

    if (!g_ScrollWheelValue) { g_ScrollWheelValue = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_MODIFY_STATE | SYNCHRONIZE); }
    if (!g_RelativeRead) { g_RelativeRead = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_MODIFY_STATE | SYNCHRONIZE); }
    if (!g_AbsoluteMode) { g_AbsoluteMode = CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE); }
    if (!g_RelativeMode) { g_RelativeMode = CreateEventEx(nullptr, nullptr, 0, EVENT_MODIFY_STATE | SYNCHRONIZE); }

    g_LastX = 0;
    g_LastY = 0;
    g_RelativeX = INT32_MAX;
    g_RelativeY = INT32_MAX;

    g_InFocus = true;
}

void MouseFinalize()
{
    SAFE_CLOSEHANDLE(g_ScrollWheelValue);
    SAFE_CLOSEHANDLE(g_RelativeRead);
    SAFE_CLOSEHANDLE(g_AbsoluteMode);
    SAFE_CLOSEHANDLE(g_RelativeMode);
}

void GetMouseState(MouseState* pState)
{
    memcpy(pState, &g_State, sizeof(g_State));
    pState->positionMode = g_Mode;

    DWORD result = WaitForSingleObjectEx(g_ScrollWheelValue, 0, FALSE);
    if (result == WAIT_FAILED) { return; }

    if (result == WAIT_OBJECT_0) {

        pState->scrollWheelValue = 0;
    }

    if (pState->positionMode == MODE_RELATIVE) {

        result = WaitForSingleObjectEx(g_RelativeRead, 0, FALSE);
        if (result == WAIT_FAILED) { return; }

        if (result == WAIT_OBJECT_0) {
            pState->x = 0;
            pState->y = 0;
        }
        else {
            SetEvent(g_RelativeRead);
        }
    }
}

void MouseResetScrollWheelValue()
{
    SetEvent(g_ScrollWheelValue);
}

void SetMouseMode(MousePositionMode mode)
{
    if (g_Mode == mode)
        return;

    SetEvent((mode == MODE_ABSOLUTE) ? g_AbsoluteMode : g_RelativeMode);

    assert(g_Window != NULL);

    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_HOVER;
    tme.hwndTrack = g_Window;
    tme.dwHoverTime = 1;
    TrackMouseEvent(&tme);
}

bool MouseIsConnected()
{
    return GetSystemMetrics(SM_MOUSEPRESENT) != 0;
}

bool MouseIsVisible()
{
    if (g_Mode == MODE_RELATIVE) {
        return false;
    }

    CURSORINFO info = { sizeof(CURSORINFO), 0, nullptr, {} };
    GetCursorInfo(&info);

    return (info.flags & CURSOR_SHOWING) != 0;
}

void MouseSetVisible(bool visible)
{
    if (g_Mode == MODE_RELATIVE) {
        return;
    }

    CURSORINFO info = { sizeof(CURSORINFO), 0, nullptr, {} };
    GetCursorInfo(&info);

    bool isVisible = (info.flags & CURSOR_SHOWING) != 0;

    if (isVisible != visible) {
        ShowCursor(visible);
    }
}

void MouseProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    HANDLE evts[3] = {
        g_ScrollWheelValue,
        g_AbsoluteMode,
        g_RelativeMode
    };

    switch (WaitForMultipleObjectsEx(_countof(evts), evts, FALSE, 0, FALSE))
    {
    case WAIT_OBJECT_0:
        g_State.scrollWheelValue = 0;
        ResetEvent(evts[0]);
        break;

    case (WAIT_OBJECT_0 + 1):
    {
        g_Mode = MODE_ABSOLUTE;
        ClipCursor(nullptr);

        POINT point;
        point.x = g_LastX;
        point.y = g_LastY;

        // リモートディスクトップに対応するために移動前にカーソルを表示する
        ShowCursor(TRUE);

        if (MapWindowPoints(g_Window, nullptr, &point, 1)) {
            SetCursorPos(point.x, point.y);
        }

        g_State.x = g_LastX;
        g_State.y = g_LastY;
    }
    break;

    case (WAIT_OBJECT_0 + 2):
    {
        ResetEvent(g_RelativeRead);

        g_Mode = MODE_RELATIVE;
        g_State.x = g_State.y = 0;
        g_RelativeX = INT32_MAX;
        g_RelativeY = INT32_MAX;

        ShowCursor(FALSE);

        ClipToWindow();
    }
    break;

    case WAIT_FAILED:
        return;
    }

    switch (message)
    {
    case WM_ACTIVATEAPP:
        if (wParam) {

            g_InFocus = true;

            if (g_Mode == MODE_RELATIVE) {

                g_State.x = g_State.y = 0;
                ShowCursor(FALSE);
                ClipToWindow();
            }
        }
        else {
            int scrollWheel = g_State.scrollWheelValue;
            memset(&g_State, 0, sizeof(g_State));
            g_State.scrollWheelValue = scrollWheel;
            g_InFocus = false;
        }
        return;

    case WM_INPUT:
        if (g_InFocus && g_Mode == MODE_RELATIVE) {

            RAWINPUT raw;
            UINT rawSize = sizeof(raw);

            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &raw, &rawSize, sizeof(RAWINPUTHEADER));

            if (raw.header.dwType == RIM_TYPEMOUSE) {

                if (!(raw.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE)) {

                    g_State.x = raw.data.mouse.lLastX;
                    g_State.y = raw.data.mouse.lLastY;

                    ResetEvent(g_RelativeRead);
                }
                else if (raw.data.mouse.usFlags & MOUSE_VIRTUAL_DESKTOP) {

                    // リモートディスクトップなどに対応
                    const int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
                    const int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

                    int x = (int)((raw.data.mouse.lLastX / 65535.0f) * width);
                    int y = (int)((raw.data.mouse.lLastY / 65535.0f) * height);

                    if (g_RelativeX == INT32_MAX) {
                        g_State.x = g_State.y = 0;
                    }
                    else {
                        g_State.x = x - g_RelativeX;
                        g_State.y = y - g_RelativeY;
                    }

                    g_RelativeX = x;
                    g_RelativeY = y;

                    ResetEvent(g_RelativeRead);
                }
            }
        }
        return;


    case WM_MOUSEMOVE:
        break;

    case WM_LBUTTONDOWN:
        g_State.leftButton = true;
        break;

    case WM_LBUTTONUP:
        g_State.leftButton = false;
        break;

    case WM_RBUTTONDOWN:
        g_State.rightButton = true;
        break;

    case WM_RBUTTONUP:
        g_State.rightButton = false;
        break;

    case WM_MBUTTONDOWN:
        g_State.middleButton = true;
        break;

    case WM_MBUTTONUP:
        g_State.middleButton = false;
        break;

    case WM_MOUSEWHEEL:
        g_State.scrollWheelValue += GET_WHEEL_DELTA_WPARAM(wParam);
        return;

    case WM_XBUTTONDOWN:
        switch (GET_XBUTTON_WPARAM(wParam))
        {
        case XBUTTON1:
            g_State.xButton1 = true;
            break;

        case XBUTTON2:
            g_State.xButton2 = true;
            break;
        }
        break;

    case WM_XBUTTONUP:
        switch (GET_XBUTTON_WPARAM(wParam))
        {
        case XBUTTON1:
            g_State.xButton1 = false;
            break;

        case XBUTTON2:
            g_State.xButton2 = false;
            break;
        }
        break;

    case WM_MOUSEHOVER:
        break;

    default:
        // メッセージなし
        return;
    }

    if (g_Mode == MODE_ABSOLUTE) {

        // すべてのマウスメッセージに対して新しい座標を取得する
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);

        g_State.x = g_LastX = xPos;
        g_State.y = g_LastY = yPos;
    }
}

void ClipToWindow()
{
    assert(g_Window != NULL);

    RECT rect;
    GetClientRect(g_Window, &rect);

    POINT ul;
    ul.x = rect.left;
    ul.y = rect.top;

    POINT lr;
    lr.x = rect.right;
    lr.y = rect.bottom;

    MapWindowPoints(g_Window, NULL, &ul, 1);
    MapWindowPoints(g_Window, NULL, &lr, 1);

    rect.left = ul.x;
    rect.top = ul.y;

    rect.right = lr.x;
    rect.bottom = lr.y;

    ClipCursor(&rect);
}
