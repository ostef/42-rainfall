#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int m;

int v() {
    int result;
    char s[512];

    fgets(s, 512, stdin);

    printf(s);
    result = m;

    if (m == 64) {
        fwrite("Wait what?!\n", 1, 12, stdout);
        return system("/bin/sh");
    }

    return result;
}

int main() {
    v();
}
