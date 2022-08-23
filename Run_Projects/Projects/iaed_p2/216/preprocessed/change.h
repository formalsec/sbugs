#ifndef CHANGE_H
#define CHANGE_H

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

void altScore(list *ls, char *name, int n_score1, int n_score2);
void changeScore(list *ls, list *tms);

#endif