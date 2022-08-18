#ifndef _EQUIPA_
#define _EQUIPA_

#include <string.h>
#include <stdlib.h>

typedef struct equipa{
    char* nome;
    int vitorias;
}Equipa;

/* Duplica um nome (ou uma string qualquer). Aloca memoria apenas para o tamanho do nome dado */
char *strdup_nome(char*);

/* Aloca memoria para uma equipa e inicializa */
Equipa* cria_equipa(char*);

/* Liberta a memoria de uma equipa */
void free_equipa(Equipa*);

/* Retorna o score de uma equipa */
int get_score_equipa(Equipa*);

/* Retorna o nome de uma equipa */
char* get_nome_equipa(Equipa*);

/* Soma ao score de uma equipa */
void alt_score_equipa(Equipa*,int);

#endif