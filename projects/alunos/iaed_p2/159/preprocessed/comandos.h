#ifndef COMANDOS
#define COMANDOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "tabelas_disp.h"

/*FUNCOES PRINCIPAIS*/
void comando_a(ST_jg Tj,ST_eq Te,Jogo* Jogos, int num_linhas);
void comando_A(ST_eq Te,int num_linhas);
void comando_l(ST_jg Tj,Jogo* Jogos, int num_linhas);
void comando_p(ST_jg Tj,int num_linhas);
void comando_P(ST_eq Te,int num_linhas);
void comando_s(ST_jg Tj,ST_eq Te, int num_linhas);
void comando_r(ST_jg Tj,ST_eq Te,Jogo* Jogos,int  num_linhas);
void comando_g(ST_eq Te,int num_linhas);


/*FUNCOES AUXILIARES*/
void adiciona_scores(Equipa e1, Equipa e2, unsigned int s1, unsigned int s2);
void altera_scores(ST_eq Te,Jogo jogo, unsigned int s1, unsigned int s2);
void elimina_scores(ST_eq Te,Jogo jogo);
int comparador(const void *a, const void * b);
#endif