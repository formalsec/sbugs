#ifndef BTGAME_H
#define BTGAME_H

#include "game.h"
#include <stdlib.h>

/* Estrutura que representa um node de uma arvore binaria de jogos. */
typedef struct BTGame {
    Game *game;                  /* O jogo. */
    struct BTGame *left, *right; /* Ramos esquerdo e direito da arvore. */
    int height;                  /* Altura relativa para efeitos de optimizacao. */
} BTGame;

/* Construtores e libertadores */
BTGame *newBTGame();
void freeBTGame(BTGame *);

/* Outra funcoes */
int countBTGame(BTGame *);
Game *searchBTGame(BTGame *, char *);
int existsBTGame(BTGame *, char *);
void insertBTGame(BTGame **, Game *);
void deleteBTGame(BTGame **, char *);
void dumpBTGame(Game *[], BTGame *);

#endif