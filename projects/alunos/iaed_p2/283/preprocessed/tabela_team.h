#ifndef __TABELATEAM__
#define __TABELATEAM__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "team.h"
#define SIZE_STRING 1024
#define HASH_SIZE 1551


/*Estrutua de equipas link reprsenta uma lista ligada dentro da hash table de equipas */

typedef struct link_t{
	Team *team;
	struct link_t *next;
} *link_t;

void liberta_link_t(link_t head);

link_t *init_t();

Team *encontra_t(link_t *table, char team[]);

void introduz_table_t(link_t *table,Team *new_team);

void liberta_table_t(link_t *table);

void Remove_table_t(link_t *table,Team *t);

int ve_maior(link_t *table);

int teams_maiores(link_t *table,char **vec,int maior);

void merge(char **aux,char**aux_1,int l,int m,int r);

void merge_principal(char **aux,char**aux_1,int l, int r);

#endif