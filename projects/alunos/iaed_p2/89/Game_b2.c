#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Game_b2.h"

/* Allocs memory for a Game and its name. Returns a pointer to the Game Created */
Game Gnew(char *name, Team team1, Team team2, int score1, int score2, int NL){
    Game new = (Game) can_fail_malloc(sizeof(struct game));
    new->name = my_strdup(name);
    new->team1 = team1;
    new->team2 = team2;
    new->score1 = score1;
    new->score2 = score2;
    new->id = NL;
    return new;
}

/* Changes the scores of game*/
Game Gchange_score(Game game, int score1, int score2){
    game->score1 = score1;
    game->score2 = score2;
    return game;
}

/* Frees the memory of the Game's name and the Game */
void Gdelete(Game game){
    free(game->name);
    free(game);
}

/* The sorting function to organize the games */
int Gqsort(const void* game1, const void* game2){
    return Ggetid(*(Game*) game1) - Ggetid(*(Game*) game2);
}

/* Returns the name of a Game */
char* Ggetname(Game game){
    return game->name;
}

/* Returns the winner team of a game */
Team Ggetwinner(Game game){
    if (Ggetscore1(game) > Ggetscore2(game))
        return Ggetteam1(game);
    if (Ggetscore2(game) > Ggetscore1(game))
        return Ggetteam2(game);
    else
        return NULL;
}

/* Returns the team1 of a game */
Team Ggetteam1(Game game){
    return game->team1;
}

/* Returns the team2 of a game */
Team Ggetteam2(Game game){
    return game->team2;
}

/* Returns the score1 of game */
int Ggetscore1(Game game){
    return game->score1;
}

/* Returns the score2 of game */
int Ggetscore2(Game game){
    return game->score2;
}

/* Returns the if of game */
int Ggetid(Game game){
    return game->id;
}