#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "Team.h"


GAME newGame(char *name,TEAM team1,TEAM team2,int home,int away) {
	GAME g = can_fail_malloc(sizeof(struct Game));                   /*aloca memoria para a estrutura do Jogo*/
    g->Gamename=can_fail_malloc(sizeof(char)*(strlen(name)+1));      /*aloca memoria para o nome do jogo*/
    strcpy(g->Gamename,name);
    g->Team1=team1;                                     
    g->Team2=team2;
    g->scoreHome = home;
    g->scoreAway = away;
	return g;
}

void deleteGame(GAME i) {
	if (i)                                              /*Se o jogo existir*/
    {
        free(i->Gamename);                              /*liberta a memoria alocada para o nome do jogo*/
        free(i);                                        /*liberta a memoria alocada para a estrutura do jogo*/
    }
}

void seeGame(GAME i) {
    if (i) printf("%s %s %s %d %d\n",i->Gamename,i->Team1->Teamname,i->Team2->Teamname,i->scoreHome, i->scoreAway);
} 


TEAM winner(GAME i){
    if (i->scoreHome > i->scoreAway)        /*caso a equipa da casa tenha ganho*/
    {
        return i->Team1;
    }
    else if (i->scoreHome < i->scoreAway)   /*caso a equipa visitante tenha ganho*/
    {
        return i->Team2;
    }
    else                                    /*caso empate*/
    {
        return NULL;
    }
    
    

}
    
