#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"


char *strdup(const char *s) {
  size_t len = strlen(s) + 1;
  void *new = malloc(len);
  if (new == NULL)
    return NULL;
  return (char *)memcpy(new, s, len);
}

game *create_game(char *name,char *team1,char *team2,int score_first_team,int score_second_team){
	game *g = malloc(sizeof(game));

	g -> name = strdup(name); /* allocates only the necessary memory */
	g -> team1 = strdup(team1);
	g -> team2 = strdup(team2);
	g -> score1 = score_first_team;
	g -> score2 = score_second_team;

	return g;
}

char *get_game_name(void *v) { return ((game *)v)->name; }


void free_game(void *v) {
  game *g = v;
  
  free(g->name); /* to avoid memory leaks */
  free(g->team1);
  free(g->team2);
  free(g);
}