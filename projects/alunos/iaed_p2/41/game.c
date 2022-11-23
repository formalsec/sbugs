#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "game.h"

/*Creates a new team and returns its pointer.*/
game create_game(char * name, team team_1, team team_2, int score_1, int score_2)
{
    game new_game;
    new_game = (game) can_fail_malloc(sizeof(struct gm));
    
    new_game->name = (char *)can_fail_malloc(sizeof(char)*(strlen(name) + 1));
    strcpy(new_game->name, name);

    new_game->team_1 = team_1;
    new_game->team_2 = team_2;
    
    new_game->score_1 = score_1;
    new_game->score_2 = score_2;

    return new_game;
}

/*Frees game structures.*/
void free_game(game game)
{
    free(game->name);
    free(game);
}