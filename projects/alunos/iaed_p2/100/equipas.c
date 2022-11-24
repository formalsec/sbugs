#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipas.h"

#define M 1049


/* Esta funcao inicializa a hastable das equipas. */

void hash_init_equipa(link_e* heads_equipas) {
    int i;
    for (i = 0; i < M; i++) heads_equipas[i] = NULL;
}


/* Esta funcao cria um noh com uma equipa e um ponteiro para o proximo noh. */

link_e NEW_equipa(equipa_ptr equipa_ptr) {
    link_e x = (link_e) can_fail_malloc(sizeof(node_e)); 
    x->e = equipa_ptr;
    x->next = NULL;
    return x;
}

/* Esta funcao insere um noh de uma equipa no inicio de uma lista. */

link_e insertBeginList_equipa(link_e head, equipa_ptr e) {
    link_e x = NEW_equipa(e);
    x->next = head;
    return x;
}

/* Esta funcao faz o hashing, retornando a key */

int hash_equipa(char *v) {
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
    h = (a*h + *v) % M;
    return h;
}

/* Esta funcao insere um noh de uma equipa na hashtable das equipas. */

void hash_insert_equipa(equipa_ptr e, link_e* heads_equipas) {
    int i = hash_equipa(e->nome);
    heads_equipas[i] = insertBeginList_equipa(heads_equipas[i], e);
}

/* Esta funcao procura uma equipa numa lista. */

equipa_ptr searchList_equipa(link_e head, char* nome_ptr) {
    link_e t;
    equipa_ptr e;
    for(t = head; t != NULL; t = t->next) {
        e = t->e;
        if(strcmp(e->nome, nome_ptr) == 0) return e;
    }
    return NULL;
}

/* Esta funcao procura uma equipa na hastable das equipas. */ 


equipa_ptr hash_search_equipa(char* nome, link_e* heads_equipas) {
    int i = hash_equipa(nome);
    return searchList_equipa(heads_equipas[i], nome);
}