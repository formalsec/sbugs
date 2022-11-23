#ifndef LISTAS_H
#define LISTAS_H

#include <stdlib.h>

#define MAXSIZE 1024    /* Tamanho maximo dos nomes das equipas e dos jogos. */
#define MAXMELHORES 20  /* Tamanho do array de nomes das melhores equipas. */

/*================================================================================================*/

typedef struct TeamNODE *tlink;

/* Estrutura para equipa. */
typedef struct Team {
    char *name;
    int vitorias;
} *pTeam;

/* Estrutura para node de equipa. */
struct TeamNODE {
    pTeam pEquipa;
    tlink next;
};

tlink NEWTeam(pTeam pEquipa, tlink next);
void put_team(pTeam Equipa, tlink* pLThead, tlink* pLTtail);
void limpaFilaEquipa(tlink* pLThead, tlink* pLTtail);

/*================================================================================================*/

typedef struct GameNODE *glink;

/* Estrutura para jogo. */
typedef struct Game {
    char *name;
    pTeam pEquipa1;
    pTeam pEquipa2;
    int score1;
    int score2;
} *pGame;

/* Estrutura para node de jogo. */
struct GameNODE {
    pGame pJogo;
    glink next;
    glink prev;
};

glink NEWGame(pGame pJogo, glink next, glink prev);
void put_game(pGame Jogo, glink* pLGhead, glink* pLGtail);
void limpaFilaJogo(glink* pLGhead, glink* pLGtail);

#endif
