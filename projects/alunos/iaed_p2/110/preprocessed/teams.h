#ifndef teams_h
#define teams_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 1023

typedef struct team{
    char *name;                 /* This structure stores a teams' name and its wins and  */ 
    int wins;                   

}*ptrTeam; 

/*--------------------teamInit-------------------------
INPUT: name (string)
OUTPUT: team (struct ptrTeam)
Initializes a team from a given name*/
ptrTeam teamInit(char* name);

/*-------------------teamDestroy----------------------
INPUT: team (struct ptrTeam)
OUTPUT: N/A
Destroys a given team*/
void teamDestroy(ptrTeam team);

/*-------------------teamName----------------------
INPUT: team (struct ptrTeam)
OUTPUT: teams' name (string)
Retuns the name of a given team*/
char* teamName(ptrTeam team);

/*-------------------teamWins----------------------
INPUT: team (struct ptrTeam)
OUTPUT: teams' wins (int)
Retuns the wins of a given team*/
int teamWins(ptrTeam team);

/*-------------------teamPrint----------------------
INPUT: NL, team (struct ptrTeam)
OUTPUT: N/A
Prints the data of a given team*/
void teamPrint(int NL, ptrTeam team);


#endif