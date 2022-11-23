#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "arvore.h"

#include <stdlib.h>
#include <string.h>

/* funcao de criacao - cria uma arvore contendo um no */
arvore * ARVinit(void * e)
{
    arvore * raiz; /* arvore a criar */

    raiz = can_fail_malloc(sizeof(arvore)); /* aloca a memoria */
    raiz->elem = e; /* atribui-lhe o valor/elemento */
    raiz->drt = raiz->esq = NOROOT; /* atribui as folhas (nao tem) */

    return raiz;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de libertacao - liberta a memoria associada a uma arvore */
void ARVclear(arvore * raiz)
{
    if (!raiz) return; /* se for uma arvore vazia nao ha nada a libertar */

    ARVclear(raiz->esq); /* libertamos a arvore da esquerda */
    ARVclear(raiz->drt); /* libertamos a arvore da direita */
    free(raiz); /* libertamos a raiz */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de adicao - adiciona um elemento a uma arvore */
arvore * ARVadd(arvore * raiz, void * e)
{
    /* NOTA: o elemento comparativo para a adicao e o NOME (ordem lexicografica) */
    int elm_comp; /* elemento comparativo - a calcular */

    if (!raiz) return ARVinit(e); /* se a arvore for vazia cria-se uma com a equipa */

    elm_comp = COMPARA(EQUIPA(raiz->elem)->nome, CHAVE_EQ(EQUIPA(e)));

    if (elm_comp > 0) /* significa que o nome da equipa vem antes do da raiz */
        raiz->esq = ARVadd(raiz->esq, e); /* adiciona-se a arvore esquerda */
    else if (elm_comp < 0)/* significa que o nome da equipa vem depois do da raiz */
        raiz->drt = ARVadd(raiz->drt, e); /* adiciona-se a arvore direita */
    /* iguais nunca vao ser porque nao ha duas equipas com o mesmo nome - apenas se coloca
    para o caso em que ha 1 equipa a adicionar e sem a condicao adiciona duas vezes */
    
    return raiz; /* com o elemento inserido ou na arvore esq ou drt */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* funcao de impressao - percorre a arvore e imprime os elementos com max vitorias */
void ARVprint(arvore * raiz, int nL)
{
    /* travessia In-Order da arvore */

    if (!raiz) return ; /* se nao houver nada a imprimir nao faz nada */

    ARVprint(raiz->esq, nL); /* imprime a arvore da esquerda */
    /* depois a raiz */
    escreve_equipa_g(nL, EQUIPA(raiz->elem)->nome);
    ARVprint(raiz->drt, nL); /* imprime a arvore da direita */
}


