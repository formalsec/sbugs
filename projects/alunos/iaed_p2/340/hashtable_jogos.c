#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable_equipas.h"
#include "hashtable_jogos.h"
#include "lista_ligada_nomes.h"




/* inicializa hashtable jogos */
table_j **inicializa_j(table_j **heads, int M){

	/*------------------------
	INICIALIZA HASHTABLE JOGOS
	------------------------*/

	int i;

	heads = can_fail_malloc(M*sizeof(table_j*));
	for (i = 0; i<M; i++){
		heads[i] = NULL;
	}
	return heads;
}





void adiciona_j(table_j **heads, Jogo *jogo, int M){

	/*----------------------------------
	ADICIONA NOVO JOGO A HASHTABLE JOGOS
	----------------------------------*/

	Jogo *x;
	int key = hash(nome_jogo(jogo), M);

	/* Caso hash[key] nao esteja inicializada, inicializa e adiciona jogo. */
	if (heads[key] == NULL){
		heads[key] = can_fail_malloc(sizeof(table_j));
		jogos_hash(heads[key]) = jogo;
	}

	/* Adiciona jogo ao inicio da hash[key]. */
	else{
		x = jogos_hash(heads[key]); 
		jogos_hash(heads[key]) = jogo;
		proximo_j(jogo) = x;
	}
	
}



Jogo *encontra_j(Jogo *head, char *nome){

	/*------------------------------------
	ENCONTRA JOGO NA LISTA LIGADA DE JOGOS
	------------------------------------*/

	Jogo *jogo;

	/* Percorre lista de jogos. */
	for (jogo = head ; (jogo != NULL); jogo = proximo_j(jogo)){
		if(strcmp(nome_jogo(jogo), nome) == 0){
			return jogo;
		}
	}
	return NULL;
}





Jogo *procura_jogo_hash(table_j **heads, Chave_j nome, int M){

	/*-------------------------------------------
	PROCURA JOGO NA HASHTABLE DADA A CHAVE (NOME)
	-------------------------------------------*/

	Jogo *x;
	int key = hash(nome ,M);

	/* Caso hash[key] nao estaja vazia. */
	if (heads[key] != NULL){
		/* x = lista de jogos de hash[key]. */
		x = jogos_hash(heads[key]);
		if((x = encontra_j(x, nome)) == NULL)
			return NULL;
		else
			return x;
	}
	return NULL;
}



int remove_j(table_j **heads, Chave_j nome, int M){

	/*----------------------------
	REMOVE JOGO DA HASHTABLE JOGOS
	----------------------------*/

	Jogo *x, *prev;
	int key = hash(nome ,M);

	/* Verifica se o jogo pertence a hashtable. */
	if ( (x = procura_jogo_hash(heads, nome, M)) != NULL ){
		/* Percorre a lista ligada correspondente a hash[key]. */
		for (x=jogos_hash(heads[key]), prev = NULL; x != NULL; prev = x, x = proximo_j(x)){
			/* Caso encontre o jogo. */
			if (strcmp(nome_jogo(x), nome) == 0){
				/* Caso o jogo seja o 1 elemento da lista ligada. */
				if (x == jogos_hash(heads[key])){
					jogos_hash(heads[key]) = proximo_j(x);

				}
				/* Caso nao seja o 1 elemento da lista ligada. */
				else{
					proximo_j(prev) = proximo_j(x);
				}

				free_jogo(x);
				break;
			}
		}

		return 1;
	}

	return 0;
}





void free_hash_jogos(table_j **heads, int M){

	/*---------------------------------------------------------
	LIBERTA TODA A MEMORIA ALOCADA REFERENTE A HSASHTABLE JOGOS
	---------------------------------------------------------*/

	Jogo *x, *head;
	int i;

	for (i=0; i<M; i++){

		if (heads[i]!= NULL){
			head = jogos_hash(heads[i]);

			for (x = head; head != NULL ; x = head){
				head = proximo_j(head);
				free_jogo(x);
			}
		}

		free(heads[i]);
	}

	free(heads);
}
