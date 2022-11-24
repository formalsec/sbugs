#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>
#include <stdlib.h>
#include "item.h"

/* Funcao que calcula o indice onde colocar um item numa tabela */
int hash(char *str,int m){
    int h,a = 31415,b = 27183;
    for(h = 0; *str != '\0'; str++, a = a * b % (m-1))
        h = (a*h + *str) % m;
    return h;
}

/* Funcao que liberta toda a memoria de um item */
void libItem(dados *item){
    free(item->nome);
    free(item->eq1);
    free(item->eq2);
}
