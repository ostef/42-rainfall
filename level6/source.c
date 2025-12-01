#include <stdlib.h>
#include <string.h>

int n() {
    return system("/bin/cat /home/user/level7/.pass");
}

int m() {
    return puts("Nope");
}

typedef int (**Func)();

int main(int argc, char** argv, char** envp) {
    char* str = malloc(64);
    Func func = malloc(sizeof(Func));

    *func = m;
    strcpy(str, argv[1]);

    return (*func)();
}
