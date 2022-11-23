#ifndef GAME_H
#define GAME_H

#include "team.h"

/*  STRUCTS  */
typedef struct game{
	char* name;
	Team_node* team1, * team2;
	int score[2];
	int winner;		/* team1 wins => winner = 1; team2 wins => winner = 2; draw => winner = 0 */
} Game;

typedef struct game_node{
	Game g;
	struct game_node* next;
} Game_node;

typedef struct game_list{
	struct game_list_node* head;
	struct game_list_node* last;
} Game_list;

typedef struct game_list_node{
	Game_node* g;
	struct game_list_node* next;
} Game_list_node;

/* MAIN FUNCTIONS */
Game_list* __a__(int nl, Game_node** head_game, Team_node** head_team, Game_list* game_list, int* max_victories);
void __l__(int nl, Game_list* game_list);
Game_list* __r__(int nl, Game_node** head_game, Game_list* game_list, Team_list_node* team_list, int* max_victories);
void __s__(int nl, Game_node** head_game, Team_list_node* team_list, int* max_victories);
void __p__(int nl, Game_node** head);

/* AUX FUNCTIONS */
Game_list* insert_game_list(Game_node* g, Game_list* game_list);
Game_list* delete_game_list(char* name, Game_list* game_list, Game_node** games_table);

int search_i_victories(int n_victories, Team_list_node* team_list);

void increase_vic(Team_node* team, int* max_victories);
void decrease_vic(Team_node* team, int* max_victories, Team_list_node* team_list);


#endif
