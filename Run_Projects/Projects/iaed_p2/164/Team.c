#include "Team.h"

/* Creates and returns a new Team, initializing all it's values as 0 and NULL.*/
Team InitTeam(){
    Team t = (Team) malloc(sizeof(struct team));
    t->wins = 0;
    t->name = NULL;
    return t;
}

/* Receives a Team and returns it's number of wins.*/
int Wins(Team t){
    return t->wins;
}

/* Receives a Team and returns it's name.*/
char * TeamName(Team t){
    return t->name;
}

/* Receives a Team and a name, setting the Team's name as "name", only allocating the necessary memory.*/
void SetTeamName(Team t, char name[]){
    char * p_name = (char*) malloc(strlen(name) + 1);
    strcpy(p_name, name);
    t->name = p_name;
}

/* Receives a Team and a line number, writing the line number and the Team's characteristics.*/
void WriteTeam(Team t, int NL){
    printf("%d %s %d\n", NL, TeamName(t), Wins(t));
}

/* Receives a Team and increments it's wins.*/
void IncWins(Team t){
    t->wins++;
}

/* Receives a Team and decrements it's wins.*/
void DecWins(Team t){
    t->wins--;
}

/* Receives a Team and destroys it, aswell as it's name.*/
void DestroyTeam(Team t){
    free(t->name);
    free(t);
}