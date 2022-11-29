#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hash.h"


unsigned int hash_jogo (char* name)
{
    /* Guarda comprimento do nome */
    int comp = strlen(name);

    int i, indice = 0;

    for (i = 0; i < comp; i++) {
        indice += name[i];
                                                /* Efetua operacoes com os carateres do nome */
        indice = (indice * name[i]) % TAB_SIZE; /* Devolve valor menor que tamanho da tabela */
    }

    return indice;
}

/* Extamanete igual ao hash_jogo mas para o tamanho da tabela de equipas */
unsigned int hash_equipa (char* name)
{
    int len = strlen(name);

    int i, indice = 0;

    for(i = 0; i < len; i++) {
        indice += name[i];

        indice = (indice * name[i]) % (TAB_SIZE / 2);
    }
    
    return indice;
}
