#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista_ligada_nomes.h"



Lista **inicializa_lista(Lista **lista){

	/*-----------------------------------------------------
	INICIALIZA OS AS DUAS LISTAS DE NOMES (EQUIPAS E JOGOS)
	-----------------------------------------------------*/

	lista = malloc(sizeof(Lista*));
	lista_nomes_jogos(lista) = NULL;
	return lista;
}


Lista *cria_elemento(char *nome){

	/*---------------------------------------
	CRIA UM NOVO ELEMENTO PARA A LISTA LIGADA
	---------------------------------------*/

	Lista *x = malloc(sizeof(Lista));
	/* Aloca memoria para o nome do elemento. */
	nome_lista(x) = malloc(sizeof(char)*(strlen(nome)+1));
	/* Copia nome para a memoria alocada. */
	strcpy(nome_lista(x), nome);
	proximo_elemento(x) = NULL;
	elemento_anterior(x) = NULL;

	return x;
}


void adiciona_elemento(Lista **lista, Lista *el, Lista **ultimo_jogo){

	/*---------------------------------------
	ADICIONA NOVO NOME DE JOGO A LISTA LIAGDA
	---------------------------------------*/

	Lista *prev;

	/* Caso a lista seja vazia, mete como 1 elemento. */
	if (lista_nomes_jogos(lista) == NULL){
		lista_nomes_jogos(lista) = el;
		ultimo_jogo[0] = el;

	}

	/* Adiciona elemento em ultimo lugar. */
	else{
		prev = ultimo_jogo[0];
		proximo_elemento(prev) = el;
		elemento_anterior(el) = prev;
		ultimo_jogo[0] = el;
	}
}



Lista **remove_el(Lista **lista, Lista **ultimo_jogo, char *nome){

	/*---------------------------------
	REMOVE NOME DE JOGO DA LISTA LIGADA
	---------------------------------*/

	Lista *x, *prev;

	for(x = lista_nomes_jogos(lista), prev = NULL; x != NULL; prev = x, x = proximo_elemento(x)){
		/* Encontra o nome do jogo. */
		if(strcmp(x->nome, nome) == 0){
			/* Se for o primeiro elemento. */
			if(x == lista_nomes_jogos(lista)){
				lista_nomes_jogos(lista) = proximo_elemento(x);
				if ( proximo_elemento(x) == NULL)
					ultimo_jogo[0] = NULL;
			
			}
			/* ELimina o elemento. */
			else{
				proximo_elemento(prev) = proximo_elemento(x);

				/* Unico caso em que altera o ponteiro previous 
				(do ponteiro seguinte) ao eliminar nome de jogo. */
				if ( proximo_elemento(x) != NULL){
					elemento_anterior(proximo_elemento(x)) = prev;
				}
				else{
					ultimo_jogo[0] = prev;
				}

			}
			free_el(x);
			break;
		}

	}
	return ultimo_jogo;
}



void free_el(Lista *head){

	/*---------------------------------------------
	LIBERTA A MEMORIA ALOCADA PARA A LISTA DE JOGOS
	---------------------------------------------*/

	free(nome_lista(head));
	free(head);
}