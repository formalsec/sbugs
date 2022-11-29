#ifndef CHAMPS_H
#define CHAMPS_H

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

void swap(char s1[MAXC], char s2[MAXC]);
void bubble(list *aux);
void findChamps(list *tms);

#endif