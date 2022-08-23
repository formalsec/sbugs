#ifndef GAME_H
#define GAME_H

#include "OOP.h"

/* Internal representation for a game*/
typedef struct {
	char *name, *team1, *team2;
	int score1,score2;
}game;

/* glibc's implementation of strdup*/
char *strdup(const char *s);

/* game constructor */
game *create_game(char *name,char *team1,char *team2,int score1,int score2);

/* returns the KEY (i.e. name )of a game */
char *get_game_name(void *v);

/*game destructor*/
void free_game(void *v);

#endif