#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "func_hash.h"
#define SIZE 1009

int func_hash(char *chave)
{
    unsigned int valor = 0;
    unsigned int n = 103;
    for( ; *chave != '\0'; chave++)
        valor = (valor*n + *chave) % SIZE;
    return valor;
}