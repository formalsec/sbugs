#ifndef LISTS
#define LISTS

#include <stdlib.h>

typedef struct lst_node {
    void *value;
    struct lst_node *prev, *next;
} lst_node;

typedef struct {
    lst_node *head, *tail;
} list;

list *list_init();
lst_node *list_append(list *, void *);
list *remove_node(list *, lst_node *);
void destroy_list(list *, void (*del)(void *));

#endif
