#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "lista_equipas.h"

LstEqs* novaListaEqs(){
	LstEqs* lst = can_fail_malloc(sizeof(LstEqs));
	lst->head = NULL;
	lst->n_eqs = 0;

	return lst;
}

NodeEq* novoNodeEq(Equipa eq){
	NodeEq* t = can_fail_malloc(sizeof(NodeEq));

	t->equipa = eq;
	t->seguinte = NULL;

	return t;
}

void pushEq(Equipa eq, LstEqs* lst){
	NodeEq* t = novoNodeEq(eq);

	t->seguinte = lst->head;
	lst->head = t;
	lst->n_eqs++;
}

void popEq(LstEqs* lst){
	NodeEq* t = lst->head;

	lst->head = lst->head->seguinte;
	lst->n_eqs--;

	destroiEquipa(t->equipa);
	free(t);
}

Equipa* procuraEq(LstEqs* lst, char* nome){
	NodeEq* t = lst->head;

	while(t)
		if(strcmp(t->equipa.nome, nome) == 0)	return &(t->equipa);
		else	t = t->seguinte;
		
	return NULL;
}

Equipa* copiaLstEq(LstEqs* lst){
	int i = 0;
	NodeEq* t = lst->head;
	Equipa* arr = can_fail_malloc(lst->n_eqs * sizeof(Equipa));

	for(i = 0; t; t = t->seguinte)
		arr[i++] = t->equipa;

	return arr;
}

void destroiLstEq(LstEqs* lst){
	if(lst)
		while(lst->head)
			popEq(lst);
	
	free(lst);
}