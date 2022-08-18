#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct team{
	char *name;
	int victory;
	struct team *next;
};

struct game{
	char *name;
	char *team1;
	char *team2;
	int points1;
	int points2;
	struct game *previous;
	struct game *next;
};

struct in_teams{
	struct team *point_team;
	struct in_teams *next;
};

struct in_games{
	struct game *point_game;
	struct in_games *previous;
	struct in_games *next;
};

struct hashteams{
	struct in_teams **heads;
	size_t capacity;
};

struct hashgames{
	struct in_games **heads;
	size_t capacity;
};
