#ifndef _OBJECTS_H
#define _OBJECTS_H

/**
 * File:  Objects.c
 * Contem as definicoes de equipa e de jogo
**/

typedef struct Equipa
{
    char *nome;
    int jogos_ganhos;
} Equipa;

typedef struct Jogo
{
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
} Jogo;

typedef enum Type
{
    EQUIPA,
    JOGO
} Type;

#endif
