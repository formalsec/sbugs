#ifndef HASTABLE_H
#define HASTABLE_H

#ifndef H_SIZE_GAME
/* Initial size of the hash table */
#define H_SIZE_GAME 1997
#endif

#ifndef H_SIZE_TEAM
/* Initial size of the hash table */
#define H_SIZE_TEAM 997
#endif

#include <string.h>

#include "game.h"
#include "team.h"

/* Prototypes - Hashing */

/* Supposed position of an item in the hash table */
int hash(char *v, int M);


/* ------ Hash table for games ------ */

/* Structure for a hash table for games */
struct ht_games{
    /* Number of games in the hash table */
    int num;
    /* Size of the hash table */
    int size;
    Game *games;
};

/* Pointer to a hash table */
typedef struct ht_games* Ht_games;

/* Prototypes */

/* Initializes a hash table for games */
Ht_games HTGinit(int max);
/* Inserts a game in a hash table */
Ht_games HTinsertGame(Ht_games ht, Game game);
/* Inserts a team in a hash table */
Game HTsearchGame(Ht_games ht, char *name);
/* Deletes a game from the hash table */
void HTdeleteGame(Ht_games ht, char *name);
/* Expands the size of the hash table for the games */
Ht_games HTexpandGames(Ht_games ht);
/* Frees the memory associated with a hash table for games */
void freeHTGames(Ht_games ht);


/* ------ Hash table for teams ------ */

/* Structure for a hash table for teams */
struct ht_teams{
    /* Number of teams in the hash table */
    int num;
    /* Size of the hash table */
    int size;
    Team *teams;
};


/* Pointer to a hash table */
typedef struct ht_teams* Ht_teams;

/* Prototypes */

/* Initializes a hash table for teams */
Ht_teams HTTinit(int max);
/* Inserts a team in a hash table */
Ht_teams HTinsertTeam(Ht_teams ht, Team team);
/* Gets the team for the key given */
Team HTsearchTeam(Ht_teams ht, char *name);
/* Expands the size of the hash table for the teams */
Ht_teams HTexpandTeams(Ht_teams ht);
/* Frees the memory associated with a hash table for teams */
void freeHTTeams(Ht_teams ht);

#endif
