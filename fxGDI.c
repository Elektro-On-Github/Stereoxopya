#include <windows.h>
#include <math.h>

int main() {
    // full screen si mangia
    HDC hdc = GetDC(NULL);

    // resolution dello scree
    int sw = GetSystemMetrics(SM_CXSCREEN); // width
    int sh = GetSystemMetrics(SM_CYSCREEN); // height

    // offset di spostamento, kustomizzali se vuoi
    int dx = 1;
    int dy = 2;
    float angle = 2; // posizione nel ciclo circolare
    int size = 1; //quanto e' grande il movimento circolare
    int speed = 2; // speed
    
    while (1) { // loop infernale, usa 1 invece di true perche' non volevo importare stdbool.h
        // copia i px da hdc (schermo) con offset di 0, 0, prende la reso (sw, sh). Incolla tutto su hdc (stesso schermo), su dx e dy, SRCCOPY significa che copia li.
        BitBlt(hdc, 0, 0, sw, sh, hdc, dx, dy, SRCCOPY);

        // cerchio perfetto con sin & cos, forza il valore finale a int, non float
        dx = (int)ceil(sin(angle) * size * 10);
        dy = (int)ceil(cos(angle) * size * 10);

        angle = angle + speed / 5.0f;

        if (angle > 3.14159f) {
            angle = -3.14159f;
        }

        Sleep(10); // sleepa per avoidare full load nella cpu, cosi' va piu' fluido. lesgo!
    }
    ReleaseDC(NULL, hdc);
    return 0;
}