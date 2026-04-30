#include <windows.h>

int main() {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);

    int x = 3;
    int y = 3;

    int vx = 21;
    int vy = 21;

    while (1) {

        HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, white);

        Rectangle(hdc, x, y, x + 100, y + 100);

        // collisione destra/sinistra
        if (x + 100 >= w || x <= 0) {
            vx = -vx;
        }

        // collisione alto/basso
        if (y + 100 >= h || y <= 0) {
            vy = -vy;
        }

        x += vx;
        y += vy;
    }

    return 0;
}