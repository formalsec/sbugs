#ifndef FUNCOES_AUX_H
#define FUNCOES_AUX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*tamanho de cabecas das hashtables*/
#define N_MOD 3013
/*dimensao maxima das strings*/
#define MAX_CHAR 1024

int calcula_chave(char nome[]);

int verifica_se_jogo_existe(int chave, char nome[],noh *cabeca[]);

int verifica_se_equipa_existe(int chave, char equipa[],noh_equipa *cabeca_equipa[]);

int cmp (const void * a, const void * b);

void free_total(int *contador_input,noh *cabeca[],noh_equipa *cabeca_equipa[],fila *fila_jogos);

void lista_com_equipas_melhores_e_sort(int *contador_input, int max, noh_equipa *cabeca_equipa[]);

#endif