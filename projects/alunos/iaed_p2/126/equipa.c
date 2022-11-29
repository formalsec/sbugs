#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"



/* Recebe um nome e devolve uma nova equipa com esse nome */
Equipa nova_equipa(char *nome) {
    Equipa nova = (Equipa) can_fail_malloc(sizeof(struct eq));
    nova->nome = strdup(nome);
    nova->vitorias = 0;
    return nova;
}



/* Recebe uma equipa e devolve o seu nome */
char* nome_equipa(Equipa eq) {
    return eq->nome;
}



/* Recebe uma equipa e devolve o numero de jogos que esta ganhou */
int vitorias_equipa(Equipa eq) {
    return eq->vitorias;
}



/* Recebe uma equipa e um inteiro e soma o inteiro ao numero de vitorias da equipa */
void altera_vitorias_eq(Equipa eq, int v) {
    eq->vitorias += v;
}



/* Recebe uma equipa e apaga-a do sistema */
void apaga_equipa(Equipa eq) {
    free(eq->nome);
    free(eq);
}



/* Compara 2 equipas pelo nome e devolve a diferenca */
int compara_eq(const void *a, const void *b) {
    Equipa eq1, eq2;
    eq1 = *(Equipa*)a;
    eq2 = *(Equipa*)b;
    return strcmp(eq1->nome, eq2->nome);
}



/* Recebe um vetor de caracteres, guarda-o na memoria e devolve o ponteiro para o seu endereco */
char *strdup(const char *str) {
    int n = strlen(str) + 1;
    char *dup = can_fail_malloc(n);

    if(dup) {
        strcpy(dup, str);
    }
    return dup;
}


