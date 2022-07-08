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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.style = CS_HREDRAW | CS_VREDRAW;     // ����WM_PAINT��Ϣʱ���»��ƣ�ˢ��
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
        PostQuitMessage(0);     // ������Ϣѭ��
        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);    // �رմ���
        return 0;

    case WM_LBUTTONDOWN:        // ����������ʱ
        // ��ȡ�������
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        // ��������������
        hdc = GetDC(hwnd);
        if (pPiano->IsHit(&pt))
        {
            pPiano->KeyDown(&pt, hdc);
        }
        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_LBUTTONUP:          // �������ɿ�ʱ
        // ��ȡ�������
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        hdc = GetDC(hwnd);
        if (pPiano->IsHit(&pt))
        {
            pPiano->KeyUp(hdc);
        }
        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_PAINT:              // �������»��Ƶ���Ϣ
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
        // ���ڱ仯
        pPiano->SetSize(&ps.rcPaint);
        pPiano->Paint(hdc);
        EndPaint(hwnd, &ps);
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}