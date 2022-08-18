#include <stdio.h>
#include "functions.h"
#include "games.h"
#include "teams.h"
#include "hash.h"


int main() {

    /* User's input command */
    int command;

    /* Counts text file's lines */
    int line_counter = 1;

    /* Initializes teams' singly linked list */
    sl_list teams_lst = create_sl_list();

    /* Initializes games' doubly linked list */
    dl_list games_lst = create_dl_list();

    /* Initializes teams' hash table */
    hash_teams teams_tbl = create_teams_hash_table(INITIAL_TABLE_SIZE);

    /* Initializes games' hash table */
    hash_games games_tbl = create_games_hash_table(INITIAL_TABLE_SIZE);

    /* Controls which command is going to be executed */
    while ((command = getchar()) != 'x') {

        switch (command) {

            case 'a':
                adds_new_game(line_counter, teams_tbl, games_tbl, games_lst);
                break;

            case 'A':
                add_new_team(line_counter, teams_tbl, teams_lst);
                break;

            case 'l':
                lists_all_games(line_counter, games_lst);
                break;

            case 'p':
                search_game(line_counter, games_tbl);
                break;

            case 'P':
                search_team(line_counter, teams_tbl);
                break;

            case 'r':
                deletes_game(line_counter, teams_tbl, games_tbl, games_lst);
                break;

            case 's':
                changes_game_score(line_counter, teams_tbl, games_tbl);
                break;

            case 'g':
                prints_top_teams(line_counter, teams_lst);
                break;

            default:
                continue;

        }

        /* Increments line's counter (mainly used for debug purposes) */
        line_counter++;

    }

    /* Clears all program's memory */
    destroy_teams_hash(teams_tbl);
    sl_list_destroy(teams_lst);
    destroy_games_hash(games_tbl);
    dl_list_destroy(games_lst);

    return 0;
}
