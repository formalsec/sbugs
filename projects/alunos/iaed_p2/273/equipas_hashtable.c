#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "equipas_hashtable.h"


/* devolve o indice correspondente a chave passada,
 para a inserir na hash table */
int hash(char *str, int M) {
	int h, a = 31415, b = 27183;
	for (h = 0; *str != '\0'; str++, a = a*b % (M-1)) {
		h = (a*h + *str) % M;
	}
	return h;
}


/* cria dinamicamente uma hash table de equipas */
equipa** inicia_hashtable_equipas(int *max, int *num_elem) {
	equipa **nova_hastable;
	int i;
	int M = 2*(*max);
	*num_elem = 0;	
	nova_hastable = can_fail_malloc(M*(sizeof(equipa*)));
	for (i = 0; i < M; i++) {
		nova_hastable[i] = NULL;
	}
	return nova_hastable;
}


/* insere dinamicamente uma equipa na hash table,
se esta chegar a 50% da carga, e redimensionada */
equipa* insere_equipa(equipa *nova_equipa, int *pt_max_ht_equipas, equipa **hashtable_equipas, int *pt_num_elem) {
	int i = hash(nova_equipa->nome, *pt_max_ht_equipas);
	while (hashtable_equipas[i] != NULL) {
		if (strcmp(hashtable_equipas[i]->nome, nova_equipa->nome) == 0) {
			return NULL; 	/* ja existe uma equipa que este nome inserida, retorna erro */
		}
		i = (i+1) % *pt_max_ht_equipas;
	}
	hashtable_equipas[i] = nova_equipa;
	if ((*pt_num_elem)++ > (*pt_max_ht_equipas)/2) {
		hashtable_equipas = expande_hashtable_equipas(hashtable_equipas, pt_max_ht_equipas, pt_num_elem);
	}
	return hashtable_equipas[i]; /* inseriu o elemento com sucesso */
}


/* liberta toda a a memoria alocada pela hash table de equipas */
void liberta_hashtable_equipas(equipa **ht_equipas, int max_ht_equipas) {
	int i;
	for (i = 0; i < max_ht_equipas; i++) {
		if (ht_equipas[i] != NULL) {
			liberta_equipa(ht_equipas[i]);
		}
	}
	free(ht_equipas);
}


/* redimensiona a hash table de equipas para o dobro do tamanho atual, faz
rehashing dos valores ja inseridos */
equipa** expande_hashtable_equipas(equipa **ht_equipas, int *pt_max_ht_equipas, int *pt_num_elem) {
	int i;
	equipa **hastable_antiga = ht_equipas;
	*pt_max_ht_equipas = 2*(*pt_max_ht_equipas); /* duplica a dimensao da hash table */
	ht_equipas = inicia_hashtable_equipas(pt_max_ht_equipas, pt_num_elem);
	for (i = 0; i < (*pt_max_ht_equipas/2); i++) {
		if (hastable_antiga[i] != NULL) {
			insere_equipa(hastable_antiga[i], pt_max_ht_equipas, ht_equipas, pt_num_elem);
		}
	}
	liberta_hashtable_equipas(hastable_antiga, *pt_max_ht_equipas);
	return ht_equipas;
}


/* procura na hash table uma equipa dada */
equipa* procura_equipa_ht (equipa **ht_equipas, char nome_equipa_procurar[], int max_ht_equipas) {
	int i = hash(nome_equipa_procurar, max_ht_equipas);
	while (ht_equipas[i] != NULL) {
		if (strcmp(ht_equipas[i]->nome, nome_equipa_procurar) == 0) {
			return ht_equipas[i];
		}
		else {
			i = (i+1) % max_ht_equipas;
		}
	}
	return NULL; /* nao encontrou a equipa na hash table */
}