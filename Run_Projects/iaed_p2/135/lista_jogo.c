#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_jogo.h"


/* Cria uma lista nova vazia */
list* cria_lista_dupla(){
    list * ls = malloc(sizeof(list));
    ls ->head = ls ->last = NULL;
    return ls;
} 

/* Adiciona a estrutura jogo na lista*/
el_lista_jogo* adiciona_elemento(list* l, pJogo j){
    el_lista_jogo *n = malloc(sizeof(el_lista_jogo));
    n->next = NULL;
    n->previous = l->last;
    n->j = j;
    if(l->last) l->last->next = n;
    l->last = n;
    if(!l->head) l->head = n;
    return n;
}

/* Liberta a toda memoria associada a um elemento da lista  */
void FREEel_lista(el_lista_jogo *t){
    FREEjogo(t->j);
    free(t);
} 

/* Remove um elemento da lista, fazendo a ligacao do anterior e do proximo */
void remove_elemento(list* l,  el_lista_jogo* elemento){
    if(!elemento->previous){
        l->head = elemento -> next;
    }else{
        elemento -> previous -> next = elemento -> next;
    }
    if(!elemento->next){
        l -> last = elemento -> previous;
    }else{
        elemento -> next -> previous = elemento -> previous;
    }
}

/* Imprime todos os jogos da lista por ordem de insercao */
void imprime_lista_jogo(list* l, const int n_comando){
    el_lista_jogo * x = l->head;
    
    for(; x != NULL; x = x->next){
        printf("%d %s %s %s %d %d\n", n_comando,
        x->j->nome, x->j->equipa1, x->j->equipa2, x->j->score1, x->j->score2);
    }
}

/* liberta a memoria associada a lista */
void FREElista(list* l){
    free(l);
}
