#ifndef _JOGO_
#define _JOGO_

#include "equipa.h"

typedef struct jogo{
    char *nome;
    Equipa *e1,*e2;
    int s1,s2;
    int id;
}Jogo;

/* Aloca memoria para um jogo e inicializa */
Jogo* cria_jogo(char*, Equipa*, Equipa*, int, int,int);

/* Liberta a memoria alocada para um jogo */
void free_jogo(Jogo*);

/* Altera o score de um jogo */
void alt_score_jogo(Jogo*,int,int);

/* Retorna o id de um jogo */
int get_id_jogo(Jogo *);

/* Retorna o nome de um jogo */
char* get_nome_jogo(Jogo*);

/* Retorna a primeira equipa de um jogo */
Equipa* get_equipa1_jogo(Jogo*);

/* Retorna a segunda equipa de um jogo */
Equipa* get_equipa2_jogo(Jogo*);

/* Retorna o score da primeira equipa de um jogo */
int get_score1_jogo(Jogo*);

/* Retorna o score da segunda equipa de um jogo */
int get_score2_jogo(Jogo*);
#endif