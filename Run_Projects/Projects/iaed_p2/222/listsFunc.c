#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"

/*#####################################################################*/
/*	FUNCOES RELATIVAS A LISTAS DUPLAMENTE LIGADAS					   */
/*#####################################################################*/

/* Cria a Lista dos Jogos */
listJogo* mkListJogo(){
	listJogo* l = malloc(sizeof(listJogo));
	l->head = l->last = NULL;
	return l;
}

/* Cria a Lista das Equipas */
listEquipa* mkListEquipa(){
	listEquipa* l = malloc(sizeof(listEquipa));
	l->head = l->last = NULL;
	return l;
}

/* Liberta um no da lista dos Jogos */
void freeNodeJogo(nodeJogo* n){
	free(n->nomeJogo);
	free(n->nomeEquipa1);
	free(n->nomeEquipa2);
	free(n);
}

/* Liberta um no da lista das Equipas */
void freeNodeEquipa(nodeEquipa* n){
	free(n->nomeEquipa);
	free(n);
}

/* Liberta a lista inteira dos Jogos */
void freeListJogo(listJogo* l){
	while(l->head){
		nodeJogo* tmp = l->head->next;
		freeNodeJogo(l->head);
		l->head = tmp;
	}
	free(l);
}

/* Liberta a lista inteira das Equipas */
void freeListEquipa(listEquipa* l){
	while(l->head){
		nodeEquipa* tmp = l->head->next;
		freeNodeEquipa(l->head);
		l->head = tmp;
	}
	free(l);
}

/* Remove um no da lista de Jogos */
void removeNodeJogo(listJogo* l, nodeJogo* n){
	if(n->previous == NULL){
		l->head = n->next;
	}else{
		n->previous->next = n->next;
	}
	if(n->next == NULL){
		l->last = n->previous;
	}else{
		n->next->previous = n->previous;
	}
	freeNodeJogo(n);
}

/* Remove um no da lista de Equipas */
void removeNodeEquipa(listEquipa* l, nodeEquipa* n){
	if(n->previous == NULL){
		l->head = n->next;
	}else{
		n->previous->next = n->next;
	}
	if(n->next == NULL){
		l->last = n->previous;
	}else{
		n->next->previous = n->previous;
	}
	freeNodeEquipa(n);
}

/* Adiciona um novo no no fim da lista de Jogos */
void addNodeJogo(listJogo* l, const char* _nomeJogo, const char* _nomeEquipa1, const char* _nomeEquipa2, int _resultado1, int _resultado2){
	nodeJogo* n = malloc(sizeof(nodeJogo));
	n->previous = l->last;
	n->next = NULL;
	n->nomeJogo = malloc(sizeof(char)*(strlen(_nomeJogo)+1));
	strcpy(n->nomeJogo, _nomeJogo);	/* preenche o campo nomeJogo */
	n->nomeEquipa1 = malloc(sizeof(char)*(strlen(_nomeEquipa1)+1));
	strcpy(n->nomeEquipa1, _nomeEquipa1);	/* preenche o campo nomeEquipa1 */
	n->nomeEquipa2 = malloc(sizeof(char)*(strlen(_nomeEquipa2)+1));	
	strcpy(n->nomeEquipa2, _nomeEquipa2);	/* preenche o campo nomeEquipa2 */
	n->resultado1 = _resultado1;	/* preenche o campo resultado1 */
	n->resultado2 = _resultado2;	/* preenche o campo resultado2 */
	if(l->last) l->last->next = n; /* caso a lista ja contenha algum no */
	else l->head = n;		/* caso a lista esteja vazia, e este seja o primeiro no a inserir */ 	
	l->last = n;
}

/* Adiciona um novo no no fim da lista de Equipas */
void addNodeEquipa(listEquipa* l, const char* _nomeEquipa){
	nodeEquipa *n = malloc(sizeof(nodeEquipa));
	n->previous = l->last;
	n->next = NULL;
	n->nomeEquipa = malloc(sizeof(char)*(strlen(_nomeEquipa)+1));
	strcpy(n->nomeEquipa, _nomeEquipa);	/* preenche o campo nomeEquipa */
	n->vitorias = 0;	/* inicializa o numero de vitorias */
	if(l->last) l->last->next = n; /* caso a lista ja contenha algum no */
	else l->head = n;		/* caso a lista esteja vazia, e este seja o primeiro no a inserir */ 	
	l->last = n;
}

/* Procura um no na lista de Jogos */
nodeJogo* searchListJogo(listJogo *lstJogo, char* _nomeJogo){
	nodeJogo *currentNode;
	for(currentNode = lstJogo->head; currentNode != NULL; currentNode = currentNode->next){
		if(strcmp(currentNode->nomeJogo, _nomeJogo) == 0)
			return currentNode;
	}
	return currentNode->next;	/* caso nao haja jogo desejada retorna NULL */
}

/* Procura um no na lista de Equipas */
nodeEquipa* searchListEquipa(listEquipa *lstEquipa, char* _nomeEquipa){
	nodeEquipa *currentNode;
	for(currentNode = lstEquipa->head; currentNode != NULL; currentNode = currentNode->next){
		if(strcmp(currentNode->nomeEquipa, _nomeEquipa) == 0)
			return currentNode;
	}
	return currentNode->next; /* caso nao haja equipa desejada retorna NULL */
}

/* Verifica se o jogo existe */
int existJogo(listJogo *lstJogo, char* _nomeJogo){
	nodeJogo *currentNode;
	for(currentNode = lstJogo->head; currentNode != NULL; currentNode = currentNode->next){
		if(strcmp(currentNode->nomeJogo, _nomeJogo) == 0){
			return 0;
		}	
	}
	return 1;
}

/* Verifica se a equipa existe */
int existEquipa(listEquipa *lstEquipa, char* _nomeEquipa){
	nodeEquipa *currentNode;
	for(currentNode = lstEquipa->head; currentNode != NULL; currentNode = currentNode->next){
		if(strcmp(currentNode->nomeEquipa, _nomeEquipa) == 0)
			return 0;
	}
	return 1;
}

/*#####################################################################*/