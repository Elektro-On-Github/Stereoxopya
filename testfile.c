#include <time.h>
#include <stdio.h>
#include <unistd.h>

void countdown(int secs) { // passa secs da curl
    int now = time(NULL); //ora
    int future = now + secs; // secs futuri
    while (now < future) {
        sleep(1);
        now = time(NULL);
        printf("%d\n",future - now);
        fflush(stdout);
    }
}

int main() {
    countdown(100);
}