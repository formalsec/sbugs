#ifndef _T_
#define _T_

#include "Team_b2.h"
#include "List_T2.h"
#include "Binary_T2.h"

/* Adds a Team to the system */
void addTeam(char *name, BTlink* BThead, int NL);
/* Search for a team in the system and prints it's names and wins */
void searchTeam(char* name, BTlink BThead, int NL);

/* Prints the teams with the most wins */
void showwinners(BTlink BThead, int NL);

/* Frees all memory allocations made regarding teams */
void freeAllTeams(BTlink *BThead);

/* Updates the wins of a team */
Team updateWins(Team team, int to_add);
#endif  