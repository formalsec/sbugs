#ifndef _JOGOS_
#define _JOGOS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"

/*Struct game which contains all the information
  surrounding a game, namely its name, the name of
  teams competing and the scoreboard*/
typedef struct game{
    char *name,*team1,*team2;
    int score1;
    int score2;
}Game;

/*Struct gameNode which contains a game and it is used for
  singly linked lists of games*/
typedef struct gameNode{
    Game *game;
    struct gameNode *next;
}NodeGame;


/*------------------------FUNCTIONS PROTOTYPES-------------------------------*/

void init_hash_games(NodeGame **heads,int mod);


Game * create_game(char *name,char *nameT1,char *nameT2,int goals1,int goals2);

void hash_insert_game(NodeGame **heads,Game *game,int mod);
NodeGame * hash_put_begin_games(NodeGame *head,Game *j);

Game * hash_search_game(NodeGame **heads,char *nameGame,int mod);
Game * search_game(NodeGame *head,char *name);

void hash_change_score(NodeGame **heads,char *nameGame, int goals1, int goals2,
                       int mod);

void hash_remove_game(NodeGame **heads,char *name,int mod);
NodeGame * remove_el_hash(NodeGame *head, char *gameName);
NodeGame * remove_el_list(NodeGame *head, char *gameName);

void free_game(Game *game);

void destroy_hash_games(NodeGame **heads, int mod);
void destroy_list_games(NodeGame *head);
void destroy_refs_list(NodeGame *head);

#endif