#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"



node_htable_jogos ** init_hash_jogos(){		/* inicia a hashtable */
	int i;
	node_htable_jogos ** hashtable_jogos;
	hashtable_jogos = can_fail_malloc(sizeof(node_htable_jogos) * TAMANHO_MAX_HASH);
	for (i = 0; i < TAMANHO_MAX_HASH; i++)
		hashtable_jogos[i] = NULL;
	return hashtable_jogos;
}

lista_ligada_jogos * init_lista_ligada_j(){		/* inicia a lista ligada */
	lista_ligada_jogos * lista_ligada;
	lista_ligada = can_fail_malloc(sizeof(lista_ligada_jogos));
	lista_ligada->jogo = can_fail_malloc(sizeof(jogo*));
	lista_ligada = NULL;
	return lista_ligada;
}



/* cria um jogo e retorna um ponteiro para o mesmo */

jogo * cria_jogo(char *nome_jogo, char *nome_equipa1, char *nome_equipa2,
 int score1, int score2, node_htable_equipas **entrada_hash_equipas){
	jogo *jogo_new = can_fail_malloc(sizeof(jogo));

	jogo_new->nome_jogo = can_fail_malloc(sizeof(char*) * (strlen(nome_jogo)+1));
	strcpy(jogo_new->nome_jogo, nome_jogo);

	jogo_new->equipa1 = procura_equipa_aux(nome_equipa1, entrada_hash_equipas);
	jogo_new->equipa2 = procura_equipa_aux(nome_equipa2, entrada_hash_equipas);

	jogo_new->score1 = score1;
	jogo_new->score2 = score2;

	if(score1 > score2)						/* caso o score da equipa 1 seja maior ela ganha */
		jogo_new->equipa1->jogos_ganhos++;
	if(score1 < score2)
		jogo_new->equipa2->jogos_ganhos++;
	return jogo_new;						/* em caso de empate ninguem ganha */
}



/* adiciona o jogo a um node para ser inserido na hash table */

node_htable_jogos * adiciona_ao_node_jogos(node_htable_jogos *pt_lista, jogo *jogo_new){
	node_htable_jogos *new = can_fail_malloc(sizeof(node_htable_jogos));
	new->jogo = jogo_new;
	new->next = pt_lista;

	return new;
}



/* adiciona o jogo a lista ligada */

lista_ligada_jogos ** adiciona_a_lista_ligada_j(jogo * jogo_new, 
lista_ligada_jogos ** lista_ligada){
	lista_ligada_jogos * new_node;
	lista_ligada_jogos * node_aux = *lista_ligada;
	new_node = can_fail_malloc(sizeof(lista_ligada_jogos));
	new_node->jogo = jogo_new;
	new_node->next = NULL;

	if(*lista_ligada == NULL){
		*lista_ligada = new_node;
		return lista_ligada;
	}
	if (node_aux->next == NULL){
		new_node->next = node_aux;
		*lista_ligada = new_node;
		return lista_ligada;
	}
	new_node->next = node_aux;
	*lista_ligada = new_node;
	return lista_ligada;
}



/* devolve um ponteiro para uma equipa, caso exista */

jogo * procura_jogo_aux(char *nome_jogo, node_htable_jogos **entrada_hash){
	node_htable_jogos * lista_jogos;
	long hash_index;

	hash_index = hash(nome_jogo);

	lista_jogos = entrada_hash[hash_index];
	while(lista_jogos != NULL && strcmp(lista_jogos->jogo->nome_jogo, nome_jogo) != 0){
		lista_jogos = lista_jogos->next;
	}
	if(lista_jogos == NULL)
		return NULL;
	return lista_jogos->jogo;
}



/* apaga o jogo da hashtable */

void apaga_jogo_hashtable(char * nome_jogo, node_htable_jogos ** entrada_hash_jogos){
	int hash_index;
	node_htable_jogos * node_hash;
	node_htable_jogos * antes;

	hash_index = hash(nome_jogo);
	node_hash = entrada_hash_jogos[hash_index];

	if (node_hash != NULL && strcmp(node_hash->jogo->nome_jogo, nome_jogo) == 0)
	{
		entrada_hash_jogos[hash_index] = entrada_hash_jogos[hash_index]->next;
		free(node_hash->jogo->nome_jogo);
		free(node_hash->jogo);
		free(node_hash);
		return;
	}

	while(node_hash != NULL && strcmp(node_hash->jogo->nome_jogo, nome_jogo) != 0){
		antes = node_hash;
		node_hash = node_hash->next;
	}

	antes->next = node_hash->next;
	free(node_hash->jogo->nome_jogo);
	free(node_hash->jogo);
	free(node_hash);
}



/* apaga um jogo da lista ligada */

void apaga_jogo_lista_ligada(char * nome_jogo, lista_ligada_jogos ** lista_ligada){
	lista_ligada_jogos * node = *lista_ligada;
	lista_ligada_jogos * node_aux;

	if(node->next == NULL){
		*lista_ligada = NULL;
		free(*lista_ligada);
		return;
	}
	if(strcmp(node->jogo->nome_jogo, nome_jogo) == 0){		/* caso seja o primeiro elemento */
		*lista_ligada = node->next;
		free(node);
		return;
	}
	while(node->next != NULL){
		if(strcmp(node->next->jogo->nome_jogo, nome_jogo) == 0){  /* se encontrarmos o jogo */
			node_aux = node->next;
			node->next = node->next->next;
			free(node_aux);
			return;
		}
		node = node->next;
	}
}


/* fim jogos.c */
