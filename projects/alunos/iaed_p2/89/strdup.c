#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "strdup.h"

/* Allocs memory for a string. Returns a pointer to that memory */
char *my_strdup(char *source){
    char *new;
    char *_new;
    int len = strlen(source) + 1;

    new = can_fail_malloc(len + 1);
    _new = new;

    while (*source)
        *_new++ = *source++;
        
    *_new = '\0';
    return new;
}