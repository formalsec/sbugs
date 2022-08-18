#include "hash.h"

int hash(char* text_sample, int dim) {

    int hash = 0, a = 127;

    while (*text_sample != '\0') {

        hash = (a*hash + *text_sample) % dim;
        ++text_sample;
    }
    return hash;
}