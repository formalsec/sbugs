#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "estruturas.h"

/* inicializa a hashtable de jogos */
JOGO ** ht_jogos_init(){
	int i;
	JOGO ** ht = can_fail_malloc(sizeof(JOGO)*TAMANHO_HASHTABLE_MAX);

	for (i = 0; i < TAMANHO_HASHTABLE_MAX; i++)
		ht[i] = NULL;

	return ht;
}

/* inicializa uma lista ligada de jogos */
LISTA * lista_jogos_init(){
	LISTA * nova_lista;
	nova_lista = NULL;
	return nova_lista;
}

/* retorna um ponteiro com um novo jogo */
JOGO * cria_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2, EQUIPA **ht){
	JOGO * novo_jogo = can_fail_malloc(sizeof(JOGO));

	novo_jogo->nome = can_fail_malloc(sizeof(char *)*(strlen(nome)+1));
	strcpy(novo_jogo->nome, nome);

	novo_jogo->equipa1 = procura_equipa_aux(equipa1, ht);
	novo_jogo->equipa2 = procura_equipa_aux(equipa2, ht);

	novo_jogo->score1 = score1;
	novo_jogo->score2 = score2;

	if (score1 > score2)
		novo_jogo->equipa1->jogos_ganhos++;
	if (score1 < score2)
		novo_jogo->equipa2->jogos_ganhos++;

	return novo_jogo;
}

/* adiciona um jogo a lista ligada */
LISTA ** adiciona_jg_lista(LISTA ** lista, JOGO * jogo){
    LISTA * aux = * lista;
    LISTA * nova_lista = can_fail_malloc(sizeof(LISTA));

    nova_lista->jogo = jogo;
    nova_lista->next = NULL;
    /* se a lista e vazia*/
    if (*lista == NULL)
    {
        *lista = nova_lista;
        return lista;
    }
    nova_lista->next = aux;
    *lista = nova_lista;
    return lista;
}

/* devolve um ponteiro para o jogo com o nome dado se existir, caso contrario devolve NULL*/
JOGO * procura_jogo_aux(char * nome, JOGO ** ht){
	int hash;
	JOGO * jogo;

	hash = funcao_hash(nome, TAMANHO_HASHTABLE_MAX);
	jogo = ht[hash];

	if (jogo == NULL)
		return NULL;

	while (jogo != NULL)
	{
		if (strcmp(jogo->nome, nome) == 0)
			return jogo;
		jogo = jogo->next;
	}
	return NULL;
}

/* apaga um jogo dado da hashtable dos jogos*/
void apaga_jg_ht(JOGO ** ht_jg, JOGO * jogo){
	int hash;
	JOGO * anterior, * node;

	hash = funcao_hash(jogo->nome, TAMANHO_HASHTABLE_MAX);
	node = ht_jg[hash];
	/* quando se apaga o 1o jogo */
	if (node != NULL && strcmp(node->nome, jogo->nome) == 0)
	{
		ht_jg[hash] = ht_jg[hash]->next;
		free(jogo->nome);
		free(jogo);
		return;
	}
	while (node != NULL && strcmp(node->nome, jogo->nome) != 0)
	{
		anterior = node;
		node = node->next;
	}
	anterior->next = node->next;

	free(jogo->nome);
	free(jogo);
}

/* apaga um jogo dado da lista ligada de jogos*/
void apaga_jg_lista(LISTA ** lista, JOGO * jogo){
	LISTA * node = * lista, * aux;

	if (node->next == NULL)
		{
			*lista = NULL;
			free(node);
			return;
		}
	/* se queremos apagar o primeiro elemento da lista*/
	if (strcmp(node->jogo->nome, jogo->nome) == 0)
	{
		*lista = node->next;
		free(node);
		return;
	}
	while (node->next != NULL)
	{
		if (strcmp(node->next->jogo->nome, jogo->nome) == 0)
		{
			aux = node->next;
			node->next = node->next->next;
			free(aux);
			return;
		}
		node = node->next;
	}
}

/* liberta a memoria alocada na hashtable dos jogos*/
void destroi_ht_jg(JOGO ** ht_jg){
	int hash = 0;
	JOGO * jogo;

	for (; hash < TAMANHO_HASHTABLE_MAX; hash++)
	{
		while (ht_jg[hash] != NULL)
		{
			jogo = ht_jg[hash];
			ht_jg[hash] = ht_jg[hash]->next;
			free(jogo->nome);
			free(jogo);
		}
	}
}

/* liberta a memoria alocada na lista ligada dos jogos*/
void destroi_lista_jg(LISTA ** lista){
	LISTA * node = * lista, * aux;

	while (node != NULL)
	{
		aux = node;
		node = node->next;
		free(aux);
	}
	free(node);
}

/* Fim */
