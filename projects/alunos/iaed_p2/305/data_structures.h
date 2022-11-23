#include "libr_const.h"

#ifndef D_S_H
#define D_S_H
/*-------------------------------------------------------------------------------------------------
	Structures
-------------------------------------------------------------------------------------------------*/

/* Structure of a game */
typedef struct st_game {
	char *n;		/* game name */
	char *t1;		/* team one name */
	char *t2;		/* team two name */
	int   s1;		/* team one score */
	int   s2;		/* team two score */
} Game;

/* Structure of a team */
typedef struct st_team {
	char *n;		/* team name */
	int   w;		/* number of games won */
} Team;

/* Structure of a node of a double linked list */
typedef struct st_node {
	char *text;
	struct st_node *prev, *next;
} node;

/*-------------------------------------------------------------------------------------------------
	List functions
-------------------------------------------------------------------------------------------------*/

/* Creates a new node */
node * NEW(char *text);

/* Inserts a new node at the end of the list */
node ** insert_END(node **ends, char *text);

/* Deletes a node of a list */
node ** lst_delete(node **ends, char *text);

/* Frees a list */
void free_list(node **ends);

/*-------------------------------------------------------------------------------------------------
	Hash tables functions
-------------------------------------------------------------------------------------------------*/

/* Taken from slides */
int hash(char *name, int sz);

/* Initializes G and returns it's pointer */
Game ** HT_G_init(Game **G, int *G_sz);

/* Initializes T and returns it's pointer */
Team ** HT_T_init(Team **T, int *T_sz);

/* Frees G */
void HT_G_free(Game **G, int *G_sz);

/* Frees T */
void HT_T_free(Team **T, int *T_sz);

/* Expands G and returns the pointer to the updated hash table */
Game ** HT_G_expand(Game **G, int *G_sz);

/* Expands T and returns the pointer to the updated hash table */
Team ** HT_T_expand(Team **T, int *T_sz, int *T_n);

/* Inserts a game in G */
void HT_G_insert(Game *g, Game **G, int *G_sz);

/* Inserts a team in T */
Team ** HT_T_insert(Team *t, Team **T, int *T_sz, int *T_n);

/* Searches for a game in G given its name and returns it's pointer */
Game * HT_G_search(char *name, Game **G, int *G_sz);

/* Searches for a team in T given its name and returns it's pointer */
Team * HT_T_search(char *name, Team **T, int *T_sz);

/* Deletes a game in G given it's name */
void HT_G_delete(char *name, Game **G, int *G_sz);
#endif