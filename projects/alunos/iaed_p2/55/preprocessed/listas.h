#ifndef _LISTAS_
#define _LISTAS_

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "estruturas.h"


/* Cria nova lista de equipa vazia. */
lista_equipa* cria_lista_equipa();                

/* Cria nova lista vazia. */
lista* cria_lista();                

/* Cria nova lista ponteiros vazia. */
lista_ponteiro* cria_lista_ponteiros();



/* Verifica se a lista equipa eh vazia. */
int eh_vazia_equipa(const lista_equipa* l);

/* Verifica se a lista eh vazia. */
int eh_vazia(const lista* l);

/* Verifica se a lista ponteiros eh vazia. */
int eh_vazia_ponteiros(const lista_ponteiro* l);



/* Adiciona um no_equipa (struct estr_equipa) como o ultimo elemento da lista. */
void adiciona_equipa_fim(lista_equipa* l, elo_equipa novo_no);

/* Adiciona uma equipa (struct estr_equipa) como o ultimo elemento da lista. */
void adiciona_fim(lista* l, elo_jogo novo_no);

/* Adiciona no ponteiro (struct estr_ptr) como o ultimo elemento da lista. */
void adiciona_fim_ponteiro(lista_ponteiro* l, elo_ponteiro novo_no);

/* Adiciona um no_jogo (struct estr_jogo) como o primeiro elemento da lista. */
void adiciona_inicio(lista* l, elo_jogo novo_no);



/* Remove um no_equipa (struct estr_equipa). */
void remove_no_equipa(lista_equipa* l, elo_equipa no);

/* Remove um no_jogo (struct estr_jogo). */
void remove_no_jogo(lista* l, elo_jogo no);

/* Remove um no_ponteiro (struct estr_ptr). */
void remove_no_ponteiro(lista_ponteiro* l, elo_ponteiro no);



/* Retorna o valor de max_vitorias */
int Retorna_max_vitorias(const lista_equipa* le);

/* Retorna quantidade de equipas com max_vitorias */
int Retorna_contador_max_vitorias(const lista_equipa* le, int max_vitorias);



/* Procura um no_equipa (struct estr_equipa). */
elo_equipa procura_no_equipa(const lista_equipa* l, char* equipa);

/* Procura um no_jogo (struct estr_jogo). */
elo_jogo procura_no_jogo(const lista* l, char* jogo);



/* Altera o numero de vitorias das Equipas. Jogo com empates. */
void altera_vitorias_empate(int s1, int s2, int s1v, int s2v, \
                            elo_equipa no1, elo_equipa n2);

/* Altera o numero de vitorias das Equipas. Jogo como vitorias Equipa1. */
void altera_vitorias_equipa1(int s1, int s2, int s1v, int s2v, \
                                elo_equipa no1, elo_equipa n2);

/* Altera o numero de vitorias das Equipas. Jogo como vitorias Equipa2. */
void altera_vitorias_equipa2(int s1, int s2, int s1v, int s2v, \
                                elo_equipa no1, elo_equipa n2);

/* Altera score de um no_jogo (struct estr_jogo). */
void altera_score(int score1, int score2, elo_jogo no);



/* Liberta toda a memoria associada a lista de equipas. */
void liberta_lista_equipa(lista_equipa* l);

/* Liberta toda a memoria associada a lista de jogos. */
void liberta_lista_jogo(lista* l);

/* Liberta toda a memoria associada a lista de jogos. */
void liberta_lista_ponteiro(lista_ponteiro* l);


#endif