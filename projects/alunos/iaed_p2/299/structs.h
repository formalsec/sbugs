#ifndef STRUCTS_H
#define STRUCTS_H

#define NAME_SIZE 1024
#define GAMES_SZ 23269
#define TEAMS_SZ 23269


/* Doubly linked list that contains the names of every game.
 * Also contains a pointer to the related game. */
typedef struct game_names {
	struct game_names *prev, *next, *last;
	struct games *game;
	char *name;
} game_names;



/* Doubly linked list of games (each game holds its name,
 * both participating teams, and their scores */
typedef struct games {
	struct games *prev, *next, *last;
	struct game_names *name;
	struct teams *team1, *team2;
	/* Holds each team's score*/
	int sc[2];

} games;


/* Singly Linked list of teams (each team holds its name, and
 * the number of wins) */
typedef struct teams {
	int wins;
	struct teams *next;
	char *name;

} teams;

#endif /* STRUCTS_H */
