#ifndef _TEAM_H_
#define _TEAM_H_

typedef struct team {
	char *name;
	int winnings;
} *Team;


/*
Cria uma equipa. Recebe os parametros referentes a 'team'.
Retorno: ponteiro para uma equipa.
*/
Team create_team(char *name);

#endif