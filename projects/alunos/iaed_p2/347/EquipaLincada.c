#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include "EquipaLincada.h"

/* Funcao que gera uma lista lincada de Equipas. */
lista_equipa* gerar_lista_equipa(){
    lista_equipa *lista = can_fail_malloc(sizeof(lista_equipa));
    lista -> cabeca = lista -> ult = NULL;
    return lista;
}

/* Funcao que libera a memoria alocada por um no da lista lincada de Equipas. */
void liberar_no_equipa(no_equipa *n) {
    free(n -> equipa->nome);
    free(n -> equipa);
    free(n);
}

/* Funcao que libera a memoria alocada pela lista lincada.*/
void liberar_lista_equipa(lista_equipa *lista) {
    while (lista -> cabeca) {
        no_equipa* temp = lista -> cabeca -> prox;
        liberar_no_equipa(lista -> cabeca);
        lista -> cabeca = temp;
    }
    free(lista);
}

/* Funcao que remove um no da lista de Equipas. */
void remover_no_equipa(lista_equipa *lista, no_equipa *n) {
    /* Se o no eh o primeiro da lista, faz com que o segundo se torne a cabeca. */
    if (n -> ant == NULL) {
        lista -> cabeca = n -> prox;
    }
    else {
        n -> ant -> prox = n -> prox;
    }
    /* Se o no eh o ultimo da lista, faz com que o no anterior seja o ultimo. */
    if (n -> prox == NULL) {
        lista -> ult = n -> ant;
    }
    else
        n->prox->ant = n->ant;
    liberar_no_equipa(n);
}

/* Funcao que adiciona um no de Equipa ao final da lista lincada. */
void adicionar_ultimo_equipa(lista_equipa *lista, Equipa *equipa) {
    no_equipa *n = can_fail_malloc(sizeof(no_equipa));
    n -> ant = lista -> ult;
    n -> prox = NULL;
    n -> equipa = equipa;
    /* Se existir um ultimo no, transforma o no adicionado como o ultimo. */
    if (lista -> ult) lista -> ult -> prox = n;
    lista->ult = n;
    /* Verifica se a lista eh vazia e transforma o no sua cabeca. */
    if (lista->cabeca == NULL)
        lista -> cabeca = n;
}
