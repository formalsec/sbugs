#include "hash.h"

/* Hash table de pilhas de equipas e jogos */
int f_hash(char *des){
	int res = 0, a = 53;
	for (; *des != '\0'; des++)
		res = (a*res + *des) % DIVISOR;
	return res;
}

/* Funcao responsavel pela inicializacao da hash table das equipas */
node_eq* init_eq(){
	int i;
	node_eq *table_eq;
	table_eq = malloc(sizeof(node_eq) * DIVISOR);
	for (i = 0; i < DIVISOR; i++)
		table_eq[i] = NULL;
	return table_eq;
}

/* Funcao responsavel pela inicializacao da hash table dos jogos */
node_jg* init_jg(){
	int i;
	node_jg *table_jg;
	table_jg = malloc(sizeof(node_jg) * DIVISOR);
	for (i = 0; i < DIVISOR; i++)
		table_jg[i] = NULL;
	return table_jg;
}

/* Funcao que inicializa a lista de jogos para o comando l */
link* init_lk(){
	link *nlink;
	nlink = malloc(sizeof(link));
	nlink->head = NULL;
	nlink->tail = NULL;
	return nlink;
}

/* Funcoes que tratam da funcao quicksort */
/* Funcao que troca duas equipas de indice i e j numa lista */
void trc_eq(int i, int j, eq **lista){
	eq *equipa;
	equipa = lista[i];
	lista[i] = lista[j];
	lista[j] = equipa;
}

/* Funcao auxiliar responsavel por fazer a particao da lista de equipas na funcao quicksort */
int div_eq(eq **lista, int e, int d){
	int i = e - 1;
	int j = d;
	eq *equipa = lista[d];
	while (i < j){
		while (strcmp(lista[++i]->des, equipa->des) < 0);
		while (strcmp(equipa->des, lista[--j]->des) < 0)
			if (j == e)
				break;
		if (i < j)
			trc_eq(i, j, lista);
	}
 	trc_eq(i, d, lista);
	return i;
}

/* Funcao auxiliar para o comando g */
void quicksort(eq **lista, int e, int d){
	int i;
	if (d <= e)
		return;
	i = div_eq(lista, e, d);
	quicksort(lista, e, i - 1);
	quicksort(lista, i + 1, d);
}