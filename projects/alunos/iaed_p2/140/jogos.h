#ifndef JOGOS_H
#define JOGOS_H

#include "equipas.h"

/* estrutura par, e um par composto por um int pontos e uma equipa equipa  */
typedef struct par {
  int pontos;
  Equipa equipa;
} *Par;

/* estrutura jogo e um ponteiro para um ponteiro de chars nome, dois pares
   e um int ordem de insercao */
typedef struct jogo {
  char* nome;
  int ordem;
  Par e1;
  Par e2;
} *Jogo;

/* estrutura jnode, e um ponteiro para um jogo e um ponteiro para a proxima jnode */
typedef struct jnode {
  Jogo jogo;
  struct jnode* next;
} *jlink;


Jogo newJogo(char* nome, char* e1, char* e2, int s1, int s2,ulong* ordem, link* hashEquipas);
Par newPar(char* equipa, int score, link* hashEquipas);
jlink JinsertBegin(jlink head, Jogo jogo);
Jogo JsearchList(jlink head, char* nome);
jlink removeJogo(jlink head, char* nome);

jlink* JhashInit();
Jogo JhashSearch(jlink *heads, char* nome);
jlink* JhashInsert(jlink *heads, Jogo jogo);
jlink* JhashDelete(jlink* heads, char* nome);

Jogo* listaOrdenada(jlink* hashJogos, ulong* size);
int Jcmp(const void* a, const void* b);

void freeJogo(Jogo jogo);
void freeJNode(jlink link);
void freeJList(jlink node);
void JfreeHash(jlink* head);

#endif
