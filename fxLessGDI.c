#include <windows.h>

int main() {
    HDC hdc;

    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    int lessyY = 0;
    int lessyX = 0;

    while (1) {
        hdc = GetDC(0);
        BitBlt(hdc, lessyX, lessyY, w, h, hdc, 0, 0, SRCCOPY);
        lessyY = lessyY + 30;
        lessyX = lessyX + 30;
        Sleep(1000);
        ReleaseDC(0, hdc);
    }
}