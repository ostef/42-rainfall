#include <string.h>

typedef struct {
    int (*operator_plus)(void *a, void *b);
    int (*operator_minus)(void *a, void *b);
} BaseClass_VTable;

typedef struct {
    BaseClass_VTable *vtable;
    char annotation[100];
    int number;
} N;

static const BaseClass_VTable N_VTable = {
    N_operator_plus, N_operator_minus,
};

N *N_operator_new(int number) {
    N *result = (N *)malloc(sizeof(N));
    result->vtable = &N_VTable;
    result->number = number;

    return result;
}

int N_operator_plus(N *a, N *b) {
    return a->number + b->number;
}

int N_operator_minus(N *a, N *b) {
    return a->number - b->number;
}

void N_setAnnotation(N *n, const char *str) {
    memcpy(n->annotation, str, strlen(str));
}

int main(int argc, char **argv) {
    N *a = N_operator_new(5);
    N *b = N_operator_new(6);

    N_setAnnotation(a, argv[1]);

    b->vtable->operator_plus(b, a);
}
