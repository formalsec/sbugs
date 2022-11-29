#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Team.h"

typedef char *gameKey;

typedef struct Game{    /*Estrutura do Jogo*/
    char *Gamename;
    TEAM Team1;
    TEAM Team2;
    int scoreHome; 
    int scoreAway;
} *GAME;

#define keygame(A) (A->Gamename) 
#define eqgame(A, B) (strcmp(A,B)==0)

GAME newGame(char *name,TEAM team1,TEAM team2,int home,int away); /*Funcao que aloca memoria para um Jogo */
void deleteGame(GAME i); /*Funcao que apaga um jogo do sistema, libertando a memoria que foi alocada*/
void seeGame(GAME i);    /*Funcao que da print ao jogo*/
TEAM winner(GAME i);     /*Funcao que retorna a equipa vencedora de dois jogos*/

#endif