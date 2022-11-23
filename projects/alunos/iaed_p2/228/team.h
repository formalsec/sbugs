#ifndef DOMAIN_H
#define DOMAIN_H
#include "hash_table.h"

typedef struct{
	char *name;
	int games_won;
}team;

/* team constructor */
team *create_team(char *team_name);

/* returns the KEY (i.e. name )of a team */
char *get_team_name(void *v);

void update_games_won(ht *teams,char *team1,char *team2,int score_team1,int score_team2);

/* team destructor */
void free_team(void *v);

#endif