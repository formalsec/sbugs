#ifndef TIPOS_H
#define TIPOS_H

/******************************************************************************
 * Bibliotecas:
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

/******************************************************************************
 * Estruturas:
******************************************************************************/

/********************************** Game *************************************/

/* Estrutura que define o tipo Game (que representa os jogos) e as suas 
caracteristicas. */
typedef struct game {
    char *name;
    char *team1, *team2;
    int score_team1, score_team2;
} Game;

/********************************** Team *************************************/

/* Estrutura que define o tipo Team (que representa as equipas) e as suas 
caracteristicas. */
typedef struct team {
    char *name;
    int wins;
} Team;

/******************************************************************************
 * Abstracoes:
******************************************************************************/

/********************************** Game *************************************/

/* Abstracoes utilizadas no acesso a parametros de variaveis do tipo Game. */
#define team1(a) ((a)->team1)
#define team2(a) ((a)->team2)
#define score_team1(a) ((a)->score_team1)
#define score_team2(a) ((a)->score_team2)

/********************************** Team *************************************/

/* Abstracao utilizada no acesso a um parametro das variaveis do tipo Team. */
#define wins(a) ((a)->wins)

/********************************** Geral ************************************/

/* Abstracao utilizada no acesso a um parametro das variaveis dos tipo Game e 
Team. */
#define name(a) ((a)->name)

/******************************************************************************
 * Prototipos:
******************************************************************************/

/********************************** Game *************************************/

/* new_game: Funcao que cria um novo jogo, e devolve um ponteiro para o mesmo. 
 nome: parametro que representa o nome do jogo.
 equipa1, equipa2: parametros que representam os nomes das equipas do jogo.
 score1, score2: parametros que representam as pontuacoes finais das equipas. */
Game* new_game(char *nome, char *equipa1, char *equipa2, int score1, int score2);

/* change_score: Funcao que altera a pontuacao de um jogo existente. 
 jogo: parametro que representa o ponteiro para o jogo.
 score1, score2: parametros que representam as novas pontuacoes. */
void change_score(Game *jogo, int score1, int score2);

/* key_game: Funcao que acede e devolve a chave que identifica o jogo numa 
tabela de dispersao.
 item: parametro que representa o ponteiro para o no da lista com o jogo. */
char* key_game(void *item);

/* print_game_list: Funcao que imprime todos os elementos de um jogo numa lista. 
 item: parametro que representa o ponteiro para o jogo. */
void print_game_list(void *item);

/* print_game: Funcao que imprime todos os elementos de um jogo. 
 jogo: parametro que representa o ponteiro para o jogo. */
void print_game(Game *jogo);

/* free_game: Funcao que liberta toda a memoria associada a um jogo. 
 item: parametro que representa o ponteiro para o jogo. */
void free_game(void *item);

/********************************** Team *************************************/

/* new_team: Funcao que cria uma nova equipa, e devolve o ponteiro para a mesma. 
 nome: parametro que representa o nome da equipa. */
Team* new_team(char *nome);

/* add_win: Funcao que adiciona uma vitoria 'a equipa. 
 equipa: parametro que representa o ponteiro para a equipa. */
void add_win(Team *equipa);

/* remove_win: Funcao que subtrai uma vitoria 'a equipa. 
 equipa: parametro que representa o ponteiro para a equipa. */
void remove_win(Team *equipa);

/* key_team_bt: Funcao que acede e devolve a chave que identifica a equipa numa 
arvore binaria.
 item: parametro que representa o ponteiro para a equipa. */
int key_team_bt(void *item);

/* key_team_lp: Funcao que acede e devolve a chave que identifica a equipa numa 
tabela de dispersao.
 item: parametro que representa o ponteiro para a equipa. */
char* key_team_lp(void *item);

/* print_team_bt: Funcao que imprime o nome de uma equipa. 
 equipa: parametro que representa o ponteiro para a equipa. */
void print_team_bt(Team *equipa);

/* print_team_lp: Funcao que imprime o nome e o numero de vitorias de uma equipa. 
 item: parametro que representa o ponteiro para a equipa. */
void print_team_lp(void *item);

/* free_team: Funcao que liberta toda a memoria associada a uma equipa. 
 item: parametro que representa o ponteiro para a equipa. */
void free_team(void *item);

/********************************** Geral ************************************/

/* hash: Funcao que gera e distribui indices para uma tabela de dispersao, e 
devolve esse mesmo indice
 chave: parametro que representa a chave do elemento.
 tamanho: parametro que representa o tamanho da tabela de dispersao. */
long hash(void *chave, long tamanho);

#endif
