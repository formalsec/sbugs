#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable_equipas.h"




int hash(char *nome, int M){

	/*------------------------------------
	FUNCAO DE DISPERSAO RETORNA A HASH KEY
	------------------------------------*/

	int h, a = 313, b = 171;

	for (h = 0; *nome != '\0'; nome++, a= a*b % (M-1)){
		h = (a*h + *nome) % M;
	}
	return h;
}




table_e **inicializa_e(table_e **heads, int M){

	/*--------------------------
	INICIALIZA HASHTABLE EQUIPAS
	--------------------------*/

	int i;
	heads = can_fail_malloc(M*sizeof(table_e*));
	for (i = 0; i<M; i++){
		heads[i] = NULL;
	}
	return heads;
}


/* adiciona nova equipa a hashtable */
void adiciona_e(table_e **heads, Equipa *eq, int M){

	/*------------------------------
	ADICIONA NOVA EQUIPA A HASHTABLE
	------------------------------*/

	Equipa *x;

	/* Chave da hashtable. */
	int key = hash(nome_e(eq), M);

	/* Caso hash[key] nao esteja inicializada, inicializa e adiciona equipa. */
	if (heads[key] == NULL){
		heads[key] = can_fail_malloc(sizeof(table_e));
		equipas_hash(heads[key]) = eq;
	}
	/* Adiciona equipa ao inicio da hash[key]. */
	else{
		x = equipas_hash(heads[key]); 
		equipas_hash(heads[key]) = eq;
		proxima_e(eq) = x;
	}
	
}



Equipa *encontra(Equipa *head, char *nome){

	/*----------------------------------------
	ENCONTRA EQUIPA NA LISTA LIGADA DE EQUIPAS
	----------------------------------------*/

	Equipa *equipa;

	/* Percorre lista de equipas. */
	for (equipa = head ; (equipa != NULL); equipa = proxima_e(equipa)){
		if(strcmp(nome_e(equipa), nome) == 0){
			return equipa;
		}
	}
	return NULL;
}



Equipa *procura_equipa_hash(table_e **heads, Chave nome, int M){

	/*---------------------------------------------
	PROCURA EQUIPA NA HASHTABLE DADA A CHAVE (NOME)
	---------------------------------------------*/

	Equipa *x;
	int key = hash(nome ,M);

	/* Caso hash[key] nao estaja vazia. */
	if (heads[key] != NULL){
		/* x = lista de equipas de hash[key]. */
		x = equipas_hash(heads[key]);
		if((x = encontra(x, nome)) == NULL)
			return NULL;
		else
			return x;
	}
	return NULL;
}


int mais_ganhos(table_e **heads, int size_hash,  int *count){

	/*------------------------------------------------
	DEVOLVE O MAIOR NUMERO DE JOGOS GANHOS E GUARDA EM 
	<count> O NUMERO DE EQUIPAS COM <max> JOGOS GANHOS
	------------------------------------------------*/

	int  max = 0, ganhos, i;
	Equipa *x;

	/* Percorre toda a hash. */
	for (i = 0; i < size_hash ; i++){

		if (heads[i] != NULL){
			/* Percorre todas as equipas da hash[key]. */
			for ( x = equipas_hash(heads[i]) ; x != NULL ; x = proxima_e(x)){

				/* Se numero da jogos ganhos = max aumenta count. */
				if ((ganhos = jogos_ganhos(x) ) == max)
					*(count) = *(count) + 1;

				/* Se ganhos > max, faz reset ao count e atualiza max. */
				else if (ganhos > max){
					max = ganhos;
					*(count) = 1;
				}

			}
		}
	}

	return max;
}




void free_hash_equipas(table_e **heads, int M){

	/*-----------------------------------------------------------
	LIBERTA TODA A MEMORIA ALOCADA REFERENTE A HSASHTABLE EQUIPAS
	-----------------------------------------------------------*/

	Equipa *x, *head;
	int i;

	for (i=0; i<M; i++){

		if (heads[i]!= NULL){
			head = equipas_hash(heads[i]);

			for (x = head; head != NULL ; x = head){
				head = proxima_e(head);
				free_equipa(x);
			}
		}

		free(heads[i]);
	}

	free(heads);
}
