#ifndef EeJ
#define EeJ
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct equipa{
    char* nome;
    int jogosVencidos;
}Equipa;

typedef struct jogo{
    char* nome;
    Equipa* equipa1;
    Equipa* equipa2;
    int score1;
    int score2;
}Jogo;

Equipa* criaEquipa(char* nome);
Jogo* criaJogo(char* nome,Equipa* equipa1,Equipa* equipa2,int score1,int score2);
void addJogosV(Equipa* equipa);
void remJogosV(Equipa* equipa);
void alteraScore(Jogo* jogo,int score1_,int score2_);
void freeEq(Equipa* equipa);
void freeJg(Jogo* jogo);

#endif