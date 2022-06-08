#include <windows.h>
#include <wchar.h>
#include "Key.h"

#pragma comment (lib, "winmm.lib")

BaseKey::BaseKey(int index) : 
    index(index + 1),
    keyDown(false),
    keyRc{0, 0, 0, 0}
{}

void BaseKey::KeyDown(POINT* pt, HDC hdc, HBRUSH hbr)
{
    if (!IsHit(pt))
    {
        return;
    }
    OnHit();
    OnPaint(hdc, hbr);
}

void BaseKey::KeyUp()
{
    keyDown = false;
}

void BaseKey::SetKeyRc(POINT* position, LONG width, LONG height)
{
    keyRc.left = position->x;
    keyRc.top = position->y;
    keyRc.right = position->x + width;
    keyRc.bottom = position->y + height;
}

bool BaseKey::IsHit(POINT* pt)
{
    keyDown = false;
    if (pt->x <= keyRc.right && pt->x >= keyRc.left && pt->y <= keyRc.bottom && pt->y >= keyRc.top)
    {
        keyDown = true;
    }
    return keyDown;
}

void BaseKey::OnPaint(HDC hdc, HBRUSH hbr)
{
    FillRect(hdc, &keyRc, hbr);
}

WhiteKey::WhiteKey(int idx) : BaseKey(idx)
{
    WCHAR cmd[128];
    swprintf_s(cmd, 128, L"open ./KeySound/wk%d.wav alias wk%d", index, index);
    mciSendString(cmd, NULL, 0, NULL);
}

void WhiteKey::OnHit()
{
    WCHAR cmd[128];
    swprintf_s(cmd, 128, L"seek wk%d to start", index);
    mciSendString(cmd, NULL, 0, NULL);
    swprintf_s(cmd, 128, L"play wk%d", index);
    mciSendString(cmd, NULL, 0, NULL);
}

BlackKey::BlackKey(int idx) : BaseKey(idx) 
{
    WCHAR cmd[128];
    swprintf_s(cmd, 128, L"open ./KeySound/bk%d.wav alias bk%d", index, index);
    mciSendString(cmd, NULL, 0, NULL);
}

void BlackKey::OnHit()
{
    WCHAR cmd[128];
    swprintf_s(cmd, 128, L"seek bk%d to start", index);
    mciSendString(cmd, NULL, 0, NULL);
    swprintf_s(cmd, 128, L"play bk%d", index);
    mciSendString(cmd, NULL, 0, NULL);
    BaseKey::index;
}
