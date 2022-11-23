#ifndef _GLL_
#define _GLL_

#include <stdio.h>
#include <stdlib.h>

typedef struct Node *Link;
typedef struct Node{
    void* data;
    int length; /* O primeiro elemento de uma lista ira guardar a length da lista aqui */
    Link next;
}Node;

/* Cria uma nova lista ligada */
Link linkedlist_create();

/* Adiciona um elemento a uma lista ligada */
void linkedlist_add_item(Link *,void *,int );

/* Remove,de uma lista ligada, o elemento de uma dada posicao */
void linkedlist_delete_item(Link *,int,void (void *));

/* Remove,de uma lista ligada, o primeiro elemento com informacao igual a dada */
void linkedlist_delete_item_cmp(Link *,void *,void *(void *),void(void*),int (void *,void *));

/* Liberta uma lista ligada */
void linkedlist_free(Link,void(void*));

/* Percorre uma lista ligada e realiza uma acao sobre cada item */
void linkedlist_traverse(Link ,void(void *));

/* Obtem a informacao da length de uma lista */
int  linkedlist_get_length(Link);

/* Altera a informacao da length de uma lista */
void linkedlist_set_length(Link,int);

/* Obtem um item de uma lista ligada consoante a posicao */
void *linkedlist_get_item(Link,int);

/* Obtem um item de uma lista ligada consoante a informacao */
void *linkedlist_get_item_cmp(Link ,void *,void *(void *),int (void *,void *));

/* Faz reset de uma lista */
Link linkedlist_reset(Link,void (void*));



#endif