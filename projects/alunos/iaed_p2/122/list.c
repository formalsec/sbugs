#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* frees a linked list node*/
void FREEnode(link t)
{
    free(t->name);
    free(t);
}

/* creates a new node for the linked list*/
link NEW(char* buffer) {
    link x = (link)can_fail_malloc(sizeof(struct node));
    x->name = (char*)can_fail_malloc(sizeof(char) * 1024);
    strcpy(x->name, buffer);
    x->next = NULL;
    free(buffer);
    return x;
}

/* inserts a match's name in the linked list*/
link insertEnd(link head, char* name) {
    link x;
    if(head == NULL)
        return NEW(name);
    for(x = head; x->next != NULL; x = x->next);
    x->next = NEW(name);
    return head;
}

/* searches for a match's name in the linked list*/
link lookup(link head, char* name) {
    link t;
    for(t = head; t != NULL; t = t->next)
        if(strcmp(t->name, name) == 0)
            return t;
    return NULL;
}

/* deletes a match's name from the linked list*/
link delete(link head, char* name) {
    link t, prev;
    for(t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if(strcmp(t->name, name) == 0) {
            if(t == head)
                head = t->next;
            else
                prev->next = t->next;
            FREEnode(t);
            break;
        }
    }
    return head;
}

/* checks if the linked list is empty*/
int isEmpty(link head) {
    return head == NULL;
}

/* destroys a linked list*/
void destroy(link head) {
    link aux;
    if(!isEmpty(head))
        while(head != NULL) {
            aux = head;
            head = head->next;
            free(aux->name);
            free(aux);
        }
    free(head);
}