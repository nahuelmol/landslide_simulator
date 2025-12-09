
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <Eigen/Dense>
#include <windows.h>
#include <winuser.h>

#include "models.h"
#include "export.h"
#include "plotting.h"

#ifndef UNICODE
#define UNICODE
#endif 

using Eigen::VectorXd;
using Eigen::MatrixXd;

LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    const char CLASS_NAME[]  = "Sample Window Class";
    HWND hwnd;
    MSG msg;

    std::string elements = "polygons";
    VectorXd L(10);
    MatrixXd Data(10,4);

    for(int i=0;i < 10;i++){
        Data(i,0) = float(i);
        Data(i,1) = 0;
        Data(i,2) = 0;
    }
    
    L << 1e-5, 1.5e-5, 1.7e-5, 1.7e-5, 1.84e-5, 1.33e-5, 1.29e-5, 1.21e-5, 1.2e-5, 1.17e-5;
    Data.col(3) = L;
    //make_csv(Data.col(0));
    //add_csv(Data.col(3));
    //implement();
    //initial_model(elements, Data);
    //plot("here.txt");
    
    WNDCLASS wc = {};
    wc.lpfnWndProc   = wndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if(!RegisterClass(&wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Learn to Program Windows",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 480, 240,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
        }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }

    return 0;
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

                EndPaint(hwnd, &ps);
            }
            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
