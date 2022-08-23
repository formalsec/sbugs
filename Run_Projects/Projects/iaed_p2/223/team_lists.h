#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"

#ifndef TEAM_LISTS_H
#define TEAM_LISTS_H

typedef struct tnode {
	Equipa equipa;
	struct tnode *next;
} *tlink;

tlink TNEW(Equipa equipa);
tlink TinsertBegin(tlink head, Equipa equipa);
tlink TinsertEnd(tlink head, Equipa equipa);
tlink Tlookup(tlink head, char *v);
tlink TremoveItem(tlink head, Equipa equipa, int n);
#endif