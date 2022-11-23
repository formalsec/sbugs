#ifndef JOGOS_H
#define JOGOS_H

#include "equipas.h"

/* Estrutura para guardar cada jogo adicionado ao sistema.
 * Contem o seu nome, ponteiros para ambas as equipas
 * participantes, os seus respetivos "scores" e dois ponteiros
 * para o jogo seguinte na hashtable e na lista ligada. */
typedef struct node_jogo {
    char *nome_jogo;
    link_equipa equipa1, equipa2;
    int score1, score2;
    struct node_jogo  *next_ht, *next_lista;
} *link_jogo;

/* Estrutura que representa a lista ligada dos jogos */
typedef struct {
    struct node_jogo *primeiro, *ultimo;
} lista_jogos;


link_jogo *inicializa_ht_jogos();
lista_jogos *inicializa_lista_jogos();
link_jogo novo_jogo(char *nome_jogo, char *equipa1, char *equipa2,
                    int score1, int score2, link_equipa *ht_equipas);
void adiciona_jogo_lista(link_jogo jogo, lista_jogos *lista);
void adiciona_jogo_ht(link_jogo jogo, link_jogo *ht);
link_jogo procura_jogo(char *nome_jogo, link_jogo *ht);
void remove_jogo_lista(link_jogo jogo, lista_jogos *lista);
void remove_jogo_ht(link_jogo jogo, link_jogo *ht);
void liberta_jogo(link_jogo jogo);
void destroi_estrut_jogos(lista_jogos *lista, link_jogo *ht);

#endif
