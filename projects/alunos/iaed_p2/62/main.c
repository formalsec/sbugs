#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teams.h"
#include "games.h"

int main()
{
    /* Initializes two hash tables, one for the teams and the other one for the
    games, each of them with 503 lines */
    TeamHT team_ht = team_ht_init(727);
    GameHT game_ht = game_ht_init(&team_ht, 727);

    /* Line counter, useful when outputting errors */
    unsigned long int NL = 1;

    /* Buffers used for storing input and passing it on to the functions */
    char command;
    char name_buff[1024], team1_buff[1024], team2_buff[1024];
    int score1_buff, score2_buff;

    while ((command = getchar()) != 'x')
    {
        switch (command)
        {

        /* Inserts a new game in the system */
        case 'a':
            scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d\n", name_buff, team1_buff,
                  team2_buff, &score1_buff, &score2_buff);
            game_ht_insert(&game_ht, name_buff, team1_buff, team2_buff,
                           score1_buff, score2_buff, NL);
            break;

        /* Prints all the games in the system, ordered by entry date */
        case 'l':
            scanf("\n");
            game_ht_print_order(game_ht, NL);
            break;

        /* Searches for a given game name in the system and outputs that game's
        information or a warning in case the game isn't present */
        case 'p':
            scanf(" %[^:\n]\n", name_buff);
            game_ht_search_print(game_ht, name_buff, NL);
            break;

        /* Deletes a game from the system */
        case 'r':
            scanf(" %[^:\n]\n", name_buff);
            game_ht_delete(&game_ht, name_buff, NL);
            break;

        /* Changes a game's scores */
        case 's':
            scanf(" %[^:\n]:%d:%d\n", name_buff, &score1_buff, &score2_buff);
            game_ht_change_score(game_ht, name_buff, score1_buff, score2_buff, NL);
            break;

        /* Inserts a new team in the system */
        case 'A':
            scanf(" %[^:\n]\n", name_buff);
            team_ht_insert(&team_ht, name_buff, NL);
            break;

        /* Searches a team in the system and outputs its name and 
        the number of victories that team has. If there is no 
        such team in the system, issue a warning */
        case 'P':
            scanf(" %[^:\n]\n", name_buff);
            team_ht_search_print(team_ht, name_buff, NL);
            break;

        /* Prints all the teams that share the highest number of victories by
        alphabetical order */
        case 'g':
            scanf("\n");
            team_ht_print_best(team_ht, NL);
            break;

        default:
            continue;
        }

        /* Updates the line counter used in the issue outputs */
        NL++;
    }

    /* Frees both data structures */
    game_ht_free(game_ht);
    team_ht_free(team_ht);

    return 0;
}
