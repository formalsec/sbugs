#ifndef _JOGOS_H_
#define _JOGOS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Equipas.h"

/* Definicao de estruturas relacionadas com jogos. */

typedef struct
{
    char* nome;
    equipa* eq_casa;
    equipa* eq_fora;
    int golos_casa;
    int golos_fora;
} jogo;

typedef struct node_jogo
{
    jogo* jogo;
    struct node_jogo *prox, *ant;
} node_jogo;

typedef struct
{
    struct node_jogo *inicio, *fim;
} lista_jogos;

/* Definicao dos prototipos das funcoes existentes no ficheiro Jogos.c. */

lista_jogos* cria_lst_jogos();

jogo* cria_jogo(char* nome, equipa* eq_casa, equipa* eq_fora, int golos_casa, int golos_fora);

void insere_fim_jogo(lista_jogos* l, jogo* novo_jogo);

void remove_jogo_lst(lista_jogos* l, char* nome);

void destroi_lst_jogos(lista_jogos* l);

jogo** insere_jogo_h(jogo** h_jogos, jogo* novo_jogo, int* cont_jogos, int* tam_h_jogos);

jogo** expande_h_jogos(jogo** h_jogos, int* cont_jogos, int* tam_h_jogos);

jogo* procura_jogo_h(char* nome, jogo** h_jogos, int tam_h_jogos);

void destroi_h_jogos(jogo** h_jogos, int tam_h_jogos);

#endif