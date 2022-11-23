#ifndef GSTRUCT_H
#define GSTRUCT_H

/*#define GAMES_LIM 11*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"
#include "hash.h"

typedef struct g_node
{
    game game;
    struct g_node * previous;
    struct g_node * next;
    struct g_node * in_previous;
    struct g_node * in_next;
}* game_node;

typedef struct g_item
{
    game_node head;
}* game_item;

void init_games(game_item **);
void free_games(game_item *);
void insert_game(game_item *, game, game_node *, game_node *);
game_node search_game(game_item *, char *);
void update_score(game_node, int, int);
void delete_ordered(game_node *, game_node);
void delete_game(game_item, game_node);
void print_game(game_node, int);
void insertion_order(game_node, int);

#endif