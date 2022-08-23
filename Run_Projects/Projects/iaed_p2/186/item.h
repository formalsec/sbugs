#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* numero maximo de caracteres do nome do jogo e das equipas*/
#define MAX_STR 1023


/* estrutura que define um item, podendo ser um jogo ou uma equipa*/
typedef struct str_item{
    struct str_item * next; /* ponteiro da estrutura que aponta para o proximo elemento */
    struct str_item * prev; /* ponteiro da estrutura que aponta para o elemento anterior */
    struct str_item * next_hash; /* ponteiro da estrutura que aponta para o proximo elemento na hashtable */
    char* nome; /* nome do item */
    char* equipa1; /* nome da primeira equipa do jogo introduzido (se o item for um jogo) */ 
    char* equipa2; /* nome da segunda equipa do jogo introduzido (se o item for um jogo) */ 
    int score1; /* pontuacao da primeira equipa do jogo introduzido (se o item for um jogo) */ 
    int score2; /* pontuacao da segunda equipa do jogo introduzido (se o item for um jogo) */ 
    int vitorias; /* numero de vitorias da equipa (se o item for uma equipa) */
} Item;


/* estrutura que define uma fila de jogos; facilita a listagem dos jogos pela ordem de introducao */ 
typedef struct str_l_jogo{
    struct str_item * head; /* ponteiro  que aponta para o primeiro jogo da lista*/
    struct str_item * last; /* ponteiro  que aponta para o ultimo jogo da lista*/
} lista_jogo;


/* recebe os dados relativamento a um jogo e cria a estrutura associada ao mesmo */
Item * cria_jogo(char * nome, char * equipa1, char * equipa2, int score1, int score2);

/* recebe o nome de uma equipa e cria a estrutura associada 'a mesma */
Item * cria_equipa(char * nome);

/* apaga na memoria todas as estruturas associadas aos jogos */
void apaga_jogos(lista_jogo * l);

/* apaga na memoria todas as estruturas associadas 'as equipas */
void apaga_equipas(Item * head_equipa);


#endif