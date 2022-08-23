#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Team.h"

void swapProd(Team **teamsMostWins, int i, int j);
int quickSortPartitionByTName(Team **teamsMostWins, int l, int h);
void quickSortByTName(Team **teamsMostWins, int l, int h);

#endif