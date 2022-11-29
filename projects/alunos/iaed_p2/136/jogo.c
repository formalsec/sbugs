#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jogo.h"
#include "equipa.h"

/* NOTA: a referencia a jogo nao e a estrutura em si mas sim ao ponteiro */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de criacao - cria um jogo */
jogo cria_jogo(char * nome, equipa e1, equipa e2, int s1, int s2)
{
    jogo j; /* jogo a criar */

    j = can_fail_malloc(sizeof(struct str_jogo)); /* 1o reserva a memoria para o jogo */
    j->nome = can_fail_malloc((strlen(nome) + 1) * sizeof(char)); /* 2o "" para o nome */

    /* 3o atribui os componentes do jogo */
    EQ_1(j) = e1; /* a equipa 1 */
    EQ_2(j) = e2; /* a equipa 2 */
    j->s1 = s1; /* os golos da equipa 1 */
    j->s2 = s2; /* os golos da equipa 2 */
    strcpy(j->nome, nome); /* o nome do jogo */

    /* 4o atribui a vitoria ao vencedor - se houver */
    if (s1 > s2) /* no caso de a equipa 1 ter marcado mais golos */
        muda_vitorias(EQ_1(j), '+'); /* a equipa 1 tem mais 1 vitoria */
    else if (s2 > s1) /* no caso de a equipa 2 ter marcado mais golos */
        muda_vitorias(EQ_2(j), '+'); /* a equipa 2 tem mais 1 vitoria */

    return j; /* devolve o jogo */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de remocao/libertacao - liberta a memoria associada a um jogo */
void apaga_jogo(jogo j)
{
    if (j) /* se houver jogo a libertar */
    {
        free(j->nome); /* liberta o nome */
        free(j); /* e depois o jogo em si */
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* altera o score de um jogo */
void altera_score(jogo j, int s1, int s2)
{
    j->s1 = s1; /* o score da equipa 1 e alterado */
    j->s2 = s2; /* e o da equipa 2 tambem */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* equipa vencedora de um jogo */
equipa obtem_vencedora(jogo j)
{
    if (j->s1 > j->s2)
        return EQ_1(j); /* equipa 1 vencedora */
    else if (j->s1 < j->s2)
        return EQ_2(j); /* equipa 2 vencedora */
    else
        return NULL; /* empate - ninguem ganhou */
} 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* escreve um jogo no stdout */
void escreve_jogo(int nL, jogo j)
{
    printf("%d %s %s %s %d %d\n", nL, j->nome, j->e1->nome, j->e2->nome, j->s1, j->s2);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
