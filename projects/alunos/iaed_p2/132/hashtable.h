#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ****** Structures ****** */

/* Teams' strutctures */
/* str_team struct represents a team in the system */
typedef struct str_team {
    char *name;                     /* name of the team */
    int  wins;                      /* number of wins of the team */
} team;

/* str_node_team struct represents a node of a linked list of teams */
typedef struct str_node_team {
    struct str_node_team *next;     /* pointer to next node of the list */
    team *t;                        /* pointer to a team struct */
} tnode;



/* Games' structures */
/* str_game struct represents a game in the system */
typedef struct str_game {
    char *name;                     /* name of the game */
    char *t1, *t2;                  /* teams' names */
    unsigned int score1, score2;    /* teams' scores */
} game;

/* str_node_game struct represents a node of a linked list of games */
typedef struct str_node_game {
    struct str_node_game *next;     /* pointer to next node of the list */
    game *g;                        /* pointer to a game struct */
} gnode;



/* ****** Functions prototypes ****** */
int hash(char *s, int m);
//char *strdup(char *s);

/* Teams' functions prototypes */
tnode **init_teams(tnode **teams_tab);
void destroy_teams(tnode **teams_tab);

void table_insert_team(tnode **teams_tab, team *t);
team *table_search_team(tnode **teams_tab, char *name);

team *new_team(char *name);
tnode *insert_team_begin(tnode *head, team *t);
team *lookup_team(tnode *head, char *name);

tnode *destroy_tnode(tnode *head);
void free_tnode(tnode *n);


/* List top teams' command specific functions */
int table_search_higher(tnode **teams_tab);
int lookup_higher(tnode *head, int higher);

tnode *table_search_top_teams(tnode **teams_tab, tnode *top_teams, int higher);
tnode *lookup_top_team(tnode *head, tnode *top_teams, int higher);
tnode *insert_team_sorted(tnode *top_teams, team *t);

tnode *destroy_teams_list(tnode *head);


/* Games' functions prototypes */
gnode **init_games(gnode **games_tab);
void destroy_games(gnode **games_tab);

void table_insert_game(gnode **games_tab, game *g);
void table_delete_game(gnode **games_tab, char *name);
game *table_search_game(gnode **games_tab, char *name);

game *new_game(char *name, char *team1, char *team2, int score1, int score2);
gnode *insert_game_begin(gnode *head, game *g);
gnode *delete_game(gnode *head, char *name);
game *lookup_game(gnode *head, char *name);

gnode *destroy_gnode(gnode *head);
void free_gnode(gnode *n); 


/* List with all games' specific functions prototypes */
gnode *del_from_glist(gnode *list, char *name);
gnode *destroy_games_list(gnode *games_list);
