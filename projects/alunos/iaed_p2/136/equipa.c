#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "equipa.h"

/* NOTA: a referencia a equipa nao e a estrutura em si mas sim ao ponteiro */

/* funcao de criacao - cria uma equipa */
equipa cria_equipa(chave_eq nome)
{
    equipa aux; /* equipa a criar */

    aux = can_fail_malloc(sizeof(struct str_equipa)); /* 1o aloca a memoria */

    /* 2o aloca o espaco necessario para o nome e 3o atribui-lhe o valor */
    aux->nome = can_fail_malloc((strlen(nome) + 1) * sizeof(char));
    strcpy(aux->nome, nome);

    /* 4o inicializa as vitorias */
    aux->vitorias = 0;

    return aux; /* devolve a equipa criada */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de remocao/libertacao - liberta a memoria associada a uma equipa */
void apaga_equipa(equipa e)
{
    if (e) /* se houver equipa para libertar */
    {
        free(e->nome); /* primeiro liberta o nome */
        free(e); /* e depois o endereco em si */
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* incrementa/decrementa o numero de vitorias de uma equipa */
void muda_vitorias(equipa e, char op)
{
    /* consoante o operando atribui-lhe ou retira uma vitoria */
    switch(op)
    {
        case '+': /* atribui */
            e->vitorias++;
            break;
        case '-': /* retira */
            e->vitorias--;
            break;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* escrita de uma equipa no stdout - formatos do comando P */
void escreve_equipa(int nL, equipa e)
{
    printf("%d %s %d\n", nL, e->nome, e->vitorias);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* escrita do nome de uma equipa - formatos do comando g*/
void escreve_equipa_g(int nL, chave_eq nome)
{
    /* NOTA: a escrita e feita nos formatos de saida do comando g, uma vez que e o unico
    que utilizara esta funcao */
    printf("%d * %s\n", nL, nome);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
