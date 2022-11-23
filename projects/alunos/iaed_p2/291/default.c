#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "default.h"
int hashU(char *v)      /* funcao hash */
{
    int h, a = 31415, b = 27183;

    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
    h = (a*h + *v) % M;
    return h;
}