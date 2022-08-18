#include <stdlib.h>
#include <string.h>
#include "teams.h"


/* Creates a new team */
fut_team creates_team(char* name) {

    /* Initializes new team and allocates memory for it */
    fut_team new = calloc(1, sizeof(struct my_team));

    /* Stores team's name */
    new->name = name;

    /* Since it was just created, it has no victories */
    new->victories = 0;

    /* Returns newly created team */
    return new;
}


/* Deletes team */
void deletes_team(fut_team team) {

    /* If team is not NULL, frees it's memory */
    if (team) {
        free(team->name);
        free(team);
    }

}


/* Returns size of list */
int sl_list_length(sl_list lst) { return lst != NULL ? lst->size : 0; }


/* Verifies if list is empty */
int sl_list_is_empty(sl_list lst) { return sl_list_length(lst) == 0; }


/* Verifies if list is valid */
int sl_list_is_valid(sl_list lst) { return lst != NULL ? 1 : 0; }


/* Gets team inside node */
fut_team get_node_team(sl_link node) {
    return node != NULL ? node->value : NULL;
}


/* Creates a singly linked list */
sl_list create_sl_list(){

    /* Creates and allocates memory for a new list */
    sl_list new_list = calloc(1, sizeof(struct singly_linked_list));

    /* Since it was just created, it has 0 elements inside */
    new_list->size = 0;

    /* Head points to NULL at the creation of the list */
    new_list->head = NULL;

    /* Returns created list */
    return new_list;
}


/* Creates a new node */
sl_link create_team_node(sl_link next, fut_team team) {

    /* Creates and allocates memory for a new layer */
    sl_link new = calloc(1, sizeof(struct sl_node));

    /* Stores team inside node */
    new->value = team;

    /* Changes pointing direction to next node */
    new->next = next;

    return new;
}


/* Deletes node of list */
void delete_sl_node(sl_link node) {

    /* Frees team's memory */
    deletes_team(get_node_team(node));

    /* Frees node's memory */
    free(node);

}


/* Inserts a team at the beginning of the list */
void insert_team_begin(sl_list lst, fut_team team) {

    /* Creates a new node to be put at the start of list */
    sl_link new = create_team_node(lst->head, team);

    /* List's head is the new node */
    lst->head = new;

    /* Updates list's size */
    lst->size++;
}


/* Destroys list, clearing all memory */
void sl_list_destroy(sl_list lst) {

    /* Variables used to clear list according to standard deleting algorithm */
    sl_link ite, ite_aux;

    /* If list is not valid, interrupts */
    if ( ! sl_list_is_valid(lst)) return ;

    /* If list is not empty, runs through all nodes of the list and deletes
     * each one of them */
    if ( ! sl_list_is_empty(lst))

        for (ite = lst->head, ite_aux = lst->head->next;
             ite != NULL;
             ite_aux = ite->next, delete_sl_node(ite), ite = ite_aux)

            ;

    /* Frees list pointer's memory allocation */
    free(lst);

}
