#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <string.h>

#include "game.h"
#include "team.h"

/* ------ Linked list for games ------- */

/* Node structure to hold a pointer */
struct node_game{
    struct node_game *next;
    Game ptr;
};

/* Definition for a node pointer */
typedef struct node_game* nodeGame;

/* Prototypes */

/* Only remove an element of the list returning the head */
nodeGame popGame(nodeGame head, char *game_name);
/* Add integer e as the first element of the list and returns the new head */
nodeGame pushGame(nodeGame head, Game pgame);
/* Frees all memory associated with the list and returns NULL */
nodeGame destroyLinkedGames(nodeGame head);


/* ------ Linked list for teams ------ */

/* Node structure to hold a pointer */
struct node_team{
    struct node_team *next;
    Team ptr;
};

/* Definition for a node pointer */
typedef struct node_team* nodeTeam;

/* Prototypes - Linked list for teams */

/* Add integer e as the first element of the list and returns the new head */
nodeTeam pushTeam(nodeTeam head, Team pteam);
/* Frees all memory associated with the list and returns NULL */
nodeTeam destroyLinkedTeams(nodeTeam head);

#endif
