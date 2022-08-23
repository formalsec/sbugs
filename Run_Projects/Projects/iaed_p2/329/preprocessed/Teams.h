#ifndef Teams
#define  Teams
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Max size of a team name */
#define  MAXTNAME 1024

/* Maximum of teams stored */
#define  THTsize  10000


/* contains all the information about each team */
typedef struct Team{
	char        *name;
	int          wins;
}*pTeam;

/* node for aconecting each game*/ 
typedef struct node{
	pTeam 		    t;
	struct node *next;
}*pnode;

/* struct that encapsulates all the information about the teams */
typedef struct TeamSystem{
	pnode *headsteams;
	pnode list_teams;
	int  HTsize;
	int  Nteams;
}TS;

/* inicializes and allocates all the info needed for the game System */
void Init_Teams(TS *ts);

/* hash function (the key is the name of the object) */
int hash(char *n, int M);

/* receves a pointer to the team system*/
void STinsert(TS *ts, pTeam team);

/*insertes the teams at the top the stack of teams */
pnode insertBeginList(pnode head, pnode new);

/* Searches for the game in the hash table */
pTeam STsearch(char *name, TS *ts);

/* frees all the memory remaining related to the teams */
void Deleteallinfo_T(TS *ts);

#endif