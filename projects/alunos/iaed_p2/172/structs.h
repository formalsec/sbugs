#ifndef _STRUCTS_
#define _STRUCTS_
#define MAX_Char 1024 /* Max name size */

/* Struct 'game' */
typedef struct game {
    char *name, *t1, *t2;
    int s1, s2;
} *Game;

/* Struct 'node', a double linked list which contains a Game */
typedef struct node {
    Game g;
    struct node *next, *prev;
} *link;

/* Struct 'team', with a linked list included */
typedef struct team {
    char *name;
    int wins;
    struct team *next;
} *Team;


/* This function allocates memory for the strings in Games and Teams */
char* ReadString(char *v);


/*########################*/
/* Game related functions */
/*########################*/


/* Allocates memory for a Game and adds the info to the struct */
Game NewGame(link *head, link *tail, char *name, char *t1, char *t2);


/* Adds a game to the double linked list */
void InsertGame(link *head, link *tail, Game g);


/* Removes a node from the list */
void RemoveGame(link *head, link *tail, char *name);


/* Prints the Games from the list */
void PrintGame(link *node, int NL);


/* Frees the memory allocated for a Game */
void FreeGame(Game g);


/*###########################################################*/
/*###########################################################*/


/*########################*/
/* Team related functions */
/*########################*/


/* Allocates memory for a Team, and adds it to the system */
Team NewTeam(char *name, Team *head);


/* Returns the max amount of victories */
int* MaxWins(Team *head, int *lst);


/* Frees the memory allocated for a Team */
void FreeTeam(Team t);

#endif
