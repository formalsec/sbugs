#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct team {
	char *name;
	int gamesWon;
} Team;

typedef struct match {
	char *name, *team1, *team2;
	int score1, score2;
} Match;

#endif