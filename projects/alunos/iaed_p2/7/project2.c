#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbms.h" /* Database Management System Library */


/* 
 *	Command __a__
 *	- Adds a new match.
 */
void cmd_a(DBMS dbms) {
	char match_name[MAXSTRINGSIZE],
		 team1[MAXSTRINGSIZE],
		 team2[MAXSTRINGSIZE];
	uint team1_score, 
		 team2_score;
	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%u:%u", match_name, team1, team2, 
											&team1_score, &team2_score);
	add_match(dbms, match_name, team1, team2, team1_score, team2_score);
}

/* 
 *	Command l
 *	- Lists all inputed matches.
 */
void cmd_l(DBMS dbms) {
	list_all_matches(dbms);
}

/* 
 *	Command p
 *	- Search for a match with the given name.
 */
void cmd_p(DBMS dbms) {
	char match_name[MAXSTRINGSIZE];

	scanf(" %[^:\n]", match_name);

	list_match(dbms, match_name);
}

/* 
 *	Command r
 *	- Remove a match with the given name.
 */
void cmd_r(DBMS dbms) {
	char match_name[MAXSTRINGSIZE];

	scanf(" %[^:\n]", match_name);

	remove_match(dbms, match_name);

}

/* 
 *	Command s
 *  - Changes the score of a match with the given name.
 */
void cmd_s(DBMS dbms) {
	char match_name[MAXSTRINGSIZE];
	uint team1_score, 
		 team2_score;

	scanf(" %[^:\n]:%u:%u", match_name, &team1_score, &team2_score);

	change_match_score(dbms, match_name, team1_score, team2_score);

}

/* 
 * 	Command A
 *	- Adds a new team.
 */
void cmd_A(DBMS dbms) {
	char team_name[MAXSTRINGSIZE];

	scanf(" %[^:\n]", team_name);

	add_team(dbms, team_name);

}

/* 
 *	Command P
 *	- Search for a team with the given name.
 */
void cmd_P(DBMS dbms) {
	char team_name[MAXSTRINGSIZE];

	scanf(" %[^:\n]", team_name);

	list_team(dbms, team_name);
}

/* 
 * 	Command g
 *	- Encontra as equipas que ganharam mais jogos e 
 *  lista por ordem lexicografica (do nome da equipa).
 */
void cmd_g(DBMS dbms) {
	list_best_teams(dbms);
}

int main() {
	/* Command character */
	char cmd;

	/* Flag that signals if the program terminated */
	int terminated = 0;
	
	/* Database Management System */
	DBMS dbms = dbms_init(/*HASHMAX 983*/ 983);

	/* Link NL value of the DBMS to local pointer */
	uint *NL = &(dbms->NL);

	while (terminated != 1) {
		cmd = getchar();
		
		switch (cmd) {
			case 'a':
				cmd_a(dbms);
				break;
			case 'l':
				cmd_l(dbms);
				break;
			case 'p':
				cmd_p(dbms);
				break;
			case 'r':
				cmd_r(dbms);
				break;
			case 's':
				cmd_s(dbms);
				break;
			case 'A':
				cmd_A(dbms);
				break;
			case 'P':
				cmd_P(dbms);
				break;
			case 'g':
				cmd_g(dbms);
				break;
			case 'x':
				terminated = 1;
				break;
		}
		(*NL)++;
		getchar();
	}

	dbms_destroy(dbms);

	return 0;
}
