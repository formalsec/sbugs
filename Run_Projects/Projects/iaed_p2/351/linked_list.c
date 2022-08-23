#include "linked_list.h"
#include <stdlib.h>

/* returns a pointer to a newly created list*/
l_list* create_l_list()
{
    l_list *list = calloc(1,sizeof(l_list));
    return list;
}

/* returns a pointer to a newly allocated l_node*/
l_node* create_l_node()
{
    l_node *ptr = calloc(1,sizeof(l_node));
    return ptr;
}

/* add the node to the list given*/
void l_list_add_node_end(l_list *list, l_node *node)
{
    if(list -> head == NULL) /* no elements in list */
    {
        list -> head = list -> last = node;
    }
    else
    {
        list -> last -> next = node;
        list -> last = node;
        node -> next = NULL;
    }
    list->n_elems++;
    return;
}

/* removes node from list */
void l_list_remove_node_only(l_list *list, l_node *node)
{
    l_node *prev,*curr;
    /* do if node is head*/
    if(list -> head == node)
    {
        /* node->next == NULL implies list is empty*/
        if(node-> next == NULL)
        {
            list -> head = NULL;
            list -> last = NULL;
            free(node);
            list->n_elems--;
            return;
        }
        else
        {
            list -> head = node -> next;
            free(node);
            list->n_elems--;
            return;

        }
    }
    /* follow the chain of nodes until node is found, then remove it
    if not found, doesnt eliminate anything*/
    for(prev = list->head,curr = list->head->next ;curr != NULL ; prev = curr, curr = curr->next)
    {
        if(curr == node)
        {
            prev->next = node->next;
            if(list->last == node) list->last = prev;
            free(node);
            list->n_elems--;
            return;
        }
    }
    return;
}

/* removes node from list and its info_struct
must provide a function to free info_struct */
void l_list_remove_node(l_list *list, l_node *node,void (*func)(void*))
{
    l_node *prev,*curr;
    /* do if node is head*/
    if(list -> head == node)
    {
        /* node->next == NULL implies list is empty*/
        if(node-> next == NULL)
        {
            list -> head = NULL;
            list -> last = NULL;
            func(node -> info_struct);
            free(node);
            list->n_elems--;
            return;
        }
        else
        {
            list -> head = node -> next;
            func(node -> info_struct);
            free(node);
            list->n_elems--;
            return;

        }
    }
    /* follow the chain of nodes until node is found, then remove it
    if not found, doesnt eliminate anything*/
    for(prev = list->head,curr = list->head->next ;curr != NULL ; prev = curr, curr = curr->next)
    {
        if(curr == node)
        {
            prev->next = node->next;
            if(list->last == node) list->last = prev;
            func(node->info_struct);
            free(node);
            list->n_elems--;
            return;
        }
    }
    return;
}

/* frees every node and the list itself */
void free_l_list_and_node_only(l_list *list)
{
    l_node *curr, *next;
    if(list == NULL) return;
    for(curr = list->head;curr != NULL;curr = next)
    {
        next = curr->next;
        l_list_remove_node_only(list,curr);
    }
    free(list);
    return;
}

/* frees every node, its info_struct and the list itself */
void free_l_list(l_list *list,void (*func)(void*))
{
    l_node *curr, *next;
    if(list == NULL) return;
    for(curr = list->head;curr != NULL;curr = next)
    {
        next = curr->next;
        l_list_remove_node(list,curr,func);
    }
    free(list);
    return;
}
