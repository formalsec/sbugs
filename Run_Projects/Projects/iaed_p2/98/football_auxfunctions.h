#include "football_defs.h"

/* Calculates the index in the hashtable with size M
   in where to put/find the name given.              */
int hash(char* v, int M);

/* Creates a pointer to a string. */
//char* strdup(char str[]);

/* Creates a Game with the information given. */
Game createGame(char name[], char team1[], char team2[],
int score1, int score2);

/* Inserts a Game in the list of Games. */
void insertGameList(Game item, List_Limits headAndTail);

/* Inserts a Game in the hash. */
void insertGameTable(Game item, Game_Link* heads);

/* Finds the Game with the name given and returns it (if it exists). */
Game searchGame(char name[], Game_Link* heads);

/* Frees all the information of a Game. */
void freeGameAux(Game x);

/* Finds and removes the Game item given. */
void freeGame(Game item, int i, Game_Link* headsG, List_Limits headAndTail);

/* Creates a Team with the name given. */
Team createTeam(char name[]);

/* Inserts a Team given in the database. */
void insertTeam(Team item, Team_Link* heads);

/* Finds the Team with the name given. */
Team searchTeam(char name[], Team_Link* heads);
