#include "lists.h"

/* Creates a list and returns its address                                     */
list *list_init(){
    list *new;
    new = malloc(sizeof(list));
    new->head = NULL;
    new->tail = NULL;
    return new;
}

/* Creates node at the end of the list with given value                       */
lst_node *list_append(list *l, void *val){
    lst_node *new;

    new = malloc(sizeof(lst_node));
    new->next = NULL;
    new->prev = l->tail;
    new->value = val;

    if(l->tail != NULL)
        l->tail->next = new;
    else
        l->head = new;
    l->tail = new;
    
    return new;
}

/*Receives pointer to node, removes it and returns pointer to the changed list*/
list *remove_node(list *l, lst_node *nd){
    if (nd->prev != NULL)
        nd->prev->next = nd->next;
    else
        l->head = nd->next;

    if (nd->next != NULL)
        nd->next->prev = nd->prev;
    else
        l->tail = nd->prev;

    free(nd);
    return l;
}

/* Destroys list using given function to destroy the value of each node       */
void destroy_list(list *l, void (*del)(void *nd)){
    lst_node *cursor, *next;
    cursor = l->head;

    while(cursor != NULL){
        next = cursor->next;
        del(cursor->value);
        free(cursor);
        cursor = next;        
    }
    free(l);
    return;
}
