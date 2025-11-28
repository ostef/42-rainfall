#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *p() {
    char s[76];

    fflush(stdout);
    gets(s);
    if ((*(unsigned int *)(s + 80) & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", s + 80);
        _exit(1);
    }

    puts(s);
    return strdup(s);
}

int main() {
    p();
}
