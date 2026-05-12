#include <windows.h>
#include <time.h>

void test(int secs) {
    HDC hdc = GetDC(NULL);
    SetBkMode(hdc, OPAQUE); // no bordi strani dietro
    SetTextColor(hdc, RGB(255,255,255)); // colore testo bianco
    
    int now = time(NULL);
    int future = now + secs;


    while(1) {
        TextOut(hdc, 50, 50, "COUNTDOWN: 10", 13); // pixel e dimensione test
    }
}

int main() {
    int secs;
    secs = 20;
    test(20);
    return 0;
}