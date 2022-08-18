#include "Function_Hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hashU(char *v, int M) {
    unsigned long h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a * b % (M - 1)) {
        h = (a * h + *v) % M;
    }
    return h;
}