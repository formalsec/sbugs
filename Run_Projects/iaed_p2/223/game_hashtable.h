#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"
#include "game_lists.h"
#include "team_lists.h"

#ifndef GAME_HASHTABLE_H
#define GAME_HASHTABLE_H

int hash(char *s, int m);

void Ginit(int m);
void Ginsert(Jogo jogo);
void Gdelete(Jogo jogo);
Jogo Gsearch(char *v);
int haJogo(char *v);
void Gclear();
#endif