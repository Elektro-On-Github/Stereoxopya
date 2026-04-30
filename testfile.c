#include <windows.h>

int main() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);
    
    HDC hdc = GetDC(NULL);

    int x = 0;
    int y = 0;

    while (1) {
        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, white);

        Rectangle(hdc, x, y, x + 100, x + 50);
        x = x + 1;
        y = y + 1;
        Sleep(1);
    }
}