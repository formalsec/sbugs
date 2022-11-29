#ifndef _GBT_
#define _GBT_

#include "Generic_Linked_List.h"
#include <string.h>

typedef struct BTnode* BTlink;
typedef struct BTnode{
    void *data;
    BTlink r;
    BTlink l;
    int height;
} BTnode;

/* Cria uma nova arvore binaria e retorna o Link para o primeiro elemento */
BTlink bintree_create();

/* Procura por um elemento na arvore binaria e retorna um ponteiro generico para a informacao deste. */
void *bintree_search(BTlink ,void *,void *(void*),int (void *,void*));

/* Retorna o Link do elemento com maior valor de uma arvore binaria */
BTlink bintree_max(BTlink);

/* Retorna o Link do elemento com menor valor de uma arvore binaria */
BTlink bintree_min(BTlink);

/* Liberta uma arvore binaria. */
void bintree_free(BTlink,void (void *));

/* Adiciona um novo elemento a uma arvore binaria */
int bintree_add_item(BTlink*,void *,int ,void (void *),void *(void*),int (void*,void*));

/* Elimina um elemento da lista; */
void bintree_delete_item(BTlink* ,void *,void *(void*),void (void *),int (void *,void*));

/* Copia a informacao de uma arvore binaria para um array */
void bintree_array(BTlink ,void **,int);

/* Cria uma lista e percorre a arvore binaria. Para cada elemento e realizada a funcao condition que atua sobre o elemento e a lista criada. */
Link bintree_to_list_condition(BTlink ,void (void *,Link*));

#endif