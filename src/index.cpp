
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <Eigen/Dense>
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <commctrl.h>
#include <stdio.h>

#include "resource.h"
#include "models.h"
#include "export.h"
#include "plotting.h"
#include "errors.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    const char CLASS_NAME[]  = "Sample Window Class";
    HWND hwnd;
    MSG msg;
    g_hInst = hInstance;

    //make_csv(Data.col(0));
    //add_csv(Data.col(3));
    //implement();
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
        CW_USEDEFAULT, CW_USEDEFAULT, 780, 540,
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


INT_PTR CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case IDOK:
                case IDCANCEL:
                    EndDialog(hwnd, 0);
                    return TRUE;
            }
            break;
        case WM_CLOSE:
            EndDialog(hwnd, 0);
            return TRUE;
    }
    return FALSE;
};

LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HWND hdraw;
    HWND htext;
    switch (uMsg) {
        case WM_CREATE:
            CreateWindow(
                "BUTTON",
                "Open Forward",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20,20,140,25,
                hwnd,
                (HMENU)ID_OPEN_DIALOG,
                g_hInst,
                NULL
            );
            hdraw = CreateWindow(
                "STATIC",
                NULL,
                WS_CHILD | WS_VISIBLE | SS_BLACKFRAME,
                20, 50, 400, 300,
                hwnd,
                (HMENU)1001,
                g_hInst,
                NULL
            );
            htext = CreateWindow(
                "STATIC",
                "Text",
                WS_CHILD | WS_VISIBLE,
                20, 360, 300, 25,
                hwnd,
                (HMENU)1002,
                g_hInst,
                NULL
            );
            break;
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
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_OPEN_DIALOG:
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
                    /*
                    DialogBoxParam(
                        g_hInst,
                        MAKEINTRESOURCE(DLG_MAIN),
                        hwnd,
                        DlgProc,
                        0
                    );*/
                    initial_model(elements, Data);

                    HWND parent = GetParent(htext);
                    if(parent != hwnd) {
                        std::cout << "err" << std::endl;
                        if(htext == NULL) {
                            std::cout << "double err" << std::endl;
                        }
                    }


                    /*if(result!=0){
                        std::cout << "correctly executed" << std::endl;
                    } else {
                        DWORD code = GetLastError();
                        char buffer[256];
                        FormatMessage(
                            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                            NULL,
                            code,
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                            buffer,
                            sizeof(buffer),
                            NULL
                        );
                        std::cout << "uncorrectly executed: " << buffer << std::endl;
                    }
                    ReleaseDC(htext, hdc);
                    */
                    break;
            }
            break;
        return 0;
   }
   return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
