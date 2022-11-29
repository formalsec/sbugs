#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipas.h"


/*..........................................................................................................................................................*/
/*|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.*/
/*..........................................................................................................................................................*/
/*|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.| FUNCOES |.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.*/
/*..........................................................................................................................................................*/
/*|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.*/
/*..........................................................................................................................................................*/


/* ESTA FUNCAO FAZ O HASHING DAS CHAVES, NESTE CASO, DOS NOMES DAS EQUIPAS/JOGOS */
unsigned int hash(const char *v){
    
    int h, a = 31415, b = 27183;
    
    for (h = 0; *v != '\0'; v++, a = a*b % (TAM_TABELA-1))
        h = (a*h + *v) % TAM_TABELA;
    
    return h;
}

/* ESTA FUNCAO CRIA A HASHTABLE COM TODAS AS ENTRADAS VAZIAS */
ht_equipas *ht_init_equipas(void){

	int i = 0;

	/* aloca a tabela */
	ht_equipas *hashtable = can_fail_malloc(sizeof(ht_equipas));
	/* aloca as entradas das tabelas com o tamanho de uma equipa */
	hashtable->entries = can_fail_malloc(sizeof(link_equipa*) * TAM_TABELA);
	/* inicializa todas a entradas vazias */
	for(; i < TAM_TABELA; ++i){
		hashtable->entries[i] = NULL;
	}

	return hashtable;
}

void ht_pair_equipas(ht_equipas *hashtable_equipas, const char *nome){
	
	unsigned int slot = hash(nome);

	/* aloca as informacoes da equipa */
	link_equipa *x = can_fail_malloc(sizeof(link_equipa));
	x->nome = can_fail_malloc(sizeof(char) * (strlen(nome) + 1));
	
	/* guarda o nome e o numero de vitorias */
	strcpy(x->nome, nome);
	x->nr_vitorias = 0;

	x->next = hashtable_equipas->entries[slot];
	hashtable_equipas->entries[slot] = x;
}

/* ESTA FUNCAO INSERE UMA EQUIPA NA HASHTABLE */
void ht_set_equipas(ht_equipas *hashtable, const char *nome, int NL){

	link_equipa *equipa = st_search(hashtable, nome);

	/* se a equipa ja existir da erro */
	if(equipa != NULL){
		printf("%d Equipa existente.\n",NL);
		return;
	}
	/* aloca a equipa */
	ht_pair_equipas(hashtable,nome);

}

/* ESTA FUNCAO DEVOLVE A EQUIPA SE FOR ENCONTRADA CASO NAO SEJA NAO DEVOLVE NADA */
link_equipa *st_search(ht_equipas *hashtable, const char *nome){

	unsigned int slot = hash(nome);
	link_equipa *x = hashtable->entries[slot];

	/* percorre todas as equipas */
	while(x != NULL){
		/* se encontrar a equipa devolve-a */
		if(strcmp(x->nome, nome) == 0)
			return x;
		x = x->next;
	}
	/* caso contrario devolve vazio */
	return NULL;
}

/* ESTA FUNCAO IMPRIME OS RESULTADOS CONSOANTE O QUE A FUNCAO ST_SEARCH DEVOLVE */
void ht_search_equipas(ht_equipas *hashtable, const char *nome, int NL){

	link_equipa *equipa = st_search(hashtable, nome);

	/* se devolver vazio, quer dizer que nao existe e por isso imprime erro */
	if(equipa == NULL){
    	printf("%d Equipa inexistente.\n",NL);
		return;
	}
	/* caso contrario imprime normalmente */
	printf("%d %s %d\n",NL,equipa->nome,equipa->nr_vitorias);
}