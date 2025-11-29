#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int m;

void p(char *s){
    printf(s);
}

void n() {
    char s[512];

    fgets(s, 512, stdin);
    p(s);

    if (m == 0x01025544) {
        system("/bin/cat /home/user/level5/.pass");
    }
}

int main() {
    n();
}

