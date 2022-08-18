#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "match.h"

#define SIZE 10151

unsigned int hash(char*);
void STinit();
void STinsert(MATCH);
void STdelete(char*);
MATCH STsearch(char*);
void STdeletetable();

#endif