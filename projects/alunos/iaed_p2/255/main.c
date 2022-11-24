#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "estruturas.h"

#define CHARMAX 1023

int main(){
	int contador_input = 0;
	char c;
	EQUIPA ** hashtable_equipas = ht_equipas_init();
	JOGO ** hashtable_jogos = ht_jogos_init();
	LISTA * lista_jogos = lista_jogos_init();
	LISTA_EQ * lista_equipas = lista_equipas_init();

	while (1)
	{
		switch (c = getchar())
		{
			case 'a': contador_input++;
				novo_jogo(contador_input, hashtable_equipas, hashtable_jogos, &lista_jogos); break;
			case 'A': contador_input++;
				nova_equipa(contador_input, hashtable_equipas, &lista_equipas); break;
			case 'l': contador_input++;
				lista_todos_jogos(contador_input, lista_jogos); break;
			case 'p': contador_input++;
				procura_jogo(contador_input, hashtable_jogos); break;
			case 'P': contador_input++;
				procura_equipa(contador_input, hashtable_equipas); break;
			case 'r': contador_input++;
				apaga_jogo(contador_input, hashtable_jogos, &lista_jogos); break;
			case 's': contador_input++;
				altera_score(contador_input, hashtable_jogos); break;
			case 'g': contador_input++;
				top_equipas(contador_input, &lista_equipas); break;
			case 'x':
				liberta_memoria(hashtable_equipas, hashtable_jogos, &lista_jogos, &lista_equipas);
				return 0;
		}
	}
	return 0;
}


/* a - Adiciona um novo jogo*/
void novo_jogo(int contador_input, EQUIPA ** ht_eq, JOGO ** ht_jg, LISTA ** lista){
	char nome[CHARMAX], equipa1[CHARMAX], equipa2[CHARMAX];
	int score1, score2;
	long hash;
	JOGO * novo_jogo, * jogo;
	EQUIPA * equipa1_aux, * equipa2_aux;

	/* nome:equipa1:equipa2:score1:score2*/
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2, &score1, &score2);

	/* se nao existir nenhum jogo com esse nome no sistema.*/
	jogo = procura_jogo_aux(nome, ht_jg);
	if (jogo != NULL)
	{
		printf("%d Jogo existente.\n", contador_input);
		return;
	}

	/* se nao existir nenhuma equipa com os nomes dados no sistema*/
	equipa1_aux = procura_equipa_aux(equipa1, ht_eq);
	equipa2_aux = procura_equipa_aux(equipa2, ht_eq);
	if (equipa1_aux == NULL || equipa2_aux == NULL)
	{
		printf("%d Equipa inexistente.\n", contador_input);
		return;
	}
	/* inicializa um novo jogo*/
	novo_jogo = cria_jogo(nome, equipa1, equipa2, score1, score2, ht_eq);
	/* adiciona jogo a ht dos jogos */
	hash = funcao_hash(novo_jogo->nome, TAMANHO_HASHTABLE_MAX);
	novo_jogo->next = ht_jg[hash];
	ht_jg[hash] = novo_jogo;
	/* adiciona o jogo a lista ligada*/
	lista = adiciona_jg_lista(lista, novo_jogo);
}


/* A - Adiciona uma nova equipa */
void nova_equipa(int contador_input, EQUIPA ** ht, LISTA_EQ ** lista){
	int hash;
	char nome[CHARMAX];
	EQUIPA * nova_equipa, * eq;

	/* nome */
	scanf(" %[^:\n]", nome);

	/*se ja existe uma equipa com esse nome no sistema*/
	eq = procura_equipa_aux(nome, ht);
	if (eq != NULL)
	{
		printf("%d Equipa existente.\n", contador_input);
		return;
	}
	/* inicializa uma nova equipa*/
	nova_equipa = cria_equipa(nome);
	/* adiciona a equipa a hashtable*/
	hash = funcao_hash(nova_equipa->nome, TAMANHO_HASHTABLE_MAX);
	nova_equipa->next = ht[hash];
	ht[hash] = nova_equipa;
	/* adiciona a equipa a lista ligada*/
	lista = adiciona_eq_lista(lista, nova_equipa);
}


/* l - Listas todos os jogos, pela ordem que foram introduzidos*/
void lista_todos_jogos(int contador_input, LISTA * lista){
    LISTA * copia_lista;
    copia_lista = lista;
    /* quando a copia da lista chegar ao ultimo elemento, imprime do fim para o inicio*/
    if (copia_lista == NULL)
        return;
    lista_todos_jogos(contador_input, copia_lista->next);
    printf("%d %s %s %s %d %d\n", contador_input, copia_lista->jogo->nome,
    	copia_lista->jogo->equipa1->nome, copia_lista->jogo->equipa2->nome,
    	copia_lista->jogo->score1, copia_lista->jogo->score2);
}


/* p - Procura um jogo dado o nome*/
void procura_jogo(int contador_input, JOGO ** ht_jg){
	char nome[CHARMAX];
	JOGO * jogo;

	/* nome */
	scanf(" %[^:\n]", nome);

	/* se nao existir nenhum jogo com esse nome no sistema*/
	jogo = procura_jogo_aux(nome, ht_jg);
	if (jogo == NULL)
	{
		printf("%d Jogo inexistente.\n", contador_input);
		return;
	}

	printf("%d %s %s %s %d %d\n", contador_input, jogo->nome, jogo->equipa1->nome,
		jogo->equipa2->nome, jogo->score1, jogo->score2);
}


