#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "equipa.h"
#include "linkedlist.h"
#include "hash.h"
#include "equipa.h"

#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#define STRINGSIZE 1024

long int NL;

linkJogo listaDeJogos;
linkEquipa  listaDeEquipas;

void a(Hashtable_JOGOS HTj, Hashtable_EQUIPAS HTe);
void A(Hashtable_EQUIPAS HTe);
void l();
void p(Hashtable_JOGOS HTj);
void P(Hashtable_EQUIPAS HTe);
void r(Hashtable_JOGOS HTj, Hashtable_EQUIPAS HTe);
void s(Hashtable_JOGOS HTj, Hashtable_EQUIPAS HTe);
void g();
void x(Hashtable_JOGOS HTj, Hashtable_EQUIPAS HTe);

int cstring_cmp(const void *a, const void *b);

#endif /*COMMANDS_H_INCLUDED*/