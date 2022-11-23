#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "codigoAux.h"
#include "equipa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Aloca memoria para uma equipa e inicializa-a */
equipa* criaEquipa(char* nome) {
    equipa* novaEquipa;
    novaEquipa = (equipa*)can_fail_malloc(sizeof(equipa));

    /* Aloca memoria para a string e inicializa-a */
    novaEquipa->nome = duplicaString(nome);
    novaEquipa->numeroVitorias = 0;

    return novaEquipa;
}

/* Liberta uma equipa e toda a memoria associada */
void freeEquipa(equipa* Equipa) {
    free(Equipa->nome);
    free(Equipa);
}

/* Imprime os parametros de uma equipa */
void printEquipa(equipa* Equipa, int* pNL) {
    printf("%d %s %d\n", *pNL, 
                         Equipa->nome, 
                         Equipa->numeroVitorias);
}
