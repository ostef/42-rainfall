#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

int main(int argc, char **argv) {
    int value = atoi(argv[1]);

    if (value == 423) {
        char *command[2];
        command[0] = strdup("/bin/sh");
        command[1] = NULL;

        __gid_t gid = getegid();
        __uid_t uid = geteuid();

        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);

        execv("/bin/sh", &command);
    } else {
        fwrite("No !\n", 1, 5, stderr);
    }

    return 0;
}