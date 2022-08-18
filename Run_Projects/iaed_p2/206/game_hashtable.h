#ifndef _GAME_HASHTABLE_H_
#define _GAME_HASHTABLE_H_ 

#include "game.h"

typedef struct game_hashtable {
	int size;
	int count;
	Game *game_table;
} Game_Hashtable;


/*
Inicializa cada uma das posicoes da hashtable relativa a 'game'.
Retorno: vazio.
*/
void init_game_hashtable_table(Game_Hashtable *GH);


/*
Inicializa a hashtable com o tamanho atual.
Retorno: ponteiro para hashtable relativa a 'game'.
*/
Game_Hashtable *init_game_hashtable(int game_hashtable_size);


/*
Insere a referencia para o jogo na hashtable, dado o nome como argumento.
Retorno: vazio.
*/
void insert_game_hashtable(Game_Hashtable *GH, Game game);


/*
Expande o tamanho da hashtable relativa a 'game'.
Retorno: vazio.
*/
void expand_game_hashtable(Game_Hashtable *GH);


/*
Procura a referencia do jogo, dado o nome como argumento.
Retorno: ponteiro para o jogo.
*/
Game search_game_hashtable(Game_Hashtable *GH, char *name);


/*
Remove a referencia do jogo dado o nome como argumento.
Retorno: vazio.
*/
void remove_game_hashtable(Game_Hashtable *GH, char *name);


/*
Liberta na hashtable relativa a 'game', o espaco alocado pela posicao dada como argumento.
Retorno: vazio.
*/
void free_game_hashtable_table(Game_Hashtable *GH, int index);


/*
Liberta o espaco alocado pela hashtable relativa a 'game'.
Retorno: vazio.
*/
void free_games_hashtable(Game_Hashtable *GH);

#endif