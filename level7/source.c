#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char c[80];

int32_t m() {
    return printf("%s - %d\n", &c, time(NULL));
}

int32_t main(int32_t argc, char** argv, char** envp) {
    char **a = malloc(8);
    a[0] = 1;
    a[1] = malloc(8);

    char **b = malloc(8);
    b[0] = 2;
    b[1] = malloc(8);

    strcpy(a[1], argv[1]);
    strcpy(b[1], argv[2]);
    FILE *file = fopen("/home/user/level8/.pass", "r");
    fgets(&c, 68, file);
    puts("~~");
    return 0;
}
