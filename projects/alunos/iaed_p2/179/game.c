#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "game.h"

Game newGame(char *str1, char *str2, char *str3, int n1, int n2){
    Game new_game = can_fail_malloc(sizeof(struct game));
    new_game->name = str1;
    new_game->team1 = str2;
    new_game->team2 = str3;
    new_game->score1 = n1;
    new_game->score2 = n2;
    return new_game;
}

void freeGame(Game game){
    free(game->name);
    free(game->team1);
    free(game->team2);
    free(game);
    game = NULLgame;
}
