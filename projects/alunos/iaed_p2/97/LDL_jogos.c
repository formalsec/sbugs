#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include "LDL_jogos.h"

lista* cria_lista_jogos() {
    lista *ret;
    /* Alocacao da memoria para a lista */
    ret = can_fail_malloc(sizeof(lista));
    /* Criacao dos ponteiros para o primeiro e ultimo elementos */
    ret->inicio = NULL;
    ret->fim = NULL;
    return ret;
}

void apaga_lista_jogos(lista *l) {
    elem_j* tmp;
    /* Caso a lista tenha mais que um elemento */
    if (l->fim != l->inicio) {
        /* Libertacao da memoria associada aos jogos e 
           aos elementos da lista contidos nestes */
        while(l->fim != l->inicio) {
            tmp = l->fim->ante;
            liberta_jogo(l->fim->jogo);
            free(l->fim);
            l->fim = tmp;
        }
        liberta_jogo(l->inicio->jogo);
        free(l->inicio);
    } else if (l->inicio != NULL) { /* Caso exista apenas um elemento */
        liberta_jogo(l->inicio->jogo);
        free(l->inicio);
    }
    free(l); /* Caso a lista esteja vazia, apenas esta instrucao e executada */
}

void liberta_lista_jogos(lista *l) {
    elem_j *aux = l->inicio, *tmp;
    /* Percorre os elementos todos e liberta-lhes a memoria */
    while (aux != NULL) {
        tmp = aux;
        aux = aux->prox;
        free(tmp);
    }
    free(l);
}

void adiciona_jogo_lista(lista *l, Item_j *el) {
    elem_j* add;
    /* Alocacao da memoria para o elemento da lista */
    add = can_fail_malloc(sizeof(elem_j));
    /* Atribuicao dos ponteiros para o elemento seguinte e anterior */
    add->jogo = el;
    add->prox = NULL;
    add->ante = l->fim;
    /* Atualizacao da lista para conter o elemento */
    if (l->fim != NULL) {
        l->fim->prox = add;
    }
    l->fim = add;
    if (l->inicio == NULL) {
        l->inicio = l->fim;
    }
}

void remove_jogo_lista(lista *l, elem_j *el) {
    if (l->inicio == el && l->fim == el) { /* Lista com apenas o elemento el */
        l->inicio = NULL;
        l->fim = NULL;
    } else if (l->inicio != el && l->fim != el) { /* Elemento fora das pontas */
        el->ante->prox = el->prox;
        el->prox->ante = el->ante;
    } else { /* Elemento numa das pontas da lista */
        if (l->inicio == el) {
            l->inicio = el->prox;
            l->inicio->ante = NULL;
        } 
        if (l->fim == el) {
            l->fim = el->ante;
            l->fim->prox = NULL;
        }
    }
    /* Depois de alterar a lista, libertar a memoria associada a el */
    free(el);
}

elem_j* encontra_jogo_lista(lista *l, char *nome) {
    elem_j *tmp;
    tmp = l->inicio;
    while (tmp != NULL) {
        if (EQ_JOGO(tmp->jogo, nome)) {
            return tmp; /* Caso se encontre o elemento pretendido */
        }
        tmp = tmp->prox;
    }
    return NULL; /* Caso contrario */
}

Item_j* acede_jogo(elem_j *el) {
    return el->jogo;
}

elem_j* acede_inicio_lista_jogos(lista *l) {
    return l->inicio;
}

elem_j* prox_elem(elem_j* el) {
    return el->prox;
}