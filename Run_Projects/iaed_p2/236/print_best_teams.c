#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "structures.h"

/*alphabeic sort func from alphabetic_sort.c */
void merge_sort(char *arr[], int l, int r);

/*
prints all best teams
	4 steps:
		1) calculation of the greatest amount of wins
		2) getting names of all best teams
		3) sorting names alphabetically
		4) displaying
input: hash table of teams(*team[]), new line(int)
output: none
*/
void printBestTeams(team *team_hash_table[], int NL){
	int wins, size, iter, i;
	team *tmp_team;
	char **names;
	wins = 0;
	/* step 1 */
	for (i = 0; i < TABLE_SIZE; ++i){
		tmp_team = team_hash_table[i];
		while(tmp_team!=NULL){ 
			if(tmp_team->wins > wins) wins = tmp_team->wins;
			tmp_team = tmp_team->next;
		}
	}
	/* step 2 */
	iter = 0;
	size = 0;
	for (i = 0; i < TABLE_SIZE; ++i){
		tmp_team = team_hash_table[i];
		while(tmp_team!=NULL){ 
			if(tmp_team->wins==wins){
				size++;
			}
			tmp_team = tmp_team->next;
		}
	}
	names = malloc(size*sizeof(char*));
	/* if no best teams it does nothing*/
	if(size!=0){
		/* step 3 */
		/* adding names of best teams to array of strings */
		for (i = 0; i < TABLE_SIZE; ++i){
			tmp_team = team_hash_table[i];
			while(tmp_team!=NULL){
				if(tmp_team->wins==wins){
					names[iter] = tmp_team->name;
					iter++;
				}
				tmp_team = tmp_team->next;
			}
		}
		/* sorting */
		merge_sort(names, 0, size-1);
		/* step 4 */
		printf("%d Melhores %d\n", NL, wins);
		for (i = 0; i < size; ++i){
			printf("%d * %s\n", NL, names[i]);
		}
	}
	/* freeing */
	free(names);
	free(tmp_team);
}
