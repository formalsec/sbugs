#ifndef _HASHGAMES_
#define _HASHGAMES_

#include "List.h"

/* Index returned if the wanted item does not exist.*/
#define DOES_NOT_EXIST -1
/* eq(A,B) is True if A and B are 2 equal strings.*/
#define eq(A,B) !strcmp(A,B)

int hash(char * v, int * M);

Node * HashGamesInit(int * m);

void HashGamesInsert(Node * hash_table, Node node, int * m);

int GameSearch(char * name, int * m, Node * hash_table);

Node HashRemoveGame(char * name, int * m, Node * hash_table);

void DestroyHashGames(Node * hash_games);

Node * ExpandGames(Node * hash_game, int * n_games, int * m);

#endif