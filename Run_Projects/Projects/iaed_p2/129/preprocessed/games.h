#ifndef games_h
#define games_h

#include "teams.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GAME_TABLE_SLOTS 1009
#define MAX_GAME_NAME_LEN 1023

typedef struct game{
    char *name;
    struct team *team_1;
    struct team *team_2;
    int score_team_1;
    int score_team_2;

}game;

typedef struct game_node{
    struct game *game;
    /*Cronological ordererd list*/
    struct game_node *previous_game;
    struct game_node *next_game;
    /*hash table line*/
    struct game_node *next_node;
    struct game_node *previous_node;

}game_node;


typedef struct game_table{
    struct game_node *first_game;
    struct game_node *latest_game;
    struct game_node *table[GAME_TABLE_SLOTS];

}game_table;


game_table * init_games();

int hash_game(char *name);

void push_game(game_table *games, game *new_game);

int same_game(game *game_1, game *game_2);

game_node * get_node(game_table *games, game *game);

void delete_game(game_table *games, game *game);

void new_game(game_table *games, char *name, team *team_1, team *team_2, 
int score_1, int score_2);

game * get_game(game_table *games, char *name);

void update_score(game *game, int score_1, int score_2);

game * first_game(game_table *game_table);

game * next_game(game_table *games, game *game);

team * game_winner(game * game);

void print_game(game *game);

void free_game(game *game);

void free_games(game_table *games);

#endif 