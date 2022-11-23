#ifndef _HASHGAME_H
#define _HASHGAME_H

#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#define N 2371

typedef struct gamenode *gamelink;

 struct gamenode {
	GAME GAME;
	gamelink next;
};



gamelink push_game(gamelink head, GAME i);			/*Adiciona o jogo i ao inicio da hashtable dos jogos*/
gamelink remove_Game(gamelink head, gameKey k);		/*Remove o jogo com nome k da hashtable dos Jogos*/
GAME search_list_game(gamelink heads, gameKey key);	/*Retorna o jogo com nome key caso presente na hashtable*/
void destroy_list_game(gamelink head);				/*Apaga os jogos presentes numa coluna da Hashtable*/
gamelink* HASHinit_game(int max)					;/*Inicializa a Hashtable dos jogos alocando a memoria necessaria*/
int hash_game(char *v);								/*Funcao Hash presente nos Powerpoints*/
gamelink NEWNode_game(GAME Game, gamelink next);	/*Cria uma nova entrada,alocando a memoria necessaria para a estrutura gamelink*/
void DELETENode_game(gamelink gamenode);			/*Apaga uma entrada da hashtable,libertando a memoria alocada para esta*/
void insert_game(gamelink* heads, GAME Game);		/*Insere um jogo no indice dado pela funcao Hash*/
void delete_game(gamelink* heads, gameKey k);		/*Apaga um jogo com nome k presente na Hashtable*/
GAME search_game(gamelink* heads, gameKey k);		/*Retorna o jogo com nome k presente na hashtable*/
void destroy_hash_game(gamelink* heads);			/*Apaga a Hashtable, libertando toda a memoria que foi alocada para esta*/

#endif