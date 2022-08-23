#ifndef _FUNCOES_
#define _FUNCOES_
#define MAX_STRING 1024
#define HASH_SIZE 2000

#include "lista.h"
#include "hash_table_equipa.h"
#include "hash_table_jogo.h"

char LeCaracterInicial();

unsigned int hash_function(char *nome);



void free_jogos(jogo *hash[HASH_SIZE]);

void free_equipas(equipa *hash[HASH_SIZE]);

void free_listas(node *head);



jogo * Comando_a(int contador, equipa *hash_1[HASH_SIZE], jogo *hash_2[HASH_SIZE]);

equipa * Comando_A(int contador, equipa *hash[HASH_SIZE]);

int Comando_l(int contador, node *head);

void Comando_p(int contador, jogo *hash[HASH_SIZE]);

void Comando_P(int contador, equipa *hash[HASH_SIZE]);

jogo * Comando_r(int contador, jogo *hash_1[HASH_SIZE], equipa *hash_2[HASH_SIZE]);

node * Comando_s(int contador, jogo *hash_1[HASH_SIZE], equipa *hash_2[HASH_SIZE], node *head);

int Compara_strings(const void *string_1,const void *string_2);

int Comando_g(int contador, equipa *hash[HASH_SIZE]);

#endif