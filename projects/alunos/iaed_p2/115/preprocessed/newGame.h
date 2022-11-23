#ifndef _JOGOS_
#define _JOGOS_

#include "newTeam.h"

/* Struct jogo caracterizado por um nome, 2 equipas (Ponteiros para structs equipa) e 2 scores (inteiros) */
typedef struct game {
    char * name;
    Team * team1;
    Team * team2;
    int score1;
    int score2;
} Game;

/* Struct no para jogo caracterizado por um ponteiro para jogo, um ponteiro para o elemento
seguinte na Hash Table (*nextH), para o elemento seguinte na lista (*nextL) e para o elemento
anterior (apenas utilizado na lista) */
typedef struct gameNode {
    Game * game;
    struct gameNode *nextH, *nextL, *previous, *prevH;
} GameNode;

/* Ponteiro para um no de um jogo */
typedef struct gameNode* gameNodeP;

/* Struct para uma Hash Table de equipas caracterizado pela propria tabela, o tamanho da tabela
e o numero de elementos que nela estao guardados
(Inicializado em "hastables.c" mas definido aqui por ser necessario para funcoes deste ficheiro)*/
typedef struct hashtableT {
    teamNodeP *headsT;
    int size;
    int n_elements;
} TeamsHash;

/* Struct para uma Hash Table de jogos caracterizado pela propria tabela, o tamanho da tabela
e o numero de elementos que nela estao guardados 
(Inicializado em "hastables.c" mas definido aqui por ser necessario para funcoes deste ficheiro)*/
typedef struct hashtableG {
    gameNodeP *headsG;
    int size;
    int n_elements;
} GamesHash;

/*--------------------------------------------------------------------------------------------
HASH FUNCTION -> Soma os caracteres e devolve o resto da divisao por M
---------------------------------------------------------------------------------------------*/
int hashU(char *v, int M);

/*-------------------------------------------------------------------------------------------
Funcao que cria um novo jogo e procura as equipas na Hash Table de equipas para as
adicionar como propriedades de um jogo
---------------------------------------------------------------------------------------------*/
gameNodeP newGame(TeamsHash *HashT, char* name, char* eq1, char*eq2, int score1, int score2);

/*-------------------------------------------------------------------------------------------
Funcao que cria um novo ponteiro para um jogo e inicializa as variaveis
---------------------------------------------------------------------------------------------*/
gameNodeP newGameNode(Game* game);

/*-------------------------------------------------------------------------------------------
Funcao que remove vitorias as equipas participantes num jogo quando um jogo e apagado
---------------------------------------------------------------------------------------------*/
void removeWin(Game* game);

#endif