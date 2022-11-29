#ifndef _hashtable_
#define _hashtable_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1024
#include "hashtable.h"
#include "estruturas.h"

int hash(char* nome_jogo,int* M);
void Stinit(int* M,pjogo* st);
void Stinsert(char* nome_jogo,char* equipa1, char* equipa2, int score1, int score2,int* M,pjogo *st,link* head);
link STdelete(char* nome_jogo,int* M,pjogo *st,link* head);
void reinsere_el(pjogo el, pjogo* st,int* M, char* nome_jogo);
pjogo search(char* nome_jogo,int* M,pjogo* st);
void Htinit (int *L,pequipa* ht);
void Htinsert(char* equipa,int vitorias,int* L,pequipa *ht,link* head_2);
pequipa search_equipa(char* equipa,int* L,pequipa* ht);

#endif
