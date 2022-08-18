#include "linkedlist.h"

/* funcao que inicializa a lista ligada */
list* mk_list(){

    list* l = malloc(sizeof(list));
    l->head = l->last = NULL;
    return l; 
}

/* funcao auxiliar que recebe n e que apaga esse mesmo node */ 
void free_node(node1* n){

    free(n->Jogo->nome);
    free(n->Jogo);
    free(n);
}

/* funcao que recebe uma lista e que apaga essa mesma lista */
void free_list(list* l){
    
    while (l->head){
        node1* tmp = l->head->next;
        free_node(l->head);
        l->head = tmp;
    }
    free(l);
}

/* funcao que recebe uma lista e n e que apaga n da lista */
void rm_node(list* l, node1* n){

    if (n->prev == NULL){
        l->head = n->next;
    }
    else {
        n->prev->next = n->next;
    }
    if (n->next == NULL){
        l->last = n->prev;
    }
    else {
        n->next->prev = n->prev;
    }
    free_node(n);
}

/* funcao que recebe uma lista e uma string e que adiciona no fim
   da lista ligada o node que guarda o jogo */
void add_last(list* l, char* n){

    node1* nn = malloc(sizeof(node1));
    nn->prev = l->last;
    nn->next = NULL;
    nn->Jogo = malloc(sizeof(pJogo));
    nn->Jogo->nome = malloc(sizeof(char)*(strlen(n)+1));
    strcpy(nn->Jogo->nome, n);
    if (l->last){
        l->last->next = nn;
    }
    else {
        l->head = nn;
    }
    l->last = nn;
}

/* funcao que recebe uma lista e uma string e que devolve o node da lista
   que tem o nome igual a string recebida */
link1 search(list* l, char* n){
    
    link1 x;
    for (x = l->head; x != NULL; x = x->next){
        if (strcmp(x->Jogo->nome, n) == 0){
            return x;
        }
    }
    return NULL;
}