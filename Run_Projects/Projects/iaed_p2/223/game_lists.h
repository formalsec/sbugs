#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "equipas.h"
#include "jogos.h"

#ifndef GAME_LISTS_H
#define GAME_LISTS_H
typedef struct gnode {
	Jogo jogo;
	struct gnode *next;
} *glink;

glink GNEW(Jogo jogo);
glink GinsertBegin(glink head, Jogo jogo);
glink GinsertEnd(glink head, Jogo jogo);
glink Glookup(glink head, char *v);
glink GremoveItem(glink head, Jogo jogo, int n);
#endif