#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "tabela_equipa.h"

int hashTabEq(char* s){	/* Copiada dos slides */
	int h = 0, a = 127;

	for(; *s != '\0'; s++)	h = (a*h + *s) % DIM_TAB_EQ;

	return h;
}

TabEquipas* novaTabEq(){
	int i;
	TabEquipas* tab = can_fail_malloc(sizeof(TabEquipas));
	tab->lst = can_fail_malloc(DIM_TAB_EQ * sizeof(LstEqs*));
	tab->n_eqs = 0;

	for(i = 0; i < DIM_TAB_EQ; i++)	tab->lst[i] = novaListaEqs();

	return tab;
}

void pushTabEq(TabEquipas* tab, Equipa eq){
	int h;

	h = hashTabEq(eq.nome);
	pushEq(eq, tab->lst[h]);

	tab->n_eqs++;
}

Equipa* procuraTabEq(TabEquipas* tab, char* nome){
	int h;
	Equipa* e;

	h = hashTabEq(nome);
	e = procuraEq(tab->lst[h], nome);

	return e;
}

Equipa* copiaTabEq(TabEquipas* tab){
	int i, j, k = 0;
	Equipa** arr = can_fail_malloc(DIM_TAB_EQ * sizeof(Equipa*));
	Equipa* res = can_fail_malloc(tab->n_eqs * sizeof(Equipa));

	for(i = 0; i < DIM_TAB_EQ; i++)	arr[i] = copiaLstEq(tab->lst[i]);

	for(i = 0; i < DIM_TAB_EQ; i++)	/* Copiamos a matriz a um vetor */
		for(j = 0; j < tab->lst[i]->n_eqs; j++)
			res[k++] = arr[i][j];

	
	for(i = 0; i < DIM_TAB_EQ; i++)	free(arr[i]);

	free(arr);

	return res;
}

void destroiTabEq(TabEquipas* tab){
	int i;
	
	for(i = 0; i < DIM_TAB_EQ; i++)	destroiLstEq(tab->lst[i]);

	free(tab->lst);
	free(tab);
}

int comparaEq(const void* a, const void* b){
	Equipa* eqA = (Equipa*) a;
	Equipa* eqB = (Equipa*) b;

	if(eqB->vitorias != eqA->vitorias)	return eqB->vitorias - eqA->vitorias;
	else	return strcmp(eqA->nome, eqB->nome);
}