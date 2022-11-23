#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "games.h"


/* Creates an match and returns it */
match creates_match(char* name, char* team1, char* team2,
                    int score1, int score2) {

    /* Initializes match and allocates memory for it */
    match new = (match) can_fail_malloc(sizeof(struct my_game));

    /* Stores match's name */
    new->name = name;

    /* Stores team1's name */
    new->team1 = team1;

    /* Stores team2's name */
    new->team2 = team2;

    /* Stores team1's score */
    new->score1 = score1;

    /* Stores team2's score */
    new->score2 = score2;

    /* Returns created match */
    return new;

}



/* Deletes match */
void deletes_match(match game) {

    /* Clears match's memory if it is not NULL*/
    if (game) {
        free(game->name);
        free(game->team1);
        free(game->team2);
        free(game);
    }

}


/* Creates a doubly linked list */
dl_list create_dl_list() {

    /* Creates and allocates memory for a new list */
    dl_list lst = can_fail_malloc(sizeof(struct doubly_linked_list));

    /* Since it was just created, it has 0 elements inside */
    lst->size = 0;

    /* Head and Tail point to NULL at the creation of the list */
    lst->head = NULL;
    lst->tail = NULL;

    /* Returns created list */
    return lst;
}


/* Creates a new node at requested position of the list */
dl_link create_dl_node(dl_link next, dl_link previous, match game) {

    /* Creates and allocates memory for a new node */
    dl_link new = can_fail_malloc(sizeof(struct dl_node));

    /* Saves game inside node */
    new->value = game;

    /* Points to next node on the list */
    new->next = next;

    /* Points to previous node on the list */
    new->previous = previous;

    /* If the node was created in the middle of the list we have to change
     * previous and next's pointing directions towards the created node */
    if (previous != NULL) { previous->next = new; }
    if (next != NULL) { next->previous = new; }

    /* Returns the created node */
    return new;
}


/* Deletes a node */
void deletes_dl_node(dl_link node) {

    /* Frees match's memory */
    deletes_match(get_node_match(node));

    /* Frees node's memory */
    free(node);

}


/* Returns size of list, if list is invalid, returns zero */
int dl_list_length(dl_list lst) { return lst != NULL ? lst->size : 0; }


/* Verifies if list is empty */
int dl_list_is_empty(dl_list lst) { return dl_list_length(lst) == 0; }


/* Verifies if list is valid */
int dl_list_is_valid(dl_list lst) { return lst != NULL ? 1 : 0; }


/* Gets match inside node */
match get_node_match(dl_link node) { return node != NULL ? node->value : NULL; }


/* Puts game at the start of the list */
void insert_begin(dl_list lst, match game) {

    /* Creates a new node to be put at the start of list */
    dl_link new = create_dl_node(lst->head, NULL, game);

    /* Head now points to the new node */
    lst->head = new;

    /* If list is empty, tail is also the new node */
    if (dl_list_is_empty(lst)) { lst->tail = new; }

    /* Updates list size */
    lst->size++;
}


/* Removes first node from list. If is empty, interrupts */
void remove_begin(dl_list lst) {

    /* Holds node that is going to be removed */
    dl_link old_head = NULL;

    /* If list is not valid, interrupts execution */
    if ( ! dl_list_is_valid(lst) || dl_list_is_empty(lst)) return ;

    /* Gets old head */
    old_head = lst->head;

    /* Changes head to it's next node */
    lst->head = old_head->next;

    /* If list is not empty, update head's pointer. Else, reset tail */
    if(lst->head != NULL) {
        lst->head->previous = NULL;
    } else {
        lst->tail = NULL;
    }

    /* Deletes node */
    deletes_dl_node(old_head);

    /* Decreases size because we removed one node */
    lst->size--;

}


/* Removes element at the end of the list */
void remove_end(dl_list lst) {

    /* Holds node that is going to be removed */
    dl_link old_tail = NULL;

    /* If list is not valid, interrupts execution */
    if (!dl_list_is_valid(lst) || dl_list_is_empty(lst)) return ;

    /* Gets old tail */
    old_tail = lst->tail;

    /* Changes tail to it's previous node */
    lst->tail = old_tail->previous;

    /* If list is not empty, update tail's pointer. Else, reset head */
    if (lst->tail != NULL) {
        lst->tail->next = NULL;
    } else {
        lst->head = NULL;
    }

    /* Frees node's memory */
    deletes_dl_node(old_tail);

    /* Updates size of list */
    lst->size--;
}


/* Removes node from list */
void remove_node(dl_list lst, dl_link del_node) {

    /* If list is not valid, interrupts */
    if ( ! dl_list_is_valid(lst) || dl_list_is_empty(lst)) return ;

    /* If key was not found, interrupts execution */
    if (del_node == NULL) return ;

    /* Deletes node and updates size */
    if (del_node == lst->head) {

        remove_begin(lst);

    } else if (del_node == lst->tail) {

        remove_end(lst);

    } else {

        /* Updates adjacent node's pointers */
        del_node->previous->next = del_node->next;
        del_node->next->previous = del_node->previous;

        /* Frees node's memory */
        deletes_dl_node(del_node);

        /* Updates size */
        lst->size--;

    }


}


/* Destroys list, clearing all memory */
void dl_list_destroy(dl_list lst) {

    /* Variables used to clear list according to standard deleting algorithm */
    dl_link ite, ite_aux;

    /* If list is not valid, interrupts */
    if ( !dl_list_is_valid(lst)) return ;

    /* If list is not empty, runs through all nodes of the list and
     * deletes each one of them */
    if ( !dl_list_is_empty(lst)) {

        for (ite = lst->head, ite_aux = lst->head->next;
             ite != NULL;
             ite_aux = ite->next, deletes_dl_node(ite), ite = ite_aux)

            ;

    }

    /* Frees list pointer's memory allocation */
    free(lst);

}
