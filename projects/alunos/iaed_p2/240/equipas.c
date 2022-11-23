#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"




/* Funcao hash */

int hash(char *v){				/* calcula a posicao de uma equipa na hashtable */
	int h, a = 31415, b = 27183;
	for (h = 0; *v != '\0'; v++, a = a*b % (TAMANHO_MAX_HASH - 1))
		h = (a*h + *v) % TAMANHO_MAX_HASH;
	return h;
}



node_htable_equipas ** init_hash_equipas(){		/* inicia a hashtable */
	int i;
	node_htable_equipas ** hashtable_equipas;
	hashtable_equipas = can_fail_malloc(sizeof(node_htable_equipas) * TAMANHO_MAX_HASH);
	for (i = 0; i < TAMANHO_MAX_HASH; i++)
		hashtable_equipas[i] = NULL;
	return hashtable_equipas;
}



lista_ligada_equipas * init_lista_ligada_e(){		/* inicia a lista ligada */
	lista_ligada_equipas * lista_ligada;
	lista_ligada = can_fail_malloc(sizeof(lista_ligada_equipas));
	lista_ligada->equipa = can_fail_malloc(sizeof(equipa*));
	lista_ligada = NULL;
	return lista_ligada;
}



/* cria uma equipa, devolve um ponteiro para a mesma */

equipa *cria_equipa(char *nome_equipa){

	equipa *equipa_new = can_fail_malloc(sizeof(equipa));

	equipa_new->nome_equipa = can_fail_malloc (sizeof(char*) * (strlen(nome_equipa)+1));
	equipa_new->jogos_ganhos = 0;
	strcpy(equipa_new->nome_equipa, nome_equipa);

	return equipa_new;
}



/* adiciona a equipa a um node para ser inserida na hash table */

node_htable_equipas *adiciona_a_lista_equipas(node_htable_equipas *pt_lista, equipa *equipa){
	node_htable_equipas *new = can_fail_malloc(sizeof(node_htable_equipas));
	new->equipa = equipa;
	new->next = pt_lista;

	return new;
}



/* adiciona a equipa a uma lista ligada com as equipas ordenadas por ordem alfabetica */

lista_ligada_equipas ** adiciona_a_lista_ligada_e(equipa * equipa_new,
lista_ligada_equipas ** lista_ligada){

	lista_ligada_equipas * new_node;
	lista_ligada_equipas * node_aux;
	lista_ligada_equipas * ultimo = *lista_ligada;

	new_node = can_fail_malloc(sizeof(lista_ligada_equipas));
	new_node->equipa = equipa_new;
	new_node->next = NULL;

	if(*lista_ligada == NULL){
		*lista_ligada = new_node;
		return lista_ligada;
	}

	/* caso a equipa seja mais pequena que a primeira */
	if(strcmp(ultimo->equipa->nome_equipa, equipa_new->nome_equipa) > 0)
	{
		new_node->next = ultimo;
		*lista_ligada = new_node;
		return lista_ligada;
	}

	/* caso so exista uma equipa e nao tenha entrado no if anterior */
	if(ultimo->next == NULL){
		ultimo->next = new_node;
		return lista_ligada;
	}

	/* percorre a lista ate encontrar uma equipa que seja maior do que a dada 
	e quando o encontra coloca-se na posicao correta */
	while(ultimo->next != NULL && strcmp(ultimo->next->equipa->nome_equipa,
	equipa_new->nome_equipa) < 0){
		ultimo = ultimo->next;
	}
	node_aux = ultimo->next;
	ultimo->next = new_node;
	new_node->next = node_aux;
	return lista_ligada;
}



/* devolve um ponteiro para uma equipa, caso exista */

equipa * procura_equipa_aux(char *nome_equipa, node_htable_equipas **entrada_hash){
	long hash_index;
	node_htable_equipas *lista_equipas;

	hash_index = hash(nome_equipa);
	lista_equipas = entrada_hash[hash_index];
	while(lista_equipas != NULL && strcmp(lista_equipas->equipa->nome_equipa, nome_equipa) != 0){
		lista_equipas = lista_equipas->next;
	}
	if(lista_equipas == NULL)
		return NULL;
	return lista_equipas->equipa;
}


/* fim equipas.c */
