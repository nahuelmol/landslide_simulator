#include <iostream>
#include <stdio.h>
#include <windows.h>

void settings() {
}
void setup() {
}
void draw() {
}

bool running = true;

void* buffer_memory;
int buffer_width;
int buffer_height;

BITMAPINFO buffer_bitmap_info;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;
    switch (msg) {
        case WM_DESTROY: {
            running = false;
        } break;
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_SIZE: {
            RECT rect;
            GetClientRect(hwnd, &rect);
            buffer_width = rect.right - rect.left;
            buffer_height = rect.bottom - rect.top;
            int buffer_size = buffer_width * buffer_height * sizeof(unsigned int);
            //el pixel es del tamaño de un unsigned int (entero de 32 bits)
            if(buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);
            buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            //BITMAPINFO
            buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
            buffer_bitmap_info.bmiHeader.biWidth = buffer_width;
            buffer_bitmap_info.bmiHeader.biHeight = buffer_height;
            buffer_bitmap_info.bmiHeader.biPlanes = 1;
            buffer_bitmap_info.bmiHeader.biBitCount = 32;
            buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;
        } break;
        default: {
            result =  DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
    return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "LandslideSimulator";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        "Landslide Simulator",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        400,
        NULL,
        NULL,
        hInstance,
        0
    );
    HDC hdc = GetDC(hwnd);

    while(running) {
        //input
        MSG message;
        while(PeekMessage(&message, hwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        //Simulate
        unsigned int* pixel = (unsigned int*)buffer_memory;
        for(int y=0; y<buffer_height; y++) {
            for (int x=0; x<buffer_width; x++) {
                *pixel++ = 0xff5500;
            }
        }

        StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width, buffer_height, buffer_memory, &buffer_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }

    //ShowWindow(hwnd, nCmdShow);
    //UpdateWindow(hwnd);
}
