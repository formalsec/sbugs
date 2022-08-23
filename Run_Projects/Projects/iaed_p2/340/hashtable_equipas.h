#ifndef HASHEQUIPA_H
#define HASHEQUIPA_H
#include "equipas.h"
#include "lista_ligada_nomes.h"

/* Estrutura da Hashtable equipas. */
typedef struct node{
	Equipa *equipas;
	struct node *next;
}table_e;

#define equipas_hash(a) (a->equipas)
#define prox_head(a) (a->next)

int hash(char *nome, int M);
table_e **inicializa_e(table_e **head, int M);
Equipa *encontra(Equipa *head, char *nome);
void adiciona_e(table_e **heads, Equipa *head, int M);
Equipa *procura_equipa_hash(table_e **heads, Chave c, int M);
int mais_ganhos(table_e **heads, int M, int *count);
void free_hash_equipas(table_e **heads, int M);



#endif /* HASHEQUIPA_H */