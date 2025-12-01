#include <stdlib.h>
#include <stdio.h>

int run() {
    fwrite("Good... Wait what?\n", 1, 19, stdout);

    return system("/bin/sh");
}

int main(int argc, char** argv, char** envp) {
    char buf[64];

    return gets(&buf);
}
