#ifndef STRUCTURES_H
#define STRUCTURES_H

/* Struct that holds the team's name and the amount of won games */
typedef struct team 
{
    char *name;
    int victories;
} team;

/* Structure that contains information regarding a game and the pointers that localize it */
typedef struct game
{
    char *name, *team1, *team2;
    int score1, score2;
    struct game *next;
    struct game *previous;

} game;

/* Struct for the game hashtable */
typedef struct game_node 
{
    game *g;
    struct game_node *next;

} glink;

/* Struct for the team hashtable */
typedef struct team_node
{
    team *t;
    struct team_node *next;

} tlink;

/* Functions: */
/* Team Related Functions: */

int new_team(tlink** team_table, char* name);
team* team_table_search(tlink** team_table, char* name);
void give_victory(tlink** team_table, char* name);
void remove_victory(tlink** team_table, char* name);
int compare_func(const void *t1, const void *t2);
void destroy_ttable(tlink** team_table);


/* Game Related Functions: */

void new_game(glink** game_table, tlink** team_table, game** first_game, game** last_game, char* name, char* t1, char* t2, int scr1, int scr2);
game* game_table_search(glink** game_table, char* name);
void delete_game(game** first_game, game** last_game, glink** game_table, tlink** team_table, char* name);
void destroy_game(game* match);
void destroy_gtable(glink** game_table);

#endif