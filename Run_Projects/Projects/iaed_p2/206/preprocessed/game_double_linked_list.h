#ifndef _GAME_DOUBLE_LINKED_LIST_H_
#define _GAME_DOUBLE_LINKED_LIST_H_

#include "game.h"

typedef struct game_node {
	Game game;
	struct game_node *next, *previous;
} Game_Node;

typedef struct {
	Game_Node *head, *last;
} Game_List;


/*
Inicializa a lista duplamente ligada relativa a 'game'.
Retorno: ponteiro para a lista relativa a 'game'.
*/
Game_List *init_game_list();


/*
Adiciona a referencia para um jogo, dado o nome como argumento, na ultima posicao da lista.
Retorno: vazio.
*/
void add_last_game_list(Game_List *GL, Game game);


/*
Remove a referencia para um jogo dado o nome como argumento.
Retorno: vazio.
*/
void remove_game_list(Game_List *GL, char *name);


/*
Liberta o espaco da memoria ocupada pelo no 'game'.
Retorno: vazio.
*/
void free_game_node(Game_Node *game_node);


/*
Liberta o espaco da memoria ocupado pelo lista duplamente ligada relativa a 'game'.
Retorno: vazio.
*/
void free_games_list(Game_List *GL);

#endif