#ifndef GAMES
#define GAMES


/* Required imports */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* -------------------------------------------------------------------------- */
/* ------------------------------ STRUCTURES -------------------------------- */
/* -------------------------------------------------------------------------- */


/* Struct that represents a match */
typedef struct my_game {

    /* Pointer to match's name */
    char *name;

    /* Pointer to team 1's name */
    char *team1;

    /* Pointer to team 2's name */
    char *team2;

    /* Team 1's score */
    int score1;

    /* Team 2's score */
    int score2;

}* match;


/* Represents each layer inside list */
typedef struct dl_node {

    /* Holds match inside this node */
    match value;

    /* Pointer to next node */
    struct dl_node *next;

    /* Pointer to previous node */
    struct dl_node *previous;

} * dl_link ;


/* Represents a doubly linked list. Used as a master/control structure */
typedef struct doubly_linked_list {

    /* Number of layers inside list */
    int size;

    /* Pointer to node at the top */
    dl_link head;

    /* Pointer to node at the bottom */
    dl_link tail;

} * dl_list ;


/* -------------------------------------------------------------------------- */
/* -------------------------------- FUNCTIONS ------------------------------- */
/* -------------------------------------------------------------------------- */


/* Creates a match and returns it */
match creates_match(char* name, char* team1, char* team2,
                    int score1, int score2);


/* Deletes match */
void deletes_match(match game);


/* Creates a doubly linked list */
dl_list create_dl_list();


/* Creates a new node at requested position of the list */
dl_link create_dl_node(dl_link next, dl_link previous, match game);


/* Deletes a node */
void deletes_dl_node(dl_link node);


/* Returns size of list */
int dl_list_length(dl_list lst);


/* Verifies if list is empty */
int dl_list_is_empty(dl_list lst);


/* Verifies if list is valid */
int dl_list_is_valid(dl_list lst);


/* Gets match inside node */
match get_node_match(dl_link node);


/* Puts game at the start of the list */
void insert_begin(dl_list lst, match game);


/* Removes first node from list. If is empty, interrupts */
void remove_begin(dl_list lst);


/* Removes element at the end of the list */
void remove_end(dl_list lst);


/* Removes node from list */
void remove_node(dl_list lst, dl_link del_node);


/* Destroys list, clearing all memory */
void dl_list_destroy(dl_list lst);


#endif
