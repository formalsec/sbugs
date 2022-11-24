#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "listajogos.h"

/* Funcao que cria uma lista de ponteiros para jogos e retorna 
o ponteiro para a lista */
lista cria_lista_jogos(){
    lista ls = can_fail_malloc(sizeof(struct listajogos));

    ls->head = ls->last = NULL;
    return ls;

}

/* Funcao que adiciona um ponteiro para um jogo a lista */
linkjg add_lista(lista l, jogo *novo_jogo){

    linkjg new = can_fail_malloc(sizeof(struct nodejg));

    new->next = NULL;
    new->jogo = novo_jogo;
    
    if (l->head == NULL){
        l->head = l->last = new;
        new->prev = NULL;
    }
    
    else{
        l->last->next = new;
        new->prev = l->last;
        l->last = new;
    }
        
    return new;

}

/* Funcao que remove um ponteiro para um jogo da lista */
void remove_lista (linkjg no, lista l){

    if (no == l->head){
        l->head = l->head->next;
    }

    else if (no == l->last) {
        l->last = l->last->prev;
        l->last->next = NULL;
    }

    else {
        no->prev->next = no->next;
        no->next->prev = no->prev;
    }

    /* Apaga o jogo da memoria do sistema */
    free(no->jogo->nome);
    free(no->jogo->equipa1);
    free(no->jogo->equipa2);
    free(no->jogo);
    free(no);

}

