#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

#define STRINGSIZE 1024

typedef struct jogo{
    char nome[STRINGSIZE], equipa1[STRINGSIZE], equipa2[STRINGSIZE];
    int score1, score2;
} jogo;

#endif /*JOGO_H_INCLUDED*/