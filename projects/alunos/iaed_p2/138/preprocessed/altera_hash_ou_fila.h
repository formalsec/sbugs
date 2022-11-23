#ifndef ALTERA_HASH_OU_FILA_H
#define ALTERA_HASH_OU_FILA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*tamanho de cabecas das hashtables*/
#define N_MOD 3013
/*dimensao maxima das strings*/
#define MAX_CHAR 1024

fila* faz_fila();

void atualiza_jogos_ganhos(noh_equipa *cabeca_equipa[],int chave_equipa1,int chave_equipa2,int score1,int score2, char equipa1[],char equipa2[]);

void adiciona_jogo_lista_fila(int chave, jogo *jogo_temp, noh *cabeca[], fila *fila_jogos);

void apaga_da_fila(char nome[],fila *fila_jogos);

void incrementa_uma_decrementa_outra(noh_equipa *cabeca_equipa[],char equipa1[],char equipa2[]);

void incrementa_uma(noh_equipa *cabeca_equipa[],char equipa[]);

void decrementa_uma(noh_equipa *cabeca_equipa[],char equipa[]);

#endif