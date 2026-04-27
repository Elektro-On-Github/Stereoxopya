// BitBlt(hdcDest, xDest, yDest, width, height, hdcSrc, xSrc, ySrc, rasterOp);

#include <windows.h>

void heightglitch_run() {
    HDC hdc;

    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    int x = 0;

    while (1) {
        hdc = GetDC(0);
        x = rand() % w; // random lungo w
        BitBlt(hdc, x, 1, 10, h, hdc, x, 0, NOTSRCCOPY);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}