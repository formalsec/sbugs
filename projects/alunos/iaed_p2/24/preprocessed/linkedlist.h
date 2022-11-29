#include "auxiliar.h"

typedef struct node
{
    char *key; /* The node has to store the key sinse it can not accsse it from the data pointer */
    void *data;
    struct node *next;
    struct node *next_order;
    struct node *prev_order;
} * Link;

Link newNode(char *key, void *data);

void freeNode(Link node);

void insertLL(Link *head, Link new);

Link searchLL(Link head, char *name);

void removeLL(Link *head, char *name);

void insertDLL(Link *first, Link *last, Link new);

void removeDLL(Link *first, Link *last, Link del);
