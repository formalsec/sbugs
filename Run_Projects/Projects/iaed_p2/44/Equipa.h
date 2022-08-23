#ifndef Equipa_H
#define Equipa_H

#include <stdio.h>
#include <stdlib.h>

typedef char* Point;

/*Estrutura que contem um nome de uma equipa e o seu numero de vitorias*/
typedef struct equipa{
    char *nome;
    int wins;

} *equipa;

/*Funcao que recebe um equipa e devolve o seu nome*/
#define point(A) (A->nome)

equipa novaEquipa(char *nom);
void freeEquipa(equipa e);
void printEquipa(equipa e);


#endif