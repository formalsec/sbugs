#ifndef COMPETITION_H_
#define COMPETITION_H_

#include "game.h"

typedef struct comp_node {
    Game * game;
    struct comp_node * next;
    struct comp_node * previous;
} Comp_node;

typedef struct competition {
    char * name;      
    int    count;
    Comp_node * first;
    Comp_node * last;
} Competition;

Competition * comp_new(char * name);
void          comp_node_free(Comp_node *cn);
void          competition_free (Competition *c);
void          competition_print(Competition *c);

void   comp_add_game   (Competition *c, Game *g);
Game * comp_find_game  (Competition *c, char * game_name);
int    comp_remove_game(Competition *c, char * game_name);
Game * comp_set_score  (Competition *c, char * game_name, int s1, int s2);   

void comp_print_games(Competition *c, int nl);

int comp_get_victories(Competition *c, char * team_name);

#endif

