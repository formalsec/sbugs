#include <stdio.h>

/*
fields:
	1) name -team's name
	2) wins - amount of victories
	3) next - points to the next team
*/
typedef struct team{
	char *name;
	int wins;
	struct team *next;
} team;

/*
fields:
	1) name - game's name
	2) team1 - 1st team's name
	3) team2 - 2nd team's name
	4) score1 - score of the 1st team
	4) score2 - score of the 2nd team
	3) next - points to the next game
*/
typedef struct game{
	char *name;
	char *team1;
	char *team2;
	int *score1;
	int *score2;
	struct game *next;
} game;

/*
fields:
	1) data - points to a game
	2) next - points to the next reference
	3) prev - points to the previous reference
*/
typedef struct game_reference{
	game *data;
	struct game_reference *next;
	struct game_reference *prev;
} game_reference;
