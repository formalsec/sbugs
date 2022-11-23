#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "ListaLigadaEquipa.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/* Cria uma equipa. */
Equipa* e_criar(char* nome) {
	Equipa* equipa = can_fail_malloc(sizeof(Equipa));
	equipa->nome_equipa = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
	strcpy(equipa->nome_equipa, nome);
	equipa->vitorias = 0;
	return equipa;
}

/* Cria nova lista vazia. */
Lista_Ligada_Equipa* ll_criar_equipa() {
	Lista_Ligada_Equipa* l = can_fail_malloc(sizeof(Lista_Ligada_Equipa));
	l->inicio = l->ultimo = NULL;
	return l;
}

/* Liberta toda a memoria associada ao no. */
void free_no_equipa(No_Equipa* n) {
	free(n->equipa->nome_equipa);
	free(n->equipa);
	free(n->chave);
	free(n);
}

/* Liberta toda a memoria associada a lista. */
void free_lista_ligada_equipa(Lista_Ligada_Equipa* l) {
	No_Equipa* tmp;
	while (l->inicio) {
		tmp = l->inicio->prox;
		free_no_equipa(l->inicio);
		l->inicio = tmp;
	}
	free(l);
}

/* Cria um novo no com a memoria necessaria para guardar uma equipa. */
No_Equipa* no_inserir_equipa(Equipa* equipa, char* chave) {
	No_Equipa* n = can_fail_malloc(sizeof(No_Equipa));
	n->prox = NULL;
	n->ant = NULL;
	n->equipa = equipa;
	n->chave = can_fail_malloc(sizeof(char) * (strlen(chave) + 1));
	strcpy(n->chave, chave);

	return n;
}

/* Adiciona uma equipa como o ultimo elemento da lista. */
void ll_inserir_equipa(Lista_Ligada_Equipa* l, Equipa* equipa, char* chave) {
	No_Equipa* n = no_inserir_equipa(equipa, chave);
	n->ant = l->ultimo;

	if (l->ultimo)
		l->ultimo->prox = n;
	l->ultimo = n;

	if (!l->inicio)
		l->inicio = n;
}