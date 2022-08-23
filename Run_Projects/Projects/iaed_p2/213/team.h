#ifndef TEAM
#define TEAM

#include <string.h>

/* Estrutura Team, representa uma equipa */
typedef struct team_node {
	int wins;
	char * name;
} * Team;


/* Nomes das equipas sao iguais */
#define eq(a, b) (strcmp(a, b) == 0)

#define teamName(a) (a->name)
#define teamWins(a) (a->wins)


/* Prototipos das funcoes referentes a team */
Team newTeam(char *name);
void freeTeam(Team t);
void printTeam(Team t, int c);
void printTeamWins(Team t, int c);
int add_win(Team t);
int rm_win(Team t);

#endif
