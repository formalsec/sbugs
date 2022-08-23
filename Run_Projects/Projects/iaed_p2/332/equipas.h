#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef EQUIPAS_H
#define EQUIPAS_H

/* tamanho maximo do nome de uma equipa */
#define MAX_NOME 1023

/* estrutura das equipas */
typedef struct equipa {
	char * nome_equipa;
	int vitorias;
} * equipa;

/* funcoes relacionadas com as equipas */
void adiciona_equipa(int nl, equipa * ht);
void free_equipa(equipa x);
equipa cria_equipa(char * nome);
void encontra_equipa(int nl, equipa * ht);
void melhores_equipas(int nl, equipa * ht);


/* algumas funcoes auxiliares */
char *strdup(const char *src);
int compara_palavras(const void * a, const void * b);

#endif