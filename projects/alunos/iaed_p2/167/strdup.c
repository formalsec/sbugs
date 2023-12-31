#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "strdup.h"

char * d_strdup(char *src)
{
    char *str;
    char *p;
    int len = 0;

    while (src[len])
    { len++; }
    str = can_fail_malloc(len + 1);
    p = str;
    while (*src)
    { *p++ = *src++; }
    *p = '\0';
    return str;
}