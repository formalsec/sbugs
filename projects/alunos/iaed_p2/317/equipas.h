#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EQUI_SIS_M 50
#define HASH_M 137

typedef struct {
	char *nome; /*nome da equipa*/
	int jogos_ganhos; /*numero de vitorias*/
} Equipa;

/* node para a hashtable de equipas e para a lista ligada de equipas do sistema*/
typedef struct node_equipa {
	Equipa *equipa; 
	struct node_equipa *next;
} *EHnode;

typedef struct equipas_sistema{
	int n_max_vitorias; /*maior numero de vitorias*/
	int n_equipas_max; /*numero de equipas com mais vitorias*/
	EHnode *equipas;
}Equipas_sistema;

int EH_hash(char *v, int M);
void inicializa_equipas_hash(EHnode *Ehash);
Equipa *EHsearch(EHnode *Ehash, char *nome);
void EHinsert(EHnode *Ehash, Equipa *equipa);
void inicializa_equipas_sistema(Equipas_sistema *equipas_sis);
void ESinsert(EHnode *equipas, Equipa *equipa);
void free_equipa(Equipa *equipa);
void free_equipas_sis(Equipas_sistema *equipas_sis);
