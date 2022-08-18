#include "jogos.h"
#include "nodes.h"
#ifndef HASH_H
#define HASH_H
#define DIVISOR 157

int f_hash(char *des);
node_eq* init_eq();
node_jg* init_jg();
link* init_lk();
void trc_eq(int i, int j, eq **lista);
int div_eq(eq **lista, int e, int d);
void quicksort(eq **lista, int e, int d);
#endif