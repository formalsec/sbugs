#ifndef STRUCT_JOGOS
#define STRUCT_JOGOS
#include <stdlib.h>
#include <string.h>
#include "TABELA_HASH_E.h"

/* Definicao da estrutura do Jogo. */
/* A definicao permite a criacao de uma lista ligada. */
typedef struct jogo
{
	struct jogo *proximo;
	struct jogo *anterior;
	char *nome;
	char *eqcasa;
	char *eqfora;
	int golos_casa;
	int golos_fora;
} Jogo ;

/* Definicao da estrutura da lista ligada de Jogos. */
typedef struct 
{
	Jogo *primeiro;
	Jogo *ultimo;	
} listJogos;

/* Declaracoes das funcoes. */
listJogos* cria_listJogos();
void free_Jogo(Jogo *n);
void rm_jogo(listJogos *lista_jogos, Jogo *jogo);
void free_listJ(listJogos *l);
void lista_todos_jogos(listJogos *lista_jogos, int contador);
#endif
