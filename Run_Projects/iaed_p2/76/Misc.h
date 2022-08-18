#ifndef _MISC_H_
#define _MISC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Equipas.h"

/* Definicao de constantes usadas diretamente no ficheiro Main.c e indiretamente nos ficheiros Equipas.c e Jogos.c. */

#define MAX 1024
#define HASH 101

/* Definicao dos prototipos das funcoes existentes no ficheiro Misc.c. */

int hash(char *nome, int M);

int comparador (const void * a, const void * b);

void atribui_vitoria (equipa* eq_casa, equipa* eq_fora, int golos_casa, int golos_fora);

void repor_score (equipa* eq_casa, equipa* eq_fora, int golos_casa, int golos_fora);

#endif