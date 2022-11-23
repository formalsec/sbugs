#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include "LL_equipas.h"

elem_eq* inicializa_lista_equipa() {
    elem_eq *ret;
    ret = NULL;
    return ret;
}

elem_eq* apaga_primeira_equipa_lista(elem_eq *cabeca) {
    elem_eq *antigo;
    if (cabeca != NULL) {
        /* Guarda a cabeca numa auxiliar */
        antigo = cabeca;
        /* Avanca com a cabeca da lista */
        cabeca = cabeca->prox;
        /* Apaga a memoria da equipa */
        liberta_equipa(antigo->equipa);
        free(antigo);
    }
    /* Retorna o novo ponteiro */
    return cabeca;
}

elem_eq* adiciona_equipa_lista(elem_eq *cabeca, Item_eq *equipa) {
    elem_eq *novo;
    /* Alocacao de memoria para o novo membro */
    novo = can_fail_malloc(sizeof(elem_eq));
    /* Alteracao de ponteiros para a equipa e para o proximo elemento */
    novo->equipa = equipa;
    novo->prox = cabeca;
    /* Retorno da lista atualizada */
    return novo;
}

elem_eq* apaga_lista_equipas(elem_eq *cabeca) {
    while (cabeca != NULL) {
        /* Apaga todos os elementos */
        cabeca = apaga_primeira_equipa_lista(cabeca);
    }
    return cabeca; /* NULL */
}

elem_eq* liberta_lista_equipas(elem_eq *cabeca) {
    elem_eq *antigo;
    while (cabeca != NULL) {
        /* Apaga todos os elementos, sem apagar a equipa dentro */
        antigo = cabeca;
        cabeca = cabeca->prox;
        free(antigo);
    }
    return cabeca; /* NULL */
}

elem_eq* encontra_equipa_lista(elem_eq *cabeca, char *nome) {
    while (cabeca != NULL) {
        if (!strcmp(nome_equipa(cabeca->equipa), nome)) {
            return cabeca; /* Caso encontre a equipa */
        }
        cabeca = cabeca->prox;
    }
    return NULL; /* Caso contrario */
}

elem_eq* prox_equipa(elem_eq *el) {
    return el->prox;
}

Item_eq* acede_equipa(elem_eq *el) {
    return el->equipa;
}

int tamanho(elem_eq *el) {
    int i = 0;
    while (el != NULL) {
        i++;
        el = el->prox;
    }
    return i;
}