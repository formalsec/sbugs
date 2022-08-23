#include "hash.h"

int hash(char *v, int num) {
    /* Soma ponderada de todos os caracteres, modulo num */
    int sum = 0, mul = 127;
    while (*v != '\0') {
        sum = (mul * sum + *v) % num;
        v++;
    }
    return sum;
}