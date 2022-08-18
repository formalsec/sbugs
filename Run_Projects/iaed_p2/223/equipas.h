#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

#ifndef EQUIPA_H
#define EQUIPA_H
typedef struct equipa {
	char *nome;
	int vitorias;
} *Equipa;

Equipa novaEquipa(char *nome);
void libertaEquipa(Equipa e);
void imprimeEquipa(Equipa e);
void aumentaVitorias(Equipa e);
void diminuiVitorias(Equipa e);
int obterVitorias(Equipa e);
char * obterNomeEquipa(Equipa e);
#endif