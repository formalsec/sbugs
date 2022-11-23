#ifndef _EQUIPA_H
#define _EQUIPA_H

#define MAX_STRING 1023
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct str_equipa{
	char* nome;
	int vitorias;
} Equipa;

/* Devolve uma variavel Equipa com o nome dado */
Equipa novaEquipa(char* nome);

/* Liberta toda a memoria reservada por e */
void destroiEquipa(Equipa e);
#endif