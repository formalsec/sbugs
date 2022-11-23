#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 1024



/*============================================================================*/
/*                              DATA STORAGE                                  */
/*============================================================================*/

/* team features */
typedef struct team{
    char *name;
    int wins;
}team;

/* game features */
typedef struct game{
    char *name;
    team *team1;
    team *team2;
    int score1;
    int score2;
    int id;
}game;

/* games hashtable */
typedef struct gametable{
    game **table;
    int size;
    int n_el;
    int last_idg;
}gametable;

/* teams hastable */
typedef struct teamstable{
    team **table;
    int size;
    int n_el;
}teamstable;


/*============================================================================*/
/*                          HASHTABLE FUNCTIONS                               */
/*============================================================================*/

/* Initialize the hastable for games */
gametable InitGameTable(int size);
/* Doubles the size of the game hashtable */
gametable* ExpandGameTable(gametable *table_g);
/* Inserts game in game hashtable */
void InsertGame(game *game_v, gametable *table_g);
/* Searches game in game hashtable by game name
returns NULL if element is not there*/
game* SearchGame(char *name, gametable* table_g);
/* Removes game from game hashtable */
void DeleteGame(game *game_v, gametable *table_g);

/* Hash function returns element's index in hashtable works for both hashtables */
int Dash(char *name, int size);

/* Intialize the hastable for teams */
teamstable InitTeamTable(int size);
/* Doubles the size of the teams hashtable */
teamstable* ExpandTeamsTable(teamstable *table_t);
/* Inserts team in team hashtable */
void InsertTeam(team *team_p, teamstable *table_t);
/* Searches team in team table by team name
returns NULL if the element is not there */
team* SearchTeam(char *name, teamstable* table_t);
