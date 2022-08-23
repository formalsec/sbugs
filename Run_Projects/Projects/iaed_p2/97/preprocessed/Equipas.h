#ifndef EQUIPAS
#define EQUIPAS

#include <string.h>

#define EQ_EQUIPA(A, B) !strcmp(A->nome, B)

typedef struct equipa {
    char *nome; /* Nome da equipa */
    int ganhos; /* Numero de jogos ganhos */
} equipa;

typedef equipa Item_eq;

/* Inicializa a equipa com as variaveis necessarias */
Item_eq* inicializa_equipa(char *nome);

/* Liberta a memoria reservada para guardar as propriedades da equipa */
void liberta_equipa(Item_eq *e);

/* Aumenta a pontuacao da equipa em um ponto */
void aumenta_pontuacao(Item_eq *e);

/* Diminui a pontuacao da equipa em um ponto */
void diminui_pontuacao(Item_eq *e);

/* Retorna o nome da equipa no Item_j e */
char* nome_equipa(Item_eq *e);

/* Retorna o numero de jogos ganhos da equipa */
int ganhos_equipa(Item_eq *e);

#endif