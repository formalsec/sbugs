#ifndef REMOVE_H
#define REMOVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "struct.h"
#include "add.h"
#include "list.h"
#include "search.h"
#include "remove.h"
#include "change.h"
#include "champs.h"

#define MAXC 1024
#define T_SIZE 1999

void rmvWin(list *tms, char name[MAXC]);
void deleteNode(node *del_n, int flag);
void pop(list *ls, node *del, int flag);
void eraseGames(list *ls, char name[MAXC]);
void eraseTeams(list *ls, char name[MAXC]);
void removeGame(list *ls, list *tms);

#endif