#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heads.h"

/*Funcao que retorna o index da hashtable correspondente a um certo nome*/
int hashU(char *v, int HT_tam)
{
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a * b % (HT_tam - 1))
        h = (a * h + *v) % HT_tam;
    return h;
}

/*Funcao que compara duas strings de forma a ordenar por ordem alfabetica*/
int compare_strings(char *first, char *second)
{
    while (*first == *second)
    {
        if (*first == '\0' || *second == '\0')
            break;

        first++;
        second++;
    }
    if (*first == '\0' && *second == '\0')
        return 0;
    else
        return -1;
}
