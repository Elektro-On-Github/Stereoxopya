#include <windows.h>
#include <math.h>
#include <curl/curl.h>
#include <unistd.h>

//globalz
int w; // width
int h; // heigh

void heightglitch_run() {
    HDC hdc = GetDC(NULL);
    int x = 0;

    x = rand() % w; // random lungo w
    BitBlt(hdc, x, 1, 10, h, hdc, x, 0, NOTSRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(10);
}

void widthglitch_run() {
    HDC hdc = GetDC(NULL);
    int x = 0;

    x = rand() % 2; // random lungo h
    BitBlt(hdc, 10, x, w, h, hdc, 0, x, NOTSRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(100);
}

void tunnel_run() {
    HDC hdc = GetDC(NULL);

    int newW = w - (1 * w / 100);
    int newH = h - (1 * h / 100);

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

    int dx = (int)(sin(angle) * 100);
    int dy = (int)(cos(angle) * 100);

    BitBlt(hdc, dx, dy, w, h, hdc, 0, 0, SRCCOPY);
    ReleaseDC(NULL, hdc);

    angle = angle + 0.1f;
}

void startfx() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    while(1) {
        heightglitch_run();
        widthglitch_run();
        tunnel_run();
        circleshake_run();
    }
}

int main() {
    CURL *kurl = curl_easy_init();

    if (kurl) {
        curl_easy_setopt(kurl, CURLOPT_URL, "http://127.0.0.1:5633/xyz" );
        curl_easy_perform(kurl);
        curl_easy_cleanup(kurl);
        sleep(1);
    } // fare output di curl
}
