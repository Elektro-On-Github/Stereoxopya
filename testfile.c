#include <windows.h>

void wrongchoose() {
    UNLONGLONG elapsed = GetTickCount64();
    MessageBox(NULL, "Sai chi è lulù?", "Scegli", MB_OK | MB_ICONINFORMATION);
    MessageBox(NULL, "Mi dispiace, hai sbagliato", "LULU.EXE", MB_OK | MB_ICONINFORMATION);
    while(1) {
        if (GetTickCount64() - elapsed < 60000) {lulu();pixelate();}
        else if (GetTickCount64 - elapsed < 80000) {fkngmelter();}
    }
}

int main() {
    wrongchoose();
}