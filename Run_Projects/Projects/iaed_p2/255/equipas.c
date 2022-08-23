#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "estruturas.h"

/* funcao de hash - atribui chaves da hashtable aos elementos */
int funcao_hash(char *v, int M){
	int h, a = 31415, b = 27183;

	for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
		h = (a*h + *v) % M;
	return h;
}

/* inicializa a hashtable das equipas */
EQUIPA ** ht_equipas_init(){
	int i;
	EQUIPA ** ht = malloc(sizeof(EQUIPA *)*TAMANHO_HASHTABLE_MAX);

	for (i = 0; i < TAMANHO_HASHTABLE_MAX; i++)
		ht[i] = NULL;
	return ht;
}

/* inicializa a lista ligada das equipas*/
LISTA_EQ * lista_equipas_init(){
	LISTA_EQ * nova_lista;
	nova_lista = NULL;
	return nova_lista;
}

/* retorna um ponteiro com uma nova equipa*/
EQUIPA * cria_equipa(char * nome){
	EQUIPA * nova_equipa = malloc(sizeof(EQUIPA));

	nova_equipa->nome = malloc(sizeof(char *)*(strlen(nome)+1));
	strcpy(nova_equipa->nome, nome);

	nova_equipa->jogos_ganhos = 0;
	
	return nova_equipa;
}

/* adiciona uma equipa a lista ligada */
LISTA_EQ ** adiciona_eq_lista(LISTA_EQ ** lista, EQUIPA * equipa){
	LISTA_EQ * ultimo = * lista;
	LISTA_EQ * nova_lista = malloc(sizeof(LISTA_EQ));

	nova_lista->equipa = equipa;
	nova_lista->next = NULL;

	/*quando a lista nao tem elementos*/
	if (*lista == NULL)
	{
		*lista = nova_lista;
		return lista;
	}
	/*quando a lista tem apenas 1 elemento*/
	if (ultimo->next == NULL || strcmp(equipa->nome, ultimo->equipa->nome) < 0)
	{
		/*se queremos colocar antes do 1o elemento*/
		if (strcmp(equipa->nome, ultimo->equipa->nome) < 0)
		{
			nova_lista->next = ultimo;
			*lista = nova_lista;
			return lista;
		}
		/*se queremos colocar depois do 1o elemento*/
		if (strcmp(equipa->nome, ultimo->equipa->nome) > 0)
		{
			ultimo->next = nova_lista;
			nova_lista->next = NULL;
			return lista;
		}
	}

	while (ultimo->next != NULL)
	{
		if (strcmp(equipa->nome, ultimo->next->equipa->nome) < 0)
		{
			nova_lista->next = ultimo->next;
			ultimo->next = nova_lista;
			return lista;
		}
		ultimo = ultimo->next;
	}
	ultimo->next = nova_lista;
	nova_lista->next = NULL;
	return lista;
}

/* devolve um ponteiro para a equipa com o nome dado se existir, caso contrario devolve NULL*/
EQUIPA * procura_equipa_aux(char * nome, EQUIPA ** ht){
	int hash;
	EQUIPA * equipa;

	hash = funcao_hash(nome, TAMANHO_HASHTABLE_MAX);
	equipa = ht[hash];

	if (equipa == NULL)
		return NULL;

	while (equipa != NULL)
	{
		if (strcmp(equipa->nome, nome) == 0)
			return equipa;
		equipa = equipa->next;
	}
	return NULL;
}

/* liberta a memoria alocada na hashtable das equipas*/
void destroi_ht_eq(EQUIPA ** ht_eq){
	int hash = 0;
	EQUIPA * equipa;

	for (; hash < TAMANHO_HASHTABLE_MAX; hash++)
	{
		while (ht_eq[hash] != NULL)
		{
			equipa = ht_eq[hash];
			ht_eq[hash] = ht_eq[hash]->next;
			free(equipa->nome);
			free(equipa);
		}
	}
}

/* liberta a memoria alocada na lista das equipas*/
void destroi_lista_eq(LISTA_EQ ** lista){
	LISTA_EQ * node = * lista;

	while (node != NULL)
	{
		*lista = node;
		node = node->next;
		free(*lista);
	}
}

/* Fim */
