#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Jogo.h"


/*Aloca memoria para um jogo e cria um novo jogo*/
jogo novoJogo(char *nom, equipa eq1, equipa eq2, int res1, int res2){
    jogo j = (jogo)can_fail_malloc(sizeof(struct jogo));
    j->nome=can_fail_malloc(sizeof(char)*(strlen(nom)+1));
    strcpy(j->nome,nom);
    j->equipa1 = eq1;
    j->equipa2 = eq2;
    j->score1=res1;
    j->score2=res2;

/*Incrementa o numero de vitorias de uma equipa na sua estrutura caso esta
    tenha vencido o novo jogo*/
    if (j->score1 > j->score2){
        j->equipa1->wins++;
    }
    else if(j->score1 < j->score2){
        j->equipa2->wins++;
    }


    return j;
}

/*Liberta a memoria alocada para um jogo*/
void freeJogo(jogo j){
    if(j){
        free(j->nome);
        free(j);
    }
}

/*Da print de um jogo*/
void printJogo(jogo j){
    if(j){
        printf("%s %s %s %d %d\n",j->nome,j->equipa1->nome,
        j->equipa2->nome,j->score1,j->score2);
    }
}