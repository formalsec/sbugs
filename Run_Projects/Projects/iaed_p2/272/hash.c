#include "hash.h"

/* Definicao da funcao da funcao para as hash */
int hash_str(const char*str) {
    int hash = 0;
    while(*str != '\0'){
        hash+= *str;
        str++;
    }
    return hash;
}
