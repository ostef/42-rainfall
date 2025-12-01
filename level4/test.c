// gcc -m32 test.c

#include <stdio.h>

int m;

int main() {
    printf("a%1$hhnb%2$hhnAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1%4$hhnAa0Aa1Aa2Aa3Aa4Aa%3$hhn\n", ((char *)&m) + 3, ((char *)&m) + 2, ((char *)&m) + 1, ((char *)&m) + 0);
    printf("%x\n", m);

    if (m == 0x01025544) {
        printf("OK!\n");
    }
}