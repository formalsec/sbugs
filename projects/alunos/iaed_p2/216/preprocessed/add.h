#ifndef ADD_H
#define ADD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "main.h"
#include "add.h"
#include "list.h"
#include "search.h"
#include "remove.h"
#include "change.h"
#include "champs.h"

#define MAXC 1024
#define T_SIZE 1999

void addWin(list *tms, char name[MAXC]);
void push(int idx, node *n_node, int flag);
void addGame(list *ls, list *tms);
void addTeam(list *ls);

#endif