#ifndef HASHEQUIPA
#define HASHEQUIPA
#include "ListaLigadaEquipa.h"

/*
	--------------------- STRUCT ---------------------
*/

typedef struct {
	Lista_Ligada_Equipa** entradas;
	int cap;
	int qtd;
} Hashtable_Equipa;

/*  --------------------------------------------------- */

/* Cria a hashtable, alocando a memoria necessaria. */
Hashtable_Equipa* ht_criar_equipa(int max);

/* Calcula o index que sera armazenada a equipa. */
int ht_hash_equipa(Hashtable_Equipa* ht, char* chave);

/* Insere a equipa na hashtable. */
void ht_inserir_equipa(Hashtable_Equipa* ht, Equipa* equipa, char* chave);

/* Verifica a exitencia de uma equipa, dada uma chave. */
Equipa* ht_pesquisar_equipa(Hashtable_Equipa* ht, char* chave);

/* Liberta todas as instancias e memoria alocada da hashtable. */
void free_hash_equipa(Hashtable_Equipa* ht);

#endif