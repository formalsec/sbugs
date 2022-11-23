#ifndef JOGOS
#define JOGOS

#include <string.h>

#define EQ_JOGO(A, B) !strcmp(A->nome, B)

typedef struct jogo {
    char *nome, *eq1, *eq2; /* Nomes do jogo e das equipas */
    int sc1, sc2; /* Pontuacoes das equipas */
} jogo;

typedef jogo Item_j;

/* Inicializa o jogo com as variaveis necessarias */
Item_j* inicializa_jogo(char *nome, char *eq1, char *eq2, int sc1, int sc2);

/* Liberta a memoria reservada para guardar as propriedades do jogo j */
void liberta_jogo(Item_j *j);

/* Altera o resultado do jogo j */
void altera_pontuacao(Item_j *j, int sc1, int sc2);

/* Retorna o nome do jogo j */
char* nome_jogo(Item_j *j);

/* Retorna o nome da equipa 1 do jogo j */
char* nome_eq1(Item_j *j);

/* Retorna o nome da equipa 2 do jogo j */
char* nome_eq2(Item_j *j);

/* Retorna a pontuacao da equipa 1 do jogo j */
int pontuacao_eq1(Item_j *j);

/* Retorna a pontuacao da equipa 2 do jogo j */
int pontuacao_eq2(Item_j *j);

#endif