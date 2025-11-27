#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char *auth;
char *service;

int main() {
    char s[136];

    while (true) {
        printf("%p, %p \n", auth, service);

        if (!fgets(s, 128, stdin)) {
            break;
        }

        if (!memcmp(s, "auth ", 5)) {
            auth = (char *)malloc(4);
            memset(auth, 0, 4);

            char *name = s + 5;
            if (strlen(name) <= 30) {
                strcpy(auth, name);
            }
        }

        if (!memcmp(s, "reset", 5)) {
            free(auth);
        }

        if (!memcmp(s, "service", 6)) {
            char *name = s + 7;
            service = strdup(name);
        }

        if (!memcmp(s, "login", 5)) {
            if (*((uint32_t *)auth + 8)) {
                system("/bin/sh");
            } else {
                fwrite("Password:\n", 1, 10, stdout);
            }
        }
    }
}
