#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "lista_j.h"

/*  Inicializa uma lista alocando o espaco suficiente */
lista* inic_lista(void){
    lista* l = can_fail_malloc(sizeof(lista));
    l->head = NULL; l->last = NULL;
    return l;
}

/*  Insere um jogo na lista de jogos inseridos como sendo o ultimo */
void push_last(jogo* j, lista* l){
    node* nn = can_fail_malloc(sizeof(node));    /* crio um no com o jogo */
    nn->prev = l->last;                 /* adiciono como ultimo elemento para manter a ordem */
    nn->next = NULL;
    nn->jogo = j;                       /* aponta para jogo */
    if (l->last) l->last->next = nn;            /* caso exista nao esteja vazia, normal */
    else l->head = nn;                          /* caso contrario, adiciona-o na cabeca */
    l->last = nn;
}

/*  Procura um jogo cujo nome e dado.
 *  Se nao existir retorna NULL, caso contrario devolve o no do jogo */
node* procura_l(const char* nome_j, lista* l){
    node* n;
    for (n = l->head; n; n = n->next){  /* percorre a lista ate encontrar o jogo */
        if (equal_j(n->jogo->nome, nome_j))
            return n;       /* devolve o no com o jogo */
    }return NULL;       /* nada se o nao encontrou */
}

/*  Remove um no com um jogo libertando a memoria respetiva dele */
void remove_node(node* n, lista* l){
    
    if (n->prev == NULL)            /* caso seja o primeiro no */
        l->head = n->next;          /* modifica cabeca */
    else n->prev->next = n->next;   /* desconecta esquerda n */
    
    if (n->next == NULL)            /* caso seja o ultimo no */
        l->last = n->prev;          /* modifica ultimo */
    else n->next->prev = n->prev;   /* desconecta direita n */
    
    free(n);                   /* liberta memoria de n */
}

/*  Liberta toda a memoria alocada dos nos e da lista */
void free_lista(lista* l){
    node* tmp;

    while (l->head){            /* percorre lista libertando memoria de cada no */
        tmp = l->head->next;    /* auxiliar para manter ligacao dos nos da lista ao */
        free(l->head);          /* libertar no nessa interacao*/
        l->head = tmp;          /* mantem ligacao */
    }
    free(l);                    /* liberta lista */
}