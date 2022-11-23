#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Match.h"


Match new_match(const char *match_name, Team team1, 
					Team team2, const uint score1, const uint score2) {

	Match new_match = can_fail_malloc(sizeof(struct match));
	/*Team winning_team;*/

	new_match->name = can_fail_malloc(sizeof(char) * (strlen(match_name) + 1));
	strcpy(new_match->name, match_name);

	new_match->team_1 = team1;
	new_match->team_2 = team2;

	new_match->score_1 = score1;
	new_match->score_2 = score2;

	if(score1 > score2) 
		team1->matches_won++;
	else if(score1 < score2)
		team2->matches_won++;

	return new_match;
}


void free_match(Match m) {
	if (m) {
		free(m->name);
		free(m);
	}
}