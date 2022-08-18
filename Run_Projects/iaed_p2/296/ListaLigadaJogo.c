#include "ListaLigadaJogo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Cria um jogo. */
Jogo* j_criar(Equipa* equipa_1, Equipa* equipa_2, int score_equipa_1, int score_equipa_2) {
	Jogo* jogo = malloc(sizeof(Jogo));
	jogo->equipa_1 = equipa_1;
	jogo->equipa_2 = equipa_2;
	jogo->score_equipa_1 = score_equipa_1;
	jogo->score_equipa_2 = score_equipa_2;
	return jogo;
}

/* Verifica qual eh a equipa vencedora de um jogo. */
Equipa* vencedor(Jogo* jogo) {
	if (jogo->score_equipa_1 > jogo->score_equipa_2)
		return jogo->equipa_1;
	else if (jogo->score_equipa_1 < jogo->score_equipa_2)
		return jogo->equipa_2;
	else
		return NULL;
}

/* Cria nova lista vazia. */
Lista_Ligada_Jogo* ll_criar_jogo() {
	Lista_Ligada_Jogo* l = malloc(sizeof(Lista_Ligada_Jogo));
	l->inicio = l->ultimo = NULL;
	return l;
}

/* Liberta toda a memoria associada ao no. */
void free_no_jogo(No_Jogo* n) {
	free(n->jogo);
	free(n->chave);
	free(n);
}

/* Liberta toda a memoria associada a lista. */
void free_lista_ligada_jogo(Lista_Ligada_Jogo* l) {
	No_Jogo* tmp;
	while (l->inicio) {
		tmp = l->inicio->prox;
		free_no_jogo(l->inicio);
		l->inicio = tmp;
	}
	free(l);
}

/* Cria um novo no com a memoria necessaria para guardar um jogo. */
No_Jogo* no_inserir_jogo(Jogo* jogo, char* chave) {
	No_Jogo* n = malloc(sizeof(No_Jogo));
	n->prox = NULL;
	n->ant = NULL;
	n->jogo = jogo;
	n->chave = malloc(sizeof(char) * (strlen(chave) + 1));
	strcpy(n->chave, chave);

	return n;
}

/* Adiciona uma equipa como o ultimo elemento da lista. */
void ll_inserir_jogo(Lista_Ligada_Jogo* l, Jogo* jogo, char* chave) {
	No_Jogo* n = no_inserir_jogo(jogo, chave);
	n->ant = l->ultimo;

	if (l->ultimo)
		l->ultimo->prox = n;
	l->ultimo = n;

	if (!l->inicio)
		l->inicio = n;
}

/* Deleta um no da lista ligada. */
void ll_deletar_no(Lista_Ligada_Jogo* l, No_Jogo* n){
	if (n->ant == NULL)
		l->inicio = n->prox;
	else
		n->ant->prox = n->prox;

	if (n->prox == NULL)
		l->ultimo = n->ant;
	else
		n->prox->ant = n->ant;
}

/* Deleta um jogo dado uma chave e retorna sucesso ou falha. */
void ll_deletar_jogo(Lista_Ligada_Jogo* l, char* chave) {
	No_Jogo* tmp = l->inicio;
	while (tmp){
		if (strcmp(tmp->chave, chave) == 0) {
			ll_deletar_no(l, tmp);
			free_no_jogo(tmp);
			return;
		}
		tmp = tmp->prox;
	}
}