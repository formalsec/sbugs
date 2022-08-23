#ifndef _estruturas_
#define _estruturas_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1024
#include "estruturas.h"

typedef struct jogo {
  char *nome_jogo;
  char *equipa1;
  char *equipa2;
  int score1;
  int score2;
} *pjogo;

typedef struct equipas{
  char *equipa;
  int vitorias;
} *pequipa;

typedef struct node {
  pequipa equipa;
  pjogo jogo;
  struct node *next;
}*link;


link insertEnd(link* head,pjogo teste);
link insertEnd_equipas(link* head, pequipa teste);
void da_free_st(link* head);
void da_free_ht(link* head_2);
#endif
