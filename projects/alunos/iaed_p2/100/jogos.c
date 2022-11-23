#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogos.h"

#define M 1049

/* Esta funcao inicializa a hastable dos jogos.*/

void hash_init_jogo(link* heads) {  
    int i;
    for (i = 0; i < M; i++) heads[i] = NULL;
}

/* Esta funcao cria um noh com um jogo e um ponteiro para o proximo noh. */

link NEW_jogo(jogo_ptr jogo_ptr) {
    link x = (link) can_fail_malloc(sizeof(node));
    x->j = jogo_ptr;
    x->next = NULL;
    return x;
}

/* Esta funcao insere um noh de um jogo no inicio de uma lista. */

link insertBeginList_jogo(link head, jogo_ptr j) {
    link x = NEW_jogo(j);
    x->next = head;
    return x;
}

/* Esta funcao insere um noh de um jogo no fim de uma lista. */

void insertEnd_lista(lst_ptr lista, jogo_ptr j) {
    link x;
    if(lista->head == NULL) { /* se a lista estava vazia, a head e a tail vao ter o novo jogo */
        lista->head = NEW_jogo(j);
        lista->tail = lista->head;       
        return;
    }

    /* caso contrario, basta dizer que o next da antiga tail eh o novo noh, que passa a ser a tail */

    x = lista->tail;
    x->next = NEW_jogo(j); 
    lista->tail = x->next;
    return;
}

/* Esta funcao faz o hashing, retornando a key */

int hash_jogo(char *v) {
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
    h = (a*h + *v) % M;
    return h;
}

/* Esta funcao insere um noh de um jogo na hashtable de jogos. */

void hash_insert_jogo(jogo_ptr j, link *heads_jogos) {
    int i = hash_jogo(j->nome); /* obter a key */
    heads_jogos[i] = insertBeginList_jogo(heads_jogos[i], j);
}

/* Esta funcao procura um jogo numa lista. */

jogo_ptr searchList_jogo(link head, char* nome_ptr) {
    link t;
    jogo_ptr j;
    for(t = head; t != NULL; t = t->next) {
        j = t->j;
        if(strcmp(j->nome, nome_ptr) == 0) return j; /* retorna o ponteiro para o jogo se existir */
    }
    return NULL; /* retorna NULL se nao existir */
}

/* Esta funcao procura um jogo na hastable dos jogos. */

jogo_ptr hash_search_jogo(char* nome, link* heads_jogos) {
    int i = hash_jogo(nome);
    return searchList_jogo(heads_jogos[i], nome);
}


/* Esta funcao remove um jogo da lista ligada com todos os jogos. */

void removeItemList_jogo(char* nome, lst_ptr lista) {
    link t, prev, t_aux;
    jogo_ptr j;
    for(t = lista->head, prev = NULL; t != NULL; prev = t, t = t_aux) {
        j= t->j;
        t_aux = t->next;
        if(strcmp(j->nome, nome) == 0) {

            /* ajustar os ponteiros da lista ligada */

            if(t == lista->head) 
                lista->head = t->next;
            else
                prev->next = t->next;
            if (t == lista->tail)
                lista->tail = prev;

            /* agora que os ponteiros foram ajustados na hash e lista, fazer os frees */

            free(j->nome); 
            free(j->equipa1);
            free(j->equipa2);
            free(j);
            free(t); 
        }
    }
    return;
}

/* Esta funcao remove um jogo da hastable e da lista ligada com todos os jogos,
   retornando a nova head da lista da hash em que se encontra. */

link removeItemList_jogo_hash(char* nome, link head, lst_ptr lista) {
    link t, prev, t_aux;
    jogo_ptr j;
    for(t = head, prev = NULL; t != NULL; prev = t, t = t_aux) {
        j= t->j;
        t_aux = t->next;
        if(strcmp(j->nome, nome) == 0) {

            /* ajustar os ponteiros na hastable */

            if(t == head) 
                head = t->next; 
            else
                prev->next = t->next;

            /* remover da lista ligada com todos os jogos */

            removeItemList_jogo(nome, lista); 
            free(t); /* o jogo ja foi libertado, so falta libertar o noh */
        }
   }
   return head;
}

/* Esta funcao remove um jogo da hastable e da lista ligada com todos os jogos. */

void hash_delete_jogo(char* nome, link* heads_jogos, lst_ptr lista) {
    int i = hash_jogo(nome);
    heads_jogos[i] = removeItemList_jogo_hash(nome, heads_jogos[i], lista);
}