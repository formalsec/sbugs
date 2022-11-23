#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "tabela_jogo.h"

int hashTabJogos(char* s){
	int h = 0, a = 127;

	for(; *s != '\0'; s++)	h = (a*h + *s) % DIM_TAB_JOGOS;

	return h;
}

TabJogos* novaTabJogos(){
	int i;
	TabJogos* tab = can_fail_malloc(sizeof(TabJogos));
	tab->lst = can_fail_malloc(DIM_TAB_JOGOS * sizeof(LstJogos*));
	tab->n_jogos = 0;

	for(i = 0; i < DIM_TAB_JOGOS; i++)	tab->lst[i] = novaListaJogos();

	return tab;
}

void pushTabJogos(TabJogos* tab, Jogo j){
	int h;

	h = hashTabJogos(j.nome);
	pushJogo(j, tab->lst[h]);

	tab->n_jogos++;
}

void popTabJogos(TabJogos* tab, char* nome){
	int h;
	h = hashTabJogos(nome);
	
	removeJogo(tab->lst[h], nome);
	tab->n_jogos--;
}

Jogo* procuraTabJogos(TabJogos* tab, char* nome){
	int h;
	Jogo* j;

	h = hashTabJogos(nome);
	j = procuraLstJogos(tab->lst[h], nome);

	return j;
}

Jogo* copiaTabJogos(TabJogos* tab){
	int i, j, k = 0;
	Jogo** arr = can_fail_malloc(DIM_TAB_JOGOS * sizeof(Jogo*));
	Jogo* res = can_fail_malloc(tab->n_jogos * sizeof(Jogo));

	for(i = 0; i < DIM_TAB_JOGOS; i++)	arr[i] = copiaLstJogos(tab->lst[i]);

	for(i = 0; i < DIM_TAB_JOGOS; i++)
		for(j = 0; j < tab->lst[i]->n_jogos; j++)
			res[k++] = arr[i][j];

	for(i = 0; i < DIM_TAB_JOGOS; i++)	free(arr[i]);
	
	free(arr);

	return res;
}

void destroiTabJogos(TabJogos* tab){
	int i;

	for(i = 0; i < DIM_TAB_JOGOS; i++)	destroiLstJogos(tab->lst[i]);

	free(tab->lst);
	free(tab);
}

int comparaJogos(const void* a, const void* b){
	Jogo* jogoA = (Jogo*) a;
	Jogo* jogoB = (Jogo*) b;

	if(jogoA->id > jogoB->id)	return 1;
	else if(jogoA->id < jogoB->id)	return -1;
	return 0;
}