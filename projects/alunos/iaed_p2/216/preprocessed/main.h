#ifndef MAIN_H
#define MAIN_H

#define MAXC 1024
#define T_SIZE 1999
#include "struct.h"
#include "add.h"
#include "list.h"
#include "search.h"
#include "remove.h"
#include "change.h"
#include "champs.h"

hashTable games[T_SIZE];
hashTable teams[T_SIZE];
int counter;

hashTable *startHash(hashTable *hash);
list *startList();
int getHashKey(char nome[MAXC]);
hashNode *getNodeGames(char n_name[MAXC]);
hashNode *getNodeTeams(char n_name[MAXC]);
void deleteList(list *ls, int flag);

#endif