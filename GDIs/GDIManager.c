#include <windows.h>
#include <math.h>

//globalz
int w;
int h;

void heightglitch_run() {
    HDC hdc = GetDC(NULL);
    int x = 0;

    x = rand() % w; // random lungo w
    BitBlt(hdc, x, 1, 10, h, hdc, x, 0, NOTSRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(10);
}

void tunnel_run() {
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

void circleshake_run() {
    HDC hdc = GetDC(NULL);
    static float angle = 0.0f;

    int dx = (int)(sin(angle) * 10);
    int dy = (int)(cos(angle) * 10);

    BitBlt(hdc, dx, dy, w, h, hdc, 0, 0, SRCCOPY);
    ReleaseDC(NULL, hdc);

    angle = angle + 0.1f;
}

int main() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    while(1) {
        heightglitch_run();
        tunnel_run();
        circleshake_run();
    }
}