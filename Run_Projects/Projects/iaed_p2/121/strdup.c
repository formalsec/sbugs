#include <string.h>
#include <stdlib.h>
#include "strdup.h"

/* Function that when given a string, allocates memory for that string */
char *mystrdup(char *source){
    /* Allocate memory */
    char *dest = (char*)malloc(sizeof(char)*(strlen(source)+1));
    /* Copy string onto the variable with the memory allocated */
    strcpy(dest, source);
    return dest;
}