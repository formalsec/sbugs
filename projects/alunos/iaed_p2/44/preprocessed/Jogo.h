#ifndef Jogo_H
#define Jogo_H

#include <stdio.h>
#include <stdlib.h>
#include "Equipa.h"

typedef char* Key;

/*Estrutura que contem o nome de um jogo, 2 apontadores para as equipas 
    participantes e o resultado do jogo, divido em 2 variaveis*/
typedef struct jogo{
    char *nome;
    equipa equipa1;
    equipa equipa2;
    int score1;
    int score2;

} *jogo;

/*Funcao que recebe um jogo e devolve o nome do mesmo*/
#define key(A) (A->nome)

jogo novoJogo(char *nom,equipa eq1, equipa eq2, int res1, int res2);
void freeJogo(jogo j);
void printJogo(jogo j);


#endif