#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "listadupEQUIPA.h"

/* cria uma estrutura equipa */
Equipa * mk_equipa(char nome[MAXEQUIPA]){
    Equipa * novaEquipa = can_fail_malloc(sizeof(Equipa));
    novaEquipa->nome = can_fail_malloc(sizeof(char)*(strlen(nome)+1));
    memset(novaEquipa->nome,'\0', sizeof(char)*(strlen(nome)+1));
    strcpy(novaEquipa->nome, nome);
    novaEquipa->vitorias = 0;
    return novaEquipa;
}

/* cria lista duplamente ligada de equipas vazia */
list_equipa * mk_list_equipa(){
    list_equipa * newL = can_fail_malloc(sizeof(list_equipa));
    newL->head = NULL;
    newL->last = NULL;
    return newL;
}

/* acrescenta nova equipa no final da lista */
void add_last_equipa(list_equipa * l, Equipa * e){
    node_equipa * newNode = can_fail_malloc(sizeof(node_equipa));
    newNode->next = NULL;
    newNode->equipa = e;
    /* se lista estiver vazia */
    if (l->head == NULL && l->last == NULL){
        newNode->previous = NULL;
        l->head = newNode;
        l->last = newNode;
    }
    /* lista tem elementos */
    else{
        newNode->previous = l->last;
        l->last->next = newNode;
        l->last = newNode;
    }
}

/* liberta toda a memoria associada a uma equipa */
void free_equipa(Equipa * e){
    free(e->nome);
    free(e);
}

/* liberta toda a memoria associada a lista */
void free_list_equipa(list_equipa * l){
    node_equipa * newLast, * lastNode = l->last;
    /* lista vazia */
    if (l->head == NULL)
        free(l);
    else{
        /* liberta todos menos cabeca */
        while (lastNode != l->head){
            newLast = lastNode->previous;
            free_equipa(lastNode->equipa);
            free(lastNode);
            newLast->next = NULL;
            lastNode = newLast;
        }
        /* liberta cabeca */
        free_equipa(lastNode->equipa);
        free(lastNode);
        free(l);
    }
}