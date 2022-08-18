#ifndef _JOGO_
#define _JOGO_

#include "listaEquipa.h"

/* Estrutura jogo */
typedef struct jogo {
    char* nome;
    char* equipa1;
    char* equipa2;
    int   score1;
    int   score2;
} jogo;

jogo* criaJogo(char* nome, char* equipa1, char* equipa2, int score1, int score2, listaEquipa** headsEquipas, int M_E);
void  freeJogo(jogo* Jogo);
void  printJogo(jogo* Jogo, int* pNL);

#endif
