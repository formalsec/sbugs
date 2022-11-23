#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"

/* liberta a memoria alocada para um jogo */
void freeJogo(pJogo j){
    /* liberta o nome do jogo */
    free(j->nome); 
    /* liberta o nome das equipas do jogo */
    free(j->equipa1);
    free(j->equipa2);
    /* liberta o ponteiro para o jogo */
    free(j);
}

/* imprime um jogo */
void printJogo(pJogo j){
    printf("%s %s %s %d %d\n",j->nome,j->equipa1,j->equipa2,j->score1,j->score2);
}


/* cria um novo jogo */
pJogo newJogo(char*nome,char*equipa1,char*equipa2,int score1,int score2){
    /* aloca memoria para um jogo */
    pJogo new = (pJogo)can_fail_malloc(sizeof(struct jogo));

    /* aloca memoria para o nome do novo jogo e atribui-o */
    new->nome = (char*)can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(new->nome,nome);

    /* aloca memoria para o nome de cada uma das equipas e atribui-os  */
    new->equipa1 = (char*)can_fail_malloc(sizeof(char)*(strlen(equipa1)+1));
    strcpy(new->equipa1,equipa1);
    new->equipa2 = (char*)can_fail_malloc(sizeof(char)*(strlen(equipa2)+1));
    strcpy(new->equipa2,equipa2);

    /* atribui os scores das duas equipas */
    new->score1 = score1;
    new->score2 = score2;

    /* devolve o ponteiro para o novo jogo */
    return new;
}

