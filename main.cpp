#ifndef UNICODE
#define UNICODE
#endif // using unicode windows api
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#pragma comment (lib, "winmm.lib")

//#include "Key.h"
#include "Piano.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
template <typename F>
void UpdatePiano(HWND hwnd, LPARAM lparam, Piano* pPiano, F const& f);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.style = CS_HREDRAW | CS_VREDRAW;     // 发送WM_PAINT消息时重新绘制，刷新
    wc.hbrBackground = CreateSolidBrush(RGB(40, 44, 52));

    RegisterClass(&wc);
    
    Piano piano;
    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        &piano       // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    RECT rc;
    GetClientRect(hwnd, &rc);
    piano.SetSize(&rc);

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Piano* pPiano;
    HDC hdc;
    POINT pt;
    HDC mhdc;
    HBITMAP mbm;
    RECT rc;
    int width;
    int height;

    if (uMsg == WM_CREATE || uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pPiano = reinterpret_cast<Piano*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pPiano);
    }
    else
    {
        LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        pPiano = reinterpret_cast<Piano*>(ptr);

    }

    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);     // 结束消息循环
        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);    // 关闭窗口
        return 0;

    case WM_LBUTTONDOWN:        // 鼠标左键按下时
        UpdatePiano(hwnd, lParam, pPiano, [pPiano](LPPOINT pt, HDC hdc) {pPiano->OnKeyDown(pt, hdc); });
        return 0;

    case WM_LBUTTONUP:          // 鼠标左键松开时
        UpdatePiano(hwnd, lParam, pPiano, [pPiano](LPPOINT pt, HDC hdc) {pPiano->OnKeyUp(hdc); });
        return 0;

    case WM_PAINT:              // 窗口重新绘制的消息
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
        // 窗口变化
        pPiano->SetSize(&ps.rcPaint);
        pPiano->Paint(hdc);
        EndPaint(hwnd, &ps);
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// 使用缓冲绘制
template <typename F>
void UpdatePiano(HWND hwnd, LPARAM lParam, Piano* pPiano, F const& func)
{
    POINT pt;
    HDC hdc, mhdc;
    RECT rc;
    HBITMAP mbm;
    int width, height;
    // 获取鼠标坐标
    pt.x = LOWORD(lParam);
    pt.y = HIWORD(lParam);
    if (pPiano->IsHit(&pt))
    {
        hdc = GetDC(hwnd);
        GetWindowRect(hwnd, &rc);
        width = rc.right - rc.left;
        height = rc.bottom - rc.top;
        mhdc = CreateCompatibleDC(hdc);
        mbm = CreateCompatibleBitmap(hdc, width, height);
        SelectObject(mhdc, mbm);
        BitBlt(mhdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY);

        func(&pt, mhdc);
        
        BitBlt(hdc, 0, 0, width, height, mhdc, 0, 0, SRCCOPY);
        DeleteDC(mhdc);
        DeleteObject(mbm);
        ReleaseDC(hwnd, hdc);
    }
}