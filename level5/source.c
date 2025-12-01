#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void o() {
    system("/bin/sh");
    _exit(1);
}

void n() {
    char s[512];

    fgets(s, 512, stdin);
    printf(s);
    exit(1);
}

int main(int argc, const char **argv, const char **envp) {
    n();
}
