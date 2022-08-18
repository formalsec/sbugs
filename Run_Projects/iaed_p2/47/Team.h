#ifndef _TEAM_H
#define _TEAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *teamKey;    

typedef struct Team{ /*Estrutura da Equipa*/
    char *Teamname;  
    int wongames;
}*TEAM;

#define keyteam(A) (A->Teamname)        
#define eqteam(A, B) (strcmp(A,B) == 0)


TEAM newTeam(char *name);   /*Funcao que aloca memoria para uma equipa */
void deleteTeam(TEAM i);    /*Funcao que apaga a equipa do sistema, libertando a memoria que foi alocada*/
void seeTeam(TEAM i);       /*Funcao que da print ao nome de uma equipa*/

#endif