#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "game.h"

int hash(char* name, int M);

Game_node** init_table_game();
Team_node** init_table_team();

Game_node* new_game_node(Game p_game);
Team_node* new_team_node(Team p_team);

Game_node* insert_game_table(Game g, Game_node** head);
Team_node* insert_team_table(Team t, Team_node** head);

Game_node* search_game(char* name, Game_node** head);
Team_node* search_team(char* name, Team_node** head);

void delete_game_table(char* name, Game_node** head);
void delete_team_table(char* name, Team_node** head);

#endif
