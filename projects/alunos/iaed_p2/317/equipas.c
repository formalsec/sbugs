#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipas.h"

/*-----------------------funcoes hashtable equipas-----------------------*/

/*funcao de dispersao*/
int EH_hash(char *v, int M) {
	int h, a = 31415, b = 27183;
	for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
		h = (a*h + *v) % M;
	return h;
}

/*inicializa a hashtable de equipas colocando cada head a null*/
void inicializa_equipas_hash(EHnode *Ehash) {
	int i;
	for (i = 0; i < HASH_M; i++) 
		Ehash[i] = NULL;
}

/*procura uma equipa na hashtable de equipas*/
Equipa *EHsearch(EHnode *Ehash, char *nome) {
	int i = EH_hash(nome, HASH_M);
	EHnode node;
	/*procurar a equipa na lista ligada que comeca a partir da cabeca selecionada por "EH_hash"*/
	for(node = Ehash[i]; node != NULL; node = node -> next) 
		if (strcmp(node -> equipa -> nome, nome) == 0)
			return node -> equipa;
	return NULL; /*return NULL se a equipa nao foi encontrada*/
}

/*insere uma equipa na hashtable de equipas*/	
void EHinsert(EHnode *Ehash, Equipa *equipa) {
	int i = EH_hash(equipa -> nome, HASH_M);
	EHnode node;
	node = can_fail_malloc(sizeof(struct node_equipa));
	node -> equipa = equipa;
	node -> next = Ehash[i];
	Ehash[i] = node;
}

/*-----------------------funcoes equipas sistema-----------------------*/

void inicializa_equipas_sistema(Equipas_sistema *equipas_sis){
	equipas_sis -> n_max_vitorias = 0;
	equipas_sis -> n_equipas_max = 0;
	equipas_sis -> equipas = can_fail_malloc(sizeof(EHnode));
	*(equipas_sis -> equipas) = NULL;
}

/*insere uma equipa numa lista ligada de equipas*/
void ESinsert(EHnode *equipas, Equipa *equipa) {
	EHnode node;
	node = can_fail_malloc(sizeof(struct node_equipa));
	node -> equipa = equipa;
	node -> next = *equipas;
	*equipas = node;
}

/*-----------------------frees-----------------------*/

void free_equipa(Equipa *equipa){
	free(equipa -> nome);
	free(equipa);
}

void free_equipas_sis(Equipas_sistema *equipas_sis){
	EHnode EHnode_aux, EHtmp;
	for(EHnode_aux = *(equipas_sis -> equipas); EHnode_aux != NULL; ){
		EHtmp = EHnode_aux -> next;
		free(EHnode_aux);
		EHnode_aux = EHtmp;
	}
	free(equipas_sis -> equipas);
	free(equipas_sis);
}
