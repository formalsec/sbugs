#ifndef TEAMS
#define TEAMS


/* Required imports */
#include <stdlib.h>
#include <stdio.h>


/* -------------------------------------------------------------------------- */
/* ------------------------------- STRUCTURES ------------------------------- */
/* -------------------------------------------------------------------------- */


/* Struct that represents a team */
typedef struct my_team {

    /* Pointer to fut_team's name */
    char *name;

    /* Count of won games */
    int victories;

}* fut_team;


/* Represents each layer inside list */
typedef struct sl_node {

    /* Pointer to team */
    fut_team value;

    /* Pointer to next node */
    struct sl_node *next;

}* sl_link;


/* Represents a singly linked list. Used as a master/control structure */
typedef struct singly_linked_list {

    /* Holds number of layers inside list */
    int size;

    /* Pointer to the beginning of the list */
    sl_link head;

}* sl_list;


/* -------------------------------------------------------------------------- */
/* ------------------------------- FUNCTIONS -------------------------------- */
/* -------------------------------------------------------------------------- */


/* Creates a new team */
fut_team creates_team(char* name);


/* Deletes team */
void deletes_team(fut_team team);


/* Returns size of list */
int sl_list_length(sl_list lst);


/* Verifies if list is empty */
int sl_list_is_empty(sl_list lst);


/* Verifies if list is valid */
int sl_list_is_valid(sl_list lst);


/* Gets team inside node */
fut_team get_node_team(sl_link node);


/* Creates a singly linked list */
sl_list create_sl_list();


/* Creates a new node */
sl_link create_team_node(sl_link next, fut_team team);


/* Deletes node of list */
void delete_sl_node(sl_link node);


/* Inserts a team at the beginning of the list */
void insert_team_begin(sl_list lst, fut_team team);


/* Destroys list, clearing all memory */
void sl_list_destroy(sl_list lst);


#endif
