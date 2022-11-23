#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "JogoLincado.h"

/* Funcao que gera uma lista lincada de Jogos. */
lista_jogo* gerar_lista_jogo(){
    lista_jogo *lista = can_fail_malloc(sizeof(lista_jogo));
    lista -> cabeca = lista -> ult = NULL;
    return lista;
}

/* Funcao que libera a memoria alocada por um no da lista lincada de Jogos. */
void liberar_no_jogo(no_jogo *n) {
    free(n->jogo->nome);
    free(n->jogo);
    free(n);
}

/* Funcao que libera a memoria alocada pela lista lincada.*/
void liberar_lista_jogo(lista_jogo *lista, int index) {
    no_jogo* temp;
    while (index != 0) {
        temp = lista->cabeca->prox;
        liberar_no_jogo(lista->cabeca);
        lista->cabeca = temp;
        index--;
    }
    free(lista);
}

/* Funcao que remove um no da lista de Jogos. */
void remover_no_jogo(lista_jogo *lista, no_jogo *n) {
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
    liberar_no_jogo(n);
}

/* Funcao que adiciona um no de Jogo ao final da lista lincada. */
void adicionar_ultimo_jogo(lista_jogo *lista, Jogo *jogo) {
    no_jogo *n = can_fail_malloc(sizeof(no_jogo));
    n -> ant = lista -> ult;
    n -> prox = NULL;
    n -> jogo = jogo;
    /* Se existir um ultimo no, transforma o no adicionado como o ultimo. */
    if (lista -> ult) 
        lista -> ult -> prox = n;
    lista->ult = n;
    /* Verifica se a lista eh vazia e transforma o no sua cabeca. */
    if (lista->cabeca == NULL)
        lista -> cabeca = n;
    
}

