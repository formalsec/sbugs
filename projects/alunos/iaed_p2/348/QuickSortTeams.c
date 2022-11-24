#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>

#include "QuickSortTeams.h"

/* Quicksort by Team Name */
void quickSortByTName(Team **teamsMostWins, int l, int h){
	int i;

	if(h <= l)
		return;

	i = quickSortPartitionByTName(teamsMostWins, l, h);

	quickSortByTName(teamsMostWins, l, i-1);
	quickSortByTName(teamsMostWins, i+1, h);
}

int quickSortPartitionByTName(Team **teamsMostWins, int l, int h){
	int i, j;

	i = l - 1;
	j = h;	
	
	while(i < j){
		while(strcmp(teamsMostWins[++i]->name, teamsMostWins[h]->name) < 0);
		while(strcmp(teamsMostWins[--j]->name, teamsMostWins[h]->name) > 0){
			if(j == l)
				break;
		}
		if(i < j){
			swapProd(teamsMostWins, i, j);	
		}
	}

	swapProd(teamsMostWins, i, h);

	return i;
}

/* Swaps products for sort by description function*/
void swapProd(Team **teamsMostWins, int i, int j){
	
	Team *temp;

	temp = teamsMostWins[i];
	teamsMostWins[i] = teamsMostWins[j];
	teamsMostWins[j] = temp;
}
