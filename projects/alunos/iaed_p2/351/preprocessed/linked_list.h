#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct l_node
{
    void *info_struct;
    struct l_node *next;
} l_node;


typedef struct l_list
{
    struct l_node *head;
    struct l_node *last;
    int n_elems;
} l_list;

l_list* create_l_list();
l_node* create_l_node();
void l_list_add_node_end(l_list *list, l_node *node);
void l_list_remove_node_only(l_list *list, l_node *node);
void free_l_list_and_node_only(l_list *list);
void l_list_remove_node(l_list *list, l_node *node,void (*free_info_struct)(void*));
void free_l_list(l_list *list,void (*free_info_struct)(void*));
#endif
