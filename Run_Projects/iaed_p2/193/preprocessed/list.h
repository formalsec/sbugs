#ifndef PROJECT2_LIST_H
#define PROJECT2_LIST_H

/*
 * Node's structure. The nodes chain represents the list.
 */
typedef struct node {
    void *dataPointer; /*The data pointer that the node will hold*/
    struct node *next; /*Pointer to the next node to build the list*/
} link;

/*
 * The List structure that keeps track of the head and tail.
 */
typedef struct list {
    link *head; /*List's head node*/
    link *tail; /*List's tail node*/
} List;

List *creatList();

void deleteList(List *list, void(freeFunction)(void *));

void listInsertEnd(List *list, void *dataPointer);

void listInsertBefore(List *list, link *nextNode, void *dataPointer);

void listRemoveElement(List *list, char *key, int(*compareFunction)(char *, void *),
                       void(freeFunction)(void *));

link *listSearch(List *list, char *key, int(*compareFunction)(char *, void *));

void listPrint(List *list, int *cmdCounter, void(printFunction)(void *, int *));

int isListEmpty(List *list);

#endif
