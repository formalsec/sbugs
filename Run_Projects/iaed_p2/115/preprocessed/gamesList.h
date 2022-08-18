#ifndef _LISTAEQUIPAS_
#define _LISTAEQUIPAS_

#include "newGame.h"
#include "hashTables.h"

/*-------------------------------------------------------------------------------------
Funcao que aloca memoria para uma lista ponteiros para jogos e inicializa variaveis
---------------------------------------------------------------------------------------*/
gameListP initGamesList();

/*-------------------------------------------------------------------------------------
Funcao que adiciona um ponteiro para um jogo no inicio da lista
---------------------------------------------------------------------------------------*/
void addGameList(gameListP gameList, gameNodeP game);

/*-------------------------------------------------------------------------------------
Funcao que percorre a lista da direita para a esquerda e imprime as propriedades de um jogo
---------------------------------------------------------------------------------------*/
void listGames(gameListP gameList, int cont);

#endif
