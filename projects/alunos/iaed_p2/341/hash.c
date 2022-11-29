#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hash.h"
/*Funcao simples de hash dada nos slides das aulas teoricas
recebe como argumentos um ponteiro para char(string) e um inteiro que
corresponde ao tamanho da Hash Table*/
int Hash(char *v ,int M){
    int h = 0, a = 127;
    
    for(;*v != '\0'; v++)
        h = (a*h + *v) % M;

    return h;
}