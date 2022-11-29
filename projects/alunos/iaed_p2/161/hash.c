#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hash.h"

/* numeros iniciais para a e b */
#define A 31415
#define B 27813


/* gera uma hash a partir de uma string -------------------------------------------------------- */
int gera_hash(char* string, unsigned int modulo)
{
    int hash, a, b;
    
    hash = 0;
    a = A;
    b = B;
    
    for (; *string != '\0'; string++, a = a*b % (modulo))
        hash = (a*hash + *string) % modulo;
    
    return hash;
}