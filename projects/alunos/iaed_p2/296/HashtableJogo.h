#ifndef HASHJOGO
#define HASHJOGO

#include "ListaLigadaJogo.h"

/*
	--------------------- STRUCT ---------------------
*/

typedef struct {
	Lista_Ligada_Jogo** entradas;
	int cap;
	int qtd;
} Hashtable_Jogo;

/*  --------------------------------------------------- */

/* Cria a hashtable, alocando a memoria necessaria. */
Hashtable_Jogo* ht_criar_jogo(int max);

/* Calcula o index que sera armazenado o jogo. */
int ht_hash_jogo(Hashtable_Jogo* ht, char* chave);

/* Insere o jogo na hashtable. */
void ht_inserir_jogo(Hashtable_Jogo* ht, Jogo* jogo, char* chave);

/* Deleta um jogo da hashtable. */
void ht_deletar_jogo(Hashtable_Jogo* ht, char* key);

/* Verifica a exitencia de um jogo, dada uma chave. */
Jogo* ht_pesquisar_jogo(Hashtable_Jogo* ht, char* chave);

/* Liberta todas as instancias e memoria alocada da hashtable. */
void free_hash_jogo(Hashtable_Jogo* ht);

#endif