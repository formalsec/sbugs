#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"
#include "game_lists.h"
#include "team_lists.h"
#include "game_hashtable.h"

#ifndef TEAM_HASHTABLE_H
#define TEAM_HASHTABLE_H

void Tinit(int n);
void Tinsert(Equipa equipa);
void Tdelete(Equipa equipa);
Equipa Tsearch(char *v);
int haEquipa(char *v);
void Tclear();
#endif