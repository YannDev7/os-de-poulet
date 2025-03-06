#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

size_t strlen(char* a) {
    size_t len = 0;
    while (a[len])
        ++len;
    return len;
}

char* strcat(char* a, char* b) {
    int la = strlen(a);
    int lb = strlen(b);

    char* c = (char*)malloc((la + lb) * sizeof(char));
    for (int i = 0; i < la; i++)
        c[i] = a[i];
    for (int i = 0; i < lb; i++)
        c[i + la] = b[i];

    return c;
}