/* P - Procura uma equipa dado o nome*/
void procura_equipa(int contador_input, EQUIPA ** ht){
	char nome[CHARMAX];
	EQUIPA * equipa;

	/* nome */
	scanf(" %[^:\n]", nome);

	/* se nao existir nenhuma equipa com esse nome no sistema*/
	equipa = procura_equipa_aux(nome, ht);
	if (equipa == NULL)
	{
		printf("%d Equipa inexistente.\n", contador_input);
		return;
	}
	printf("%d %s %d\n", contador_input, equipa->nome, equipa->jogos_ganhos);
}


/* r - Apaga um jogo dado o nome*/
void apaga_jogo(int contador_input, JOGO ** ht_jg, LISTA ** lista){
	char nome[CHARMAX];
	JOGO * jogo;

	/* nome */
	scanf(" %[^:\n]", nome);

	/* se nao existir nenhum jogo com esse nome no sistema*/
	jogo = procura_jogo_aux(nome, ht_jg);
	if (jogo == NULL)
	{
		printf("%d Jogo inexistente.\n", contador_input);
		return;
	}
	/* altera os jogos ganhos das equipas*/
	if (jogo->score1 > jogo->score2)
		jogo->equipa1->jogos_ganhos--;
	if (jogo->score1 < jogo->score2)
		jogo->equipa2->jogos_ganhos--;

	/* apagar o jogo da lista ligada */
	apaga_jg_lista(lista, jogo);
	/* apagar o jogo da hashtable */
	apaga_jg_ht(ht_jg, jogo);
	
}


/* s - Altera o score de um jogo dado o nome*/
void altera_score(int contador_input, JOGO ** ht_jg){
	JOGO * jogo;
	char nome[CHARMAX];
	int score1, score2;

	/* nome:score1:score2 */
	scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);

	/* se nao existir nenhum jogo com esse nome no sistema */
	jogo = procura_jogo_aux(nome, ht_jg);
	if (jogo == NULL)
	{
		printf("%d Jogo inexistente.\n", contador_input);
		return;
	}
	/* muda numero de jogos ganho de cada equipa */
	if (jogo->score1 > jogo->score2) /* se antes a eq vencedora era a 1*/
	{
		if (score1 == score2) /*passa a empate*/
			jogo->equipa1->jogos_ganhos--;
		else if (score1 < score2) /*passa a ser a 2*/
		{
			jogo->equipa1->jogos_ganhos--;
			jogo->equipa2->jogos_ganhos++;
		}
	}
	else if (jogo->score1 < jogo->score2) /*se antes a eq vencedora era a 2*/
	{
		if (score1 == score2) /*passa a empate*/
			jogo->equipa2->jogos_ganhos--;
		else if (score1 > score2) /*se passa a ser a 1*/
		{
			jogo->equipa1->jogos_ganhos++;
			jogo->equipa2->jogos_ganhos--;
		}
	}
	else if (jogo->score1 == jogo->score2) /*se antes estavam empatadas*/
	{
		if (score1 > score2) /*a 1 ganha */
			jogo->equipa1->jogos_ganhos++;
		else if (score1 < score2) /*a 2 ganha */
			jogo->equipa2->jogos_ganhos++;
	}
	/* muda o score do jogo */
	jogo->score1 = score1;
	jogo->score2 = score2;
}


/* g - Encontra as equipas que venceram mais jogos e lista por ordem de nome*/
void top_equipas(int contador_input, LISTA_EQ ** lista){
	int mais_jg_ganhos = 0;
	LISTA_EQ * node = * lista;

	if (*lista == NULL)
		return;

	while (node != NULL)
	{
		if (node->equipa->jogos_ganhos > mais_jg_ganhos)
			mais_jg_ganhos = node->equipa->jogos_ganhos;
		node = node->next;
	}

	printf("%d Melhores %d\n", contador_input, mais_jg_ganhos);
	node = * lista;
	while (node != NULL)
	{
		if (node->equipa->jogos_ganhos == mais_jg_ganhos)
			printf("%d * %s\n", contador_input, node->equipa->nome);
		node = node->next;
	}
}


/* x - Da free a toda a memoria alocada.*/
void liberta_memoria(EQUIPA ** ht_eq, JOGO ** ht_jg, LISTA ** lista_jg, LISTA_EQ ** lista_eq){

	destroi_lista_eq(lista_eq);

	destroi_lista_jg(lista_jg);

	destroi_ht_eq(ht_eq);

	destroi_ht_jg(ht_jg);

	free(ht_eq);
	free(ht_jg);

	/* equipas: */
	/* free nomes (char*)*/
	/* free a ht_eq*/

	/* jogos:*/
	/* free nomes (char *) (as equipas ja estao)*/
	/* free a ht_jg*/

	/* lista ligada:*/
	/* free aos nodes (os jogos ja estao)*/
}

/* Fim */
