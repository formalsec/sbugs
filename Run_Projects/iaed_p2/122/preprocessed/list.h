#ifndef LIST_H
#define LIST_H

typedef struct node {
    char* name;
    struct node* next;
} *link;

link insertEnd(link, char*);
link lookup(link, char*);
link delete(link, char*);
int isEmpty(link);
void destroy(link);

#endif