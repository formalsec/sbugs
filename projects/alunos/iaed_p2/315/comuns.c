#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comuns.h"

int hash(char *v, int M)
{
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a*h + *v) % M;
    return h;
}

int hash1(char *v, int M){
    int h = hash(v,M);
    return 23*h+13;
}

char *reduce_string(char s[MAX_STRING]){
    int len = strlen(s);
    int i;
    char *t;
    t = can_fail_malloc((len+1)*sizeof(char));
    for(i = 0;i <len;i++)
        *(t+i) = s[i];
    *(t+i) = '\0';
    return t;
}

