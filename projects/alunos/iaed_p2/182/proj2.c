#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "auxiliary.h"
#include "structures.h"
#include "commands.h"


int main()
{
    int i;
    unsigned int NL = 0;

    game **first_game = can_fail_malloc(sizeof(game*));
    game **last_game = can_fail_malloc(sizeof(game*)); 

    glink **game_table = can_fail_malloc(sizeof(glink*) * HASHSIZE);
    tlink **team_table = can_fail_malloc(sizeof(tlink*) * HASHSIZE);

    *first_game = NULL;
    *last_game = NULL;

    for (i = 0; i < HASHSIZE; i++)
    {
        game_table[i] = NULL;
        team_table[i] = NULL;
    }

    while (OK)
    {
        char com;
        NL++;
        switch (com = getchar())
        {
            case 'A':
            {
                getchar(); /* Skips empty space */
                add_team(NL, team_table);
                break;
            }
            case 'a':
            {
                getchar();
                add_game(NL, first_game, last_game, game_table, team_table);
                break;
            }
            case 'l':
            {
                getchar();
                list_games(NL, first_game);
                break;
            }
            case 'P':
            {
                getchar();
                search_team(NL, team_table);
                break;
            }
            case 'p':
            {
                getchar();
                search_game(NL, game_table);
                break;
            }
            case 'r':
            {
                getchar();
                remove_game(NL, first_game, last_game, game_table, team_table);
                break;
            }
            case 's':
            {
                getchar();
                change_score(NL, game_table, team_table);
                break;
            }
            case 'g':
            {
                getchar();
                best_teams(NL, team_table);
                break;
            }
            case 'x':
                free_memory(game_table, team_table, first_game, last_game);
                return EXIT_SUCCESS;
                
            default:
            {
                break;
            } 
        }
    }

    return EXIT_FAILURE;
}