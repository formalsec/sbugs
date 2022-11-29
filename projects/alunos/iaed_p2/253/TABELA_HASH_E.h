#ifndef TABELA_HASH_E
#define TABELA_HASH_E
#include <stdlib.h>
#include <string.h>
#include "STRUCT_JOGOS.h"

#define T_INICIAL 1999							/* Tamanho/Capacidade inicial da hash table */
#define MAX_NOME 1024							/* Maximo de caracteres de um nome (+ \0) */

/* Definicao da estrutura da Equipa. */
typedef struct eq
{
	struct eq *proximo;
	char *nome;
	int pontos;
} Equipa;

/* Definicao da estrutura da lista ligada de Equipas. */
typedef struct 
{
	Equipa *topo;
} listE;

/* Definicao da estrutura do no da hash table. */
typedef struct no_hash
{
	struct no_hash *proximo;
	struct no_hash *anterior;
	Equipa *ponteiro;
	Jogo *pont_jogo;
	
} No_hash ;

/* Definicao da estrutura da hash table. */
typedef struct 
{
	No_hash **topos;
	size_t   capacidade;
} Tabela_hash;


/* Declaracoes das funcoes. */
No_hash *cria_Jogo_hash(No_hash *ultimo, Jogo *novo_J);
int verifica_j(Tabela_hash *calendario, const char *nome);
void cria_Jogo(listJogos *jogos, const char *nome, const char *casa, const char *fora,\
int g_casa, int g_fora, Tabela_hash *calendario);
listE* cria_listE();	
void free_list(listE *l);
void free_Equipa(Equipa *n);
Tabela_hash *cria_tabela_hash();
int hash(const char *nome, int M);
void free_tabela_hash(Tabela_hash *t);
int verifica_e(Tabela_hash *tabela, const char *nome);
No_hash *cria_Equipa_hash(No_hash *topo, Equipa *nova_E);
void retira_pontos(Tabela_hash *tabela, const char *nome);
void aumenta_pontos(Tabela_hash *tabela, const char *nome);
void cria_Equipa(listE *l, const char *n, Tabela_hash *tabela);
void adiciona_jogo(listJogos *lista_jogos, Tabela_hash *calendario, Tabela_hash *tabela,\
int contador);
void procura_jogo(Tabela_hash *calendario, int contador);
void apaga_jogo(Tabela_hash *calendario,Tabela_hash *tabela, listJogos *lista_jogos, int contador);
void altera_resultado(Tabela_hash *calendario, Tabela_hash *tabela, int contador);
void altera_pontos(Tabela_hash *tabela, No_hash *jogo, int score_casa, int score_fora);
void adiciona_equipa(listE *lista_equipas, Tabela_hash *tabela, int contador);
void procura_equipa(Tabela_hash *tabela,int contador);
void vencedores(listE *lista_equipas, int contador);
#endif