#include "constants.h" /*  */
#include "Team.h" /*  */

#ifndef MATCH_H
#define MATCH_H

/* Key for Match Structure. */
typedef const char* m_Key;

/* Match* Structure */
typedef struct match {
    char *name;
	Team team_1,
		 team_2;
	uint score_1, 
		 score_2;
}* Match;

#define m_key(M) (M->name)
#define m_eq(M1, M2) (strcmp(M1, M2) == 0)
#define m_cmp(M1, M2) (strcmp(M1,M2))

Match new_match(const char *match_name, Team team1, 
					Team team2, const uint score1, const uint score2);
					
void free_match(Match m);

#endif /* MATCH_H */




