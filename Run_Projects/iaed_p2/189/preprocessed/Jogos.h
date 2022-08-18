#ifndef _JOGOS_H
#define _JOGOS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct jogo 
{
    char *nome, *equipa1, *equipa2;
    int score1, score2;
} *ptr_jogo;

typedef struct no_jogos
{
    ptr_jogo jogo;
    struct no_jogos *proximo;
} *link_j; /*ponteiro para no*/

/*---------- funcoes de listas ligadas ----------*/
/*cria um novo jogo*/
ptr_jogo novo_jogo(char *nome, char *eq1, char *eq2, int score1, int score2);

/*insere um jogo j1 no fim da lista ligada*/
link_j insere_fim_j(link_j primeiro_jogo, link_j j1);

/*insere um jogo j1 no inicio da lista ligada*/
link_j insere_inicio_j(link_j inicio, link_j j1);

/*procura um jogo numa lista ligada*/
link_j procura_j(link_j primeiro_jogo, char* nome);

/*da free dos nomes do jogo e das equipas*/
void FreeNomes_j (link_j x);

/*da free do no_jogo*/
void FreeNode_j(link_j x);

/*apaga um jogo e da free aos seus elementos alocados*/
link_j apaga_j(link_j *primeiros_j, link_j primeiro_jogo, char* nome, link_j *fim_lista);

/*---------- funcoes da hashtable dos jogos ----------*/

/*inicializa a hashtable dos jogos*/
link_j* inicializa_j(link_j *primeiros_j);

/*insere jogo na hashtable*/
void insere_jogo(link_j *primeiros_j, link_j j1);

/*procura um jogo numa hashtable de jogos*/
link_j procura_jogo(link_j *primeiros_j, char* nome);

/*apaga um jogo*/
link_j apaga_jogo(link_j *primeiros_j,char *nome);

#endif
