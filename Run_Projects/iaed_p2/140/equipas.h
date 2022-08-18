#ifndef EQUIPAS_H
#define EQUIPAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* o tamanho das hash */
#define HASH_SIZE 2269
/* o tamanho maximo das strings */
#define STR_SIZE 1023

typedef unsigned long ulong;

/* estrutura equipa, e um ponteiro para um ponteiro de chars, nome, e
   pora um int, nr de jogos ganhos  */
typedef struct equipa {
  char* nome;
  int ganhos;
} *Equipa;

/* key das hash */
#define Key(x) (x->nome)

/* estrutura node, e um ponteiro para uma equipa e um ponteiro para a proxima node */
typedef struct node{
  Equipa equipa;
  struct node* next;
} *link;

int hash(char* nome);

Equipa newEquipa(char* buffer);
link insertBegin(link head, Equipa equipa);
Equipa searchList(link head, char* nome);

link* EhashInit();
Equipa EhashSearch(link* heads, char* nome);
link* EhashInsert(link* heads, Equipa equipa);

void freeEquipa(Equipa equipa);
void freeEList(link head);
void EfreeHash(link* heads);

Equipa* listaMaioresVitorias(link* hashEquipas,int* maior,int* count);
int cmpfunc(const void* a, const void* b);

#endif
