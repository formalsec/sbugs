#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "equipas_hashtable.h" /* contem a funcao hash */
#include "jogos.h"
#include "jogos_hashtable.h"


/* cria dinamicamente uma hash table de jogos */
jogo** inicia_hashtable_jogos(int *max, int *num_elem) {
	jogo **nova_hastable;
	int i;
	int M = 2*(*max);
	*num_elem = 0;
	nova_hastable = can_fail_malloc(M*(sizeof(jogo*)));
	for (i = 0; i < M; i++) {
		nova_hastable[i] = NULL;
	}
	return nova_hastable;
}


/* insere dinamicamente um jogo na hash table,
se esta chegar a 50% da carga, e redimensionada */
jogo* insere_jogo(jogo *novo_jogo, int *pt_max_ht_jogos, jogo **hashtable_jogos, 
				  int *pt_num_elem, lista_jogos *lst_jogos) {
	int i = hash(novo_jogo->nome, *pt_max_ht_jogos);
	while (hashtable_jogos[i] != NULL) {
		if (strcmp(hashtable_jogos[i]->nome, novo_jogo->nome) == 0) {
			return NULL; 	/* ja existe um jogo que este nome inserido, retorna erro */
		}
		i = (i+1) % *pt_max_ht_jogos;
	}
	hashtable_jogos[i] = novo_jogo;
	novo_jogo->anterior = lst_jogos->jogo_final; /* atualiza os ponteiros para os jogos */
	novo_jogo->seguinte = NULL;
	if (lst_jogos->jogo_final != NULL) {
		lst_jogos->jogo_final->seguinte = novo_jogo;
	}
	else {
		lst_jogos->jogo_inicial = novo_jogo;
	}
	lst_jogos->jogo_final = novo_jogo;
	if ((*pt_num_elem)++ > (*pt_max_ht_jogos)/2) { /* se chegar a 1/2 da carga, e redimensionada */
		hashtable_jogos = expande_hashtable_jogos(hashtable_jogos, pt_max_ht_jogos, 
												  pt_num_elem, lst_jogos);
	}
	
	return hashtable_jogos[i]; /* inseriu o elemento com sucesso */
}


/* liberta toda a a memoria alocada pela hash table de jogos */
void liberta_hashtable_jogos(jogo **ht_jogos, int max_ht_jogos) {
	int i;
	for (i = 0; i < max_ht_jogos; i++) {
		if (ht_jogos[i] != NULL) {
			liberta_jogo(ht_jogos[i]);
		}
	}
	free(ht_jogos);
}


/* redimensiona a hash table de jogos para o dobro do tamanho atual, faz
rehashing dos valores ja inseridos */
jogo** expande_hashtable_jogos(jogo **ht_jogos, int *pt_max_ht_jogos, int *pt_num_elem, lista_jogos *lst_jogos) {
	int i;
	jogo **hastable_antiga = ht_jogos;
	*pt_max_ht_jogos = 2*(*pt_max_ht_jogos); /* duplica a dimensao da hash table */
	ht_jogos = inicia_hashtable_jogos(pt_max_ht_jogos, pt_num_elem);
	for (i = 0; i < (*pt_max_ht_jogos/2); i++) {
		if (hastable_antiga[i] != NULL) { /* reinsere os valores ja inseridos na nova hash table */
			insere_jogo(hastable_antiga[i], pt_max_ht_jogos, ht_jogos, pt_num_elem, lst_jogos);
		}
	}
	free(hastable_antiga);
	return ht_jogos;
}


/* procura na hash table um jogo dado */
jogo* procura_jogo_ht(jogo **ht_jogos, char nome_jogo_procurar[], int max_ht_jogos){
	int i = hash(nome_jogo_procurar, max_ht_jogos);
	while (ht_jogos[i] != NULL) {
		if (strcmp(ht_jogos[i]->nome, nome_jogo_procurar) == 0) {
			return ht_jogos[i];
		}
		else {
			i = (i+1) % max_ht_jogos;
		}
	}
	return NULL; /* nao encontrou o jogo na hash table, assinala o erro */
}


/* encontra e liberta um jogo, depois de removido, os jogos seguintes sao reinseridos, ate ser 
encontrada uma posicao NULL */
int remove_jogo_ht(char nome_jogo_eliminar[], jogo **ht_jogos, int *pt_max_ht_jogos, 
				   int *pt_num_elem_ht_jogos, lista_jogos *lst_jogos) {
	int j, i = hash(nome_jogo_eliminar, *pt_max_ht_jogos);
	while (ht_jogos[i] != NULL) {
		if (strcmp(ht_jogos[i]->nome, nome_jogo_eliminar) == 0) {
			break;
		}
		else {
			i = (i+1) % *pt_max_ht_jogos;
		}
	}	
	if (ht_jogos[i] == NULL) {
		return -1;  /* nao encontrou o jogo na hash table, assinala o erro */
	}
	altera_resultados_jogo(ht_jogos[i], 0, 0); /* jogo removido, ninguem ganhou (0-0) e atualiza */
	if (ht_jogos[i]->anterior == NULL) {	   /* resultado nas equipas */
		lst_jogos->jogo_inicial = ht_jogos[i]->seguinte;
	}
	else {
		ht_jogos[i]->anterior->seguinte = ht_jogos[i]->seguinte;
	}
	if (ht_jogos[i]->seguinte == NULL) {
		lst_jogos->jogo_final = ht_jogos[i]->anterior;
	}
	else {
		ht_jogos[i]->seguinte->anterior = ht_jogos[i]->anterior;
	}
	liberta_jogo(ht_jogos[i]);
	ht_jogos[i] = NULL;
	(*pt_num_elem_ht_jogos)--; /* atualiza numero de jogos na hash table */
	for (j = (i+1) % (*pt_max_ht_jogos); ht_jogos[j] != NULL; j = (j+1) % (*pt_max_ht_jogos), (*pt_num_elem_ht_jogos)--) {
		jogo *aux_remove_jogo = ht_jogos[j];
		ht_jogos[j] = NULL;
		insere_jogo(aux_remove_jogo, pt_max_ht_jogos, ht_jogos, pt_num_elem_ht_jogos, lst_jogos);
	}	/* reinserem-se os jogos seguintes, ate ser encontrada uma posicao NULL */
		return 0;  /* removeu o elemento com sucesso */
}

