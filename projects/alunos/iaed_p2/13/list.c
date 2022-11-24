#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hash.h"


static List head = NULL; /* Pointer to first element in list */
static List tail = NULL; /* Pointer to last element in list */ 


/* Add given Game to linked list and hash map
*/
void add(item game) {
    List new = (List) can_fail_malloc(sizeof(struct list));

    new->prev = NULL;
    new->next = NULL;
    new->game = game;

    /* Insert Game in hash map */
    hashInsertGame(game);

    /* If list is empty */
    if(head == NULL) {
        head = new; 
        tail = new;
        return;
    }

    tail->next = new;
    new->prev = tail;
    tail = new;
    return;
}

/* Clear list and free all list nodes.
 * Game nodes are not freed because Hash clearing function has already done it.
*/
void cleanList() {
    List aux, next;
    for(aux = head; aux != NULL; aux = next) {
        /* Needed for increment section of the for cycle */
        next = aux->next; 
        free(aux);
    }
}

/* Print all Games in chronological order 
*/
void printList(int lineNumber) {
    List aux;
    for(aux = head; aux != NULL; aux = aux->next) {
        item game = aux->game;
        printGame(lineNumber, game);
    }
}

/* Remove Game with specified name "str" from the list
*/
void listRemove(char *str) {
    List aux;

    for(aux = head; aux != NULL; aux = aux->next)
        if(!strcmp(str, getName(aux->game))) {
            if(aux->prev == NULL) /* If Game is the first in the list */ 
                head = aux->next; /* Set first element pointer to second element */
            else 
                (aux->prev)->next = aux->next;
            
            if(aux->next == NULL) /* If Game is the last in the list */
                tail = aux->prev; /* Set last element pointer to second to last element */
            else
                (aux->next)->prev = aux->prev;
                        
            free(aux);
            break;
        }
}