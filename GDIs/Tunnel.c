#include <windows.h>

void tunnel_run() {
    HDC hdc = GetDC(NULL);

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    while(1) {
        HDC hdc = GetDC(NULL);

        int newW = w - (5 * w / 100);
        int newH = h - (5 * h / 100);

        // trova il centro
        int x = (w - newW) / 2;
        int y = (h - newH) / 2;

        StretchBlt(hdc, x, y, newW, newH, hdc, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
        Sleep(100);
    }
}