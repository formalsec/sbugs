#ifndef HASHJOGO_H
#define HASHJOGO_H
#include "jogos.h"

/* Estrutura da hashtable jogos. */
typedef struct node2{
	Jogo *jogos;
	struct node2 *next;
}table_j;


#define jogos_hash(a) (a->jogos)
#define prox_head_j(a) (a->next)


table_j **inicializa_j(table_j **head, int M);
void adiciona_j(table_j **heads, Jogo *head, int M);
Jogo *encontra_j(Jogo *head, char *nome);
Jogo *procura_jogo_hash(table_j **heads, Chave_j nome, int M);
int remove_j(table_j **heads, Chave_j nome, int M);
void free_hash_jogos(table_j **heads, int M);



#endif /* HASHJOGO_H */