#include <stdio.h>
#include "structs.h"
#include "teams.h"
#include "games.h"
#include "hash_tables.h"
#include "main_functions.h"

int main(){

    char c;
    /*line of input counter*/
    int l_count = 0;
    /*games double linked list*/
    node_games *head_games;
    /*teams double linked list*/
    node_teams *head_teams;
    /*games hash_table*/
    node_games *games_table[M];
    /*teams hash_table*/
    node_teams *teams_table[M];
    
    /*initialization of the lists and tables*/
    init_program(&head_games, &head_teams, games_table, teams_table);

    /*while it doesn't read an x, keeps reading characters*/
    while ((c = getchar()) != 'x'){

        /*every new line of input increment the line counter*/
        if (c != '\n'){
            l_count++;
        }

        /*calls a function depending on the command read*/
        switch(c){
            case 'a':
                add_game(&head_games, games_table, teams_table, l_count);
                break;
            case 'p':
                search_game(games_table, l_count);
                break;
            case 'A':
                add_team(&head_teams, teams_table, l_count);
                break;
            case 'P':
                search_team(teams_table, l_count);
                break;
            case 'l':
                list_games(&head_games, l_count);
                break;
            case 'r':
                delete_game(&head_games, games_table, l_count);
                break;
            case 's':
                change_score(games_table, l_count);
                break;
            case 'g':
                list_most_wins(&head_teams, l_count);
                break;
            default:
                break;
        }
    }

    /*frees all memory to end the program*/
    end_program(&head_games, &head_teams);

    return 0;
}