#ifndef _ESTRUTURAS_
#define _ESTRUTURAS_

#include <stdlib.h>

typedef struct jogo
{
    /* Nome do jogo */
    char *nome; 
    /* Nomes das equipas */
    char *equipa1; 
    char *equipa2;
    /* Pontos de cada equipa */
    int pontos1; 
    int pontos2;
    /* Jogo introduzidos depois e antes, respetivamente */
    struct jogo *prox; 
    struct jogo *ant; 
} *p_jogo;

typedef struct equipa
{
    /* Nome da equipa */
    char *nome;
    /* Numero de vitorias */
    int vitorias;
    /* Equipa introduzida depois */
    struct equipa *prox;
} *p_equipa;

/* Funcao que da free aos conteudos de jogo e ao proprio jogo */
void free_jogo(p_jogo jogo);

/* Funcao que da free aos conteudos de equipa e a propria equipa */
void free_equipa(p_equipa equipa);


#endif