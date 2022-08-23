#include "team.h"
#include "OOP.h"
#include "hash_table.h"
#include <stdlib.h>

team *create_team(char *team_name){
	team *t = malloc(sizeof(team));
	t -> name = strdup(team_name);
	t-> games_won = 0;

	return t;
}

char *get_team_name(void *v) { return ((team *)v)->name; }

void update_games_won(ht *teams,char *team1,char *team2,int score_team1,int score_team2){
	team *t;
	
	/* depending on who won the game increments the team's games_won parameter */
	if (score_team1 > score_team2) {
		t = find_in_ht(teams,team1);
		t->games_won++;
	}
	else {
		t = find_in_ht(teams,team2);
		t->games_won++;
	}
}

void free_team(void *v) {
  team *t = v;
  free(t->name);
  free(t);
}