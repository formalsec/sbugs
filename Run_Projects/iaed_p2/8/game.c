#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myLib.h"
#include "game.h"
#include "team.h"


/* Creates a game*/
Game * new_game(char *name, Team *t1, Team *t2, Score score){
	
	extern char* strdup(const char*);
	Game * game = (Game *) malloc(sizeof(Game));
    EXIT_IF_ERROR("game_new: create_game");

    /* Incialization of variables */
    game->name = strdup(name);
	game->t1 = t1;
	game->t2 = t2;
	game->score = score;

	return game;
}

/* Frees memory of game */
void game_free(Game *g) {
	ERROR_IF_NULL(g, "game_free", exit(EXIT_FAILURE));

    /* free da string com o nome */
    free((char *)g->name);

    /* Doesnt make sense do make free of t1 && t2 that can be utilize in other game*/

    /* Free da estrutura Game */
    free((Game *)g);
}

/*Gets game name*/
char *game_get_name(Game * g) {
	ERROR_IF_NULL(g, "game_get_name", exit(EXIT_FAILURE));
	return (char *)g->name;
}

/*Gets game of team 1*/
Team * game_get_team1(Game * g) {
	ERROR_IF_NULL(g, "game_get_team1", exit(EXIT_FAILURE));
	return (Team *)g->t1;
}

/*Gets game of team 2*/
Team * game_get_team2(Game * g) {
	ERROR_IF_NULL(g, "game_get_team2", exit(EXIT_FAILURE));
	return (Team *)g->t2;
}

/*Gets game score 1*/
int game_get_score1(Game * g) {
	ERROR_IF_NULL(g, "game_get_score1", exit(EXIT_FAILURE));
	return g->score.t1;
}

/*Gets game score 2*/
int game_get_score2(Game * g) {
	ERROR_IF_NULL(g, "game_get_score2", exit(EXIT_FAILURE));
	return g->score.t2;
}

/*Game set score*/
void game_set_score(Game * g, int s1, int s2) {
	ERROR_IF_NULL(g, "game_set_score", exit(EXIT_FAILURE));
	
    /* could validate s1 && s2*/

    /* Sets new score */
    g->score.t1 = s1;
    g->score.t2 = s2;
}

/* With the game and team name and gives the team with a name or NULL */
Team * game_get_team(Game *g, char * team_name) {

    if ( strcmp(team_get_name(g->t1), team_name)==0 )
        return (Team *)g->t1;
    else if ( strcmp(team_get_name(g->t2), team_name)==0 )
        return (Team *)g->t2;
    else
        return NULL;
}


/* With the game, gives the winning team or Null in case of a draw */
Team * game_get_winner(Game *g) {

    if (g->score.t1 > g->score.t2)
        return (Team *)g->t1;
    else if (g->score.t2 > g->score.t1)
        return (Team *)g->t2;
    else
        return NULL;

}

/* Prints game atributes */
void game_print(Game *g) {
	ERROR_IF_NULL(g, "game_print", exit(EXIT_FAILURE));
	printf("Game: NAME=%s TEAM1=%s TEAM2=%s SCORE1=%d SCORE2=%d\n", game_get_name(g),game_get_team1(g)->name, game_get_team2(g)->name, game_get_score1(g), game_get_score2(g));
}

/* Prints game to a string */
char * game_to_string(Game *g, char *buf) {
	ERROR_IF_NULL(g, "game_to_string", exit(EXIT_FAILURE));
    sprintf(buf, "%s %s %s %d %d\n", game_get_name(g),game_get_team1(g)->name,game_get_team2(g)->name, game_get_score1(g), game_get_score2(g));
    return buf;
}
