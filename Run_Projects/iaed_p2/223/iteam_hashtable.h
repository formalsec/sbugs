#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"
#include "game_lists.h"
#include "team_lists.h"
#include "game_hashtable.h"
#include "team_hashtable.h"

#ifndef ITEAM_HASHTABLE_H
#define ITEAM_HASHTABLE_H

int hashint(int n, int m);

void iTinit(int l);
void iTinsert(Equipa equipa);
void iTdelete(Equipa equipa);
tlink iLastList();
int equipasVazioQ();
void iTclear();
#endif