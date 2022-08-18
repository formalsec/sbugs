#include "strdup.h"
#include <string.h>
#include <stdlib.h>

/* duplicates a string*/
char* _strdup(char* original) {
    char* duplicate;
    int len;    /* length of the original string*/
    len = strlen(original);
    duplicate = malloc(len + 1);
    strcpy(duplicate, original);
    return duplicate;
}