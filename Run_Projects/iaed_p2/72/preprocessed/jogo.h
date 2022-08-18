#ifndef JOGO_H_INCLUDE
#define JOGO_H_INCLUDE

/*INCLUDES*/
#include <stdlib.h>
#include <strings.h>
#include "equipa.h"
#include "estruturas_equipa.h"
#include "auxiliares.h"

/*MACROS*/
#define nome_jogo(a) (a->nome)
#define obtem_equipa1(a) (a->equipa1)
#define obtem_equipa2(a) (a->equipa2)
#define obtem_score1(a) (a->score1)
#define obtem_score2(a) (a->score2)

/*
  Jogo: char*, Equipa, Equipa, int, int
  Ponteiro para um jogo que consiste numa string nome
  duas Equipas e dois inteiros que representam a pontuacao 
  de cada equipa
*/
typedef struct jogo {
    char* nome;
    Equipa equipa1;
    Equipa equipa2;
    int score1;
    int score2;
} *Jogo;

/*PROTOTIPOS*/

Jogo cria_jogo(char* nome, int size_nome, Equipa equipa1, Equipa equipa2, int score1, int score2);
void free_jogo(Jogo jg);
void remove_jogo(Jogo jg);
void altera_score(Jogo jg, int score1, int score2);

#endif
