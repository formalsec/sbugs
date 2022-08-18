#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "equipa.h"

/* liberta a memoria alocada para uma equipa */
void freeEquipa(pEquipa e){
    /* liberta o nome da equipa */
    free(e->nome);
    /* liberta o ponteiro para a equipa */
    free(e);
}

/* imprime uma equipa */
void printEquipa(pEquipa e){
    printf("%s %d\n",e->nome,e->vitorias);
}

/* cria uma nova equipa */
pEquipa newEquipa(char *nome){
    /* aloca memoria para uma equipa */
    pEquipa new = (pEquipa)malloc(sizeof(struct equipa));

    /* aloca memoria para o nome da equipa e atribui-o*/
    new->nome = (char*)malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(new->nome,nome);

    /* coloca o numero de vitorias da equipa a 0*/
    new->vitorias=0;

    /* devolve o ponteiro para a nova equipa */
    return new;
}
