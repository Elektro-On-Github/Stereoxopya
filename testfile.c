#include <windows.h>
int w;
int h;

void image() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL); // piglia il dc dello schermo
    HDC memdc = CreateCompatibleDC(hdc); // crea un DC compatibile in ram

    //karika il bmp
    HBITMAP bmp = (HBITMAP)LoadImageA(NULL, "img1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // usa bitmap nel memdc
    SelectObject(memdc, bmp);

    BitBlt(hdc, 100, 100, 256, 256, memdc, 0, 0, SRCCOPY);


    //togli merda
    DeleteObject(bmp);
    DeleteDC(memdc);
    ReleaseDC(NULL, hdc);
}

int main() {
    while (1) {
        image();
    }
}