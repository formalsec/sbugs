#ifndef AUX_H
#define AUX_H

#include "p2.h"             /* Header file que contem as estruturas utilizadas no projeto e os comandos */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

#define MAX 3100           /* tamanho maximo que o input pode receber */
#define TAMANHO 10003      /* tamanho das hashtables */


/* Funcoes utilizadas para a lista de equipas */
Lista_equipas *criar_lista();

void liberta_lista_equipas(Lista_equipas *lista_equipa);


/* Funcoes utilizadas para a hashtable das equipas */
unsigned int hash(char *key);

hashtable_equipas *criar_equipas();

Equipa *ht_equipas_aloca(char *key);

void ht_equipas_insere(hashtable_equipas *hashtable, char *key);

Equipa *ht_equipas_verifica(hashtable_equipas *hashtable, char *key);

void libertar_equipas(hashtable_equipas *hashtable);


/* Funcoes utilizadas para a lista de jogos */
Lista_jogos *criar_lista_j();

void liberta_lista(Lista_jogos *lista_jogo); 


/* Funcoes utilizadas para a hashtable dos jogos */
hashtable_jogos *criar_jogos();

Jogo *ht_jogos_verifica(hashtable_jogos *hashtable_j, char *key);

void ht_jogos_apaga(hashtable_jogos *hashtable_j, char *key);

void libertar_jogos(hashtable_jogos *ht_jogos);


/*  Funcao que compara 2 strings */
int compara(const void *ptr1, const void *ptr2);
#endif
