#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Allocs the memory for the new node and defines its parameters.
 * Requires: Void pointer to the data to be stored.
 * Returns: The new link pointer created.
 */
link *createNode(void *dataPointer) {
    link *node = (link *) malloc(sizeof(link));
    node->dataPointer = dataPointer;
    node->next = NULL;
    return node;
}

/*
 * Frees the data of the node using the function provided. If the function is NULL the data will not be freed
 * only the node.
 * The free function its required since its unknown the data type at compile time so this function is required to free
 * efficiently the data.
 * Requires: the link pointer and the void pointer to the free function.
 */
void freeNode(link *node, void(*freeFunction)(void *)) {
    if (freeFunction != NULL) {
        freeFunction(node->dataPointer);
    }
    free(node->next);
    free(node);
}

/*
 * Allocs the needed memory to the new List pointer.
 * Defines its attributes, Head and Tail, as NULL.
 * Returns: the list pointer created.
 */
List *creatList() {
    List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

/*
 * Deletes the list by delete node by node using the 'freeNode' function with the 'freeFunction' provided.
 * Requires: the list pointer and the void pointer to the free function.
 */
void deleteList(List *list, void(*freeFunction)(void *)) {
    link *t;
    while (list->head != NULL) {
        t = list->head;
        list->head = list->head->next;
        t->next = NULL;
        freeNode(t, freeFunction);
    }
    free(list);
}

/*
 * Searches in the list for the node that contains de given key using the 'compareFunction'.
 * The compare function its required since its unknown the data type at compile time so this function is required to
 * compare efficiently the data with the key. This functions cannot be NULL.
 * Requires: a pointer to the list, char array with the key and a pointer to the compare function.
 * Returns: if a node is found returns its pointers otherwise returns NULL.
 */
link *listSearch(List *list, char *key, int(*compareFunction)(char *, void *)) {
    link *t;
    if (compareFunction == NULL) {
        return NULL;
    }
    for (t = list->head; t != NULL; t = t->next) {
        if (compareFunction(key, t->dataPointer)) {
            return t;
        }
    }
    return NULL;
}

/*
 * Inserts in the list the node at the end using the list's tail.
 * The last node next pointer becomes pointing to this new node and the list's tails becomes pointing to this new node.
 * The list can't be NULL.
 * This function requires the node to be created before its execution.
 * Requires: List pointer and the new node pointer.
 */
void listInsertEndNode(List *list, link *node) {
    if (list == NULL) {
        return;
    }

    if (list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
}

/*
 * Creates the node for the data pointer and inserts in the list using the functions 'listInsertEndNode'.
 * The list can't be NULL.
 * Requires: List pointer and the void pointer to the data.
 */
void listInsertEnd(List *list, void *dataPointer) {
    link *node;
    if (list == NULL) {
        return;
    }
    node = createNode(dataPointer);
    listInsertEndNode(list, node);
}

/*
 * Inserts in the list before the given node.
 * If the node give node is the head the new node becomes the list's head e the next points to the give next node,
 * Or if the previous node's next pointer starts pointing to the new node and the next pointer points to the given
 * next node.
 * This function requires the node to be created before its execution and the list and nodes cannot be NULL.
 * Requires: List pointer, nextNode pointer and the new node pointer.
 */
void listInsertBeforeNode(List *list, link *nextNode, link *node) {
    link *prev, *t;
    if (list == NULL || nextNode == NULL || node == NULL) {
        return;
    }
    for (t = list->head, prev = NULL; t != NULL; prev = t, t = t->next) {
        if (t == nextNode) {
            if (t == list->head) {
                node->next = t;
                list->head = node;
                break;
            } else {
                node->next = t;
                prev->next = node;
                break;
            }
        }
    }
}

/*
 * Creates the node for the data pointer and inserts int the list using 'listInsertBeforeNode'.
 * The list, node and data pointer cannot be NULL.
 * Requires: list pointer, the next node pointer and the data pointer.
 */
void listInsertBefore(List *list, link *nextNode, void *dataPointer) {
    link *node;
    if (list == NULL || nextNode == NULL || dataPointer == NULL) {
        return;
    }
    node = createNode(dataPointer);
    listInsertBeforeNode(list, nextNode, node);
}

/*
 *
 */
void listRemoveElement(List *list, char *key, int(*compareFunction)(char *, void *), void(freeFunction)(void *)) {
    link *t, *prev = NULL;
    for (t = list->head; t != NULL; prev = t, t = t->next) {
        if (compareFunction(key, t->dataPointer)) {
            if (t == list->head && t == list->tail) {
                list->head = NULL;
                list->tail = NULL;
            } else if (t == list->head) {
                list->head = list->head->next;
                t->next = NULL;
            } else if (t == list->tail) {
                list->tail = prev;
                prev->next = NULL;
            } else {
                prev->next = t->next;
                t->next = NULL;
            }
            freeNode(t, freeFunction);
            break;
        }
    }
}

/*
 * Prints the the list using the print function.
 * The print function its required since its unknown the data type at compile time so this function is required to print
 * correctly the data.
 * Requires: List pointer, a pointer to the command counter and a pointer to the print function.
 */
void listPrint(List *list, int *cmdCounter, void (*printFunction)(void *, int *)) {
    link *t;
    for (t = list->head; t != NULL; t = t->next) {
        printFunction(t->dataPointer, cmdCounter);
    }
}

/*
 * Check if the list's head is NULL to determine if is empty or not.
 * Returns: 1 if the list is empty 0 otherwise.
 */
int isListEmpty(List *list) {
    if (list->head == NULL) {
        return 1;
    }
    return 0;
}
