#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "lista_jogos.h"

LstJogos* novaListaJogos(){
	LstJogos* lst = can_fail_malloc(sizeof(LstJogos));
	lst->head = NULL;
	lst->n_jogos = 0;

	return lst;
}

NodeJogo* novoNodeJogo(Jogo j){
	NodeJogo* t = can_fail_malloc(sizeof(NodeJogo));

	t->jogo = j;
	t->seguinte = NULL;

	return t;
}

void pushJogo(Jogo j, LstJogos* lst){
	NodeJogo* t = novoNodeJogo(j);

	t->seguinte = lst->head;
	lst->head = t;
	lst->n_jogos++;
}

void popJogo(LstJogos* lst){
	NodeJogo* t = lst->head;

	lst->head = lst->head->seguinte;
	lst->n_jogos--;

	destroiJogo(t->jogo);
	free(t);
}

void removeJogo(LstJogos* lst, char* nome){
	NodeJogo* t;
	NodeJogo* anterior;
	t = lst->head;
	anterior = NULL;
	while(t != NULL){
		if(strcmp(t->jogo.nome, nome) == 0){
			if(t == lst->head)	lst->head = t->seguinte;
			else	anterior->seguinte = t->seguinte;

			destroiJogo(t->jogo);
			free(t);
			lst->n_jogos--;
			
			break;
		}
		anterior = t;
		t = t->seguinte;
	}
}

Jogo* procuraLstJogos(LstJogos* lst, char* nome){
	NodeJogo* t = lst->head;
	if(!lst)	return NULL;
	while(t)
		if(strcmp(t->jogo.nome, nome) == 0)	return &(t->jogo);
		else	t = t->seguinte;
		
	return NULL;
}

Jogo* copiaLstJogos(LstJogos* lst){
	int i = 0;
	NodeJogo* t = lst->head;
	Jogo* arr = can_fail_malloc(lst->n_jogos * sizeof(Jogo));

	for(i = 0; t; t = t->seguinte)
		arr[i++] = t->jogo;

	return arr;
}

void destroiLstJogos(LstJogos* lst){
	if(lst)
		while(lst->head)
			popJogo(lst);

	free(lst);
}