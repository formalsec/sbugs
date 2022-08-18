#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "TEAM.h"
#define M_G 100000

/*Estrutura usada para guardar as equipas ordenadas pelo numero de vitorias*/
typedef struct names{
  char* name;
  struct names* next;
} *GamesList;

/*Estrutura que define um jogo. Nome do jogo, nome das equipas, e o resultado*/
typedef struct game{
  char* name;
  char* team1;
  char* team2;
  int score1;
  int score2;
} *Game;

/*Lista ligada que contem os jogos*/
typedef struct GameNode{
  Game game;
  struct GameNode *next;
} *gamelink;


gamelink *g_heads;

/*Lista ligada auxiliar para guardar a ordem pela qual foram inseridos*/
GamesList list_head, tail;


void NewGame(int line); /*funcao a */
void SearchGame(int line); /*funcao p */
void DeleteGame(int line);  /*funcao r */
void ListAllGames(int line);  /*funcao l */
void Change_Score(int line);  /* funcao s */



/*:::::::::::::::::::::AUXILIARES:::::::::::::::::::::*/

int hash_game(char* name);
void GameInit();
gamelink insertHashGame(char* name, char* name1, char* name2, int score1, int score2, gamelink head);
gamelink searchHashGame(char* name, gamelink head);
gamelink deleteHashGame(char* name, gamelink head);
void freeGameHash();
void free_gamelist(gamelink head);

gamelink newGameLink(char* name, char* name1, char* name2, int score1, int score2);



void insertListGames(char* name);
void delete_gamelist(char* name);
GamesList new_game_node(char* name);











#endif
