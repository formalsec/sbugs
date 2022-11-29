#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "games.h"
#include "teams.h"
#include "hash.h"


/* Verifies if team is already in system */
int team_exists(hash_teams teams_tbl, char* team_name) {
    return search_team_index_in_hash(teams_tbl, team_name) != -1 ? 1 : 0;
}


/* Verifies if game is already in system */
int game_exists(hash_games games_tbl, char* game_name) {
    return search_game_index_in_hash(games_tbl, game_name) != -1 ? 1 : 0;
}


/* Qsort comparison function for strings */
int string_cmp(const void *input_word1, const void *input_word2) {

    /* Casts inputs to requested type */
    const char **word1 = (const char **)input_word1;
    const char **word2 = (const char **)input_word2;

    /* Returns result of comparing: (0, 1, -1) */
    return strcmp(*word1, *word2);

}


/* Creates a new match */
void adds_new_game(int lct, hash_teams teams_tbl,
                    hash_games games_tbl, dl_list games_lst) {

    /* Holds input from user */
    char *name, *team1, *team2;
    int score1 = 0, score2 = 0;

    /* Temporary buffer that receives input from user */
    char buffer[MAX_STRING_SIZE] = { 0 };

    /* Stores new game */
    match new_game;

    /* Holds wining team's index */
    int winner_idx;

    /* Gets game's name from user and resets buffer */
    scanf(" %[^:\n]", buffer);
    name = (char*) can_fail_calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(name, buffer);
    memset(buffer, 0, MAX_STRING_SIZE);

    /* Gets team1's name from user and resets buffer */
    scanf(":%[^:\n]", buffer);
    team1 = (char*) can_fail_calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(team1, buffer);
    memset(buffer, 0, MAX_STRING_SIZE);

    /* Gets team2's name from user */
    scanf(":%[^:\n]", buffer);
    team2 = (char*) can_fail_calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(team2, buffer);

    scanf(":%d", &score1);
    scanf(":%d", &score2);

    /* If game already exists, prints an error */
    if (game_exists(games_tbl, name)) {

        printf("%d Jogo existente.\n", lct);
        free(name);
        free(team1);
        free(team2);

    /* If one of the teams doesn't exist, prints an error */
    } else if ( ! team_exists(teams_tbl, team1) ||
                ! team_exists(teams_tbl, team2)) {

        printf("%d Equipa inexistente.\n", lct);
        free(name);
        free(team1);
        free(team2);

    /* If everything is valid, creates a game inside the system */
    } else {

        /* Updates wining team's number of victories */
        if (score1 > score2) {
            winner_idx = search_team_index_in_hash(teams_tbl, team1);
            teams_tbl->table[winner_idx]->value->victories++;
        } else if (score1 < score2) {
            winner_idx = search_team_index_in_hash(teams_tbl, team2);
            teams_tbl->table[winner_idx]->value->victories++;
        }

        /* Creates game */
        new_game = creates_match(name, team1, team2, score1, score2);

        /* Inserts game inside the list */
        insert_begin(games_lst, new_game);

        /* Gets one of the table's pointers to point to the new list's node */
        insert_games_hash(games_tbl, games_lst->head);

    }

}


/* Creates a new fut_team */
void add_new_team(int lct, hash_teams teams_tbl, sl_list teams_lst) {

    /* Holds input from user */
    char* name;

    /* Holds newly created team */
    fut_team new_team;

    /* Temporary buffer that receives input from user */
    char buffer[MAX_STRING_SIZE] = { 0 };

    /* Reads from stdin and saves input in temporary variable */
    scanf(" %[^:\n]", buffer);

    /* Reads team's name from stdin */
    name = (char*) can_fail_calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(name, buffer);

    /* If team is already in system, prints error message */
    if (team_exists(teams_tbl, name)) {

        printf("%d Equipa existente.\n", lct);

        /* Frees name because it won't be needed */
        free(name);

    /* Adds team to the system */
    } else {

        /* Creates a valid team */
        new_team = creates_team(name);

        /* Stores team inside a singly linked list */
        insert_team_begin(teams_lst, new_team);

        /* Gets one of the table's pointers to point to the new list's node */
        insert_team_hash(teams_tbl, teams_lst->head);

    }

}


/* Prints all games in system */
void lists_all_games(int lct, dl_list games_lst) {

    /* Iterator */
    int i;

    /* Holds each game during iteration over games' list */
    match gm;

    /* Iterator used upon games' list */
    dl_link ite;

    /* Holds size of games' list */
    int lst_size = games_lst->size;

    /* If list of game is empty, interrupts execution and does nothing */
    if (dl_list_is_empty(games_lst)) return ;

    /* Iterates over games' list and prints each one of it's games */
    for(i = 0, ite = games_lst->tail; i < lst_size; i++) {

        /* Gets current game */
        gm = ite->value;

        /* Prints game */
        printf("%d %s %s %s %d %d\n", lct, gm->name, gm->team1,
                gm->team2, gm->score1, gm->score2);

        /* Gets next game */
        ite = ite->previous;

    }

}


/* Searches for a match and prints it's values if found */
void search_game(int lct, hash_games games_tbl) {

    /* Holds requested game's name */
    char* name;

    /* Holds game's index inside hash table */
    int game_index;

    /* Stores requested game after knowing that it is valid */
    match game;

    /* Temporary buffer that receives input from user */
    char buffer[MAX_STRING_SIZE] = { 0 };

    /* Reads game's name from stdin */
    scanf(" %[^:\n]", buffer);
    name = (char*) can_fail_calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(name, buffer);

    /* Gets game's index inside table */
    game_index = search_game_index_in_hash(games_tbl, name);

    /* If game doesn't exist, prints an error */
    if (game_index == -1) {

        printf("%d Jogo inexistente.\n", lct);

    /* If game exists, prints it's values */
    } else {

        game = games_tbl->table[game_index]->value;

        printf("%d %s %s %s %d %d\n", lct, game->name, game->team1,
                game->team2, game->score1, game->score2);

    }

    /* Frees previously allocated temporary memory */
    free(name);


}


/* Searches for a team and prints it's name and score if found */
void search_team(int lct, hash_teams teams_tbl) {

    /* Holds stdin's name input */
    char* name;

    /* Holds team's index inside hash table */
    int team_index;

    /* Stores requested team after knowing that it is valid */
    fut_team team;

    /* Temporary buffer that receives input from user */
    char buffer[MAX_STRING_SIZE] = { 0 };

    /* Reads team's name from stdin */
    scanf(" %[^:\n]", buffer);
    name = (char*) can_fail_calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(name, buffer);

    /* Gets team index inside table */
    team_index = search_team_index_in_hash(teams_tbl, name);

    /* If team doesn't exist, prints an error */
    if (team_index == -1) {

        printf("%d Equipa inexistente.\n", lct);

    /* If team exists, prints it's name and victories  */
    } else {

        team = teams_tbl->table[team_index]->value;
        printf("%d %s %d\n", lct, team->name, team->victories);

    }

    /* Frees previously allocated temporary memory */
    free(name);

}


/* Removes match from system */
void deletes_game(int lct, hash_teams teams_tbl,
                    hash_games games_tbl, dl_list games_lst) {

    /* Holds requested game's name */
    char* name;

    /* Holds game's index inside hash table */
    int game_index;

    /* Holds game that is going to be deleted */
    match game;

    /* Holds index of the team that won the game */
    int team_idx;

    /* Temporary buffer that receives input from user */
    char buffer[MAX_STRING_SIZE] = { 0 };

    /* Reads game's name from stdin */
    scanf(" %[^:\n]", buffer);
    name = (char*) can_fail_calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(name, buffer);

    /* Gets game's index inside table. If not found, returns -1 */
    game_index = search_game_index_in_hash(games_tbl, name);

    /* If game doesn't exist, prints an error message */
    if (game_index == -1) {

        printf("%d Jogo inexistente.\n", lct);

    /* If found, deletes it */
    } else {

        /* Gets game */
        game = games_tbl->table[game_index]->value;

        /* Updates match's winner's number of victories because
         * the game no int er exists */
        if (game->score1 > game->score2) {

            /* Gets winner's index inside the table */
            team_idx = search_team_index_in_hash(teams_tbl, game->team1);

            /* Removes it's victory */
            teams_tbl->table[team_idx]->value->victories--;

        } else if (game->score1 < game->score2) {

            /* Gets winner's index inside the table */
            team_idx = search_team_index_in_hash(teams_tbl, game->team2);

            /* Removes it's victory */
            teams_tbl->table[team_idx]->value->victories--;

        }

        /* Deletes game's node inside doubly linked list */
        remove_node(games_lst, games_tbl->table[game_index]);

        /* Deletes game inside table */
        deletes_game_hash(games_tbl, game_index);

    }

    /* Frees previously allocated temporary memory */
    free(name);

}


/* Changes final score of a match */
void changes_game_score(int lct, hash_teams teams_tbl, hash_games games_tbl) {

    /* Holds game's name */
    char* name;

    /* New team1's score and team2's score, respectively */
    int new_sc1 = 0, new_sc2 = 0;

    /* Holds requested game */
    match game;

    /* Holds team1 and team2's index inside the table */
    int t1_idx, t2_idx;

    /* Temporary buffer that receives input from user */
    char buffer[MAX_STRING_SIZE] = { 0 };

    /* Reads game's name from stdin */
    scanf(" %[^:\n]", buffer);
    name = (char*) can_fail_calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(name, buffer);

    /* Gets from stdin, new game's final score */
    scanf(":%d", &new_sc1);
    scanf(":%d", &new_sc2);

    /* If game doesn't exist, prints an error message */
    if( ! game_exists(games_tbl, name)) {

        printf("%d Jogo inexistente.\n", lct);

    /* If game exists, changes it's score */
    } else {

        /* Gets requested game from table */
        game = games_tbl->
                table[search_game_index_in_hash(games_tbl, name)]->value;

        /* Gets both team's indexes */
        t1_idx = search_team_index_in_hash(teams_tbl, game->team1);
        t2_idx = search_team_index_in_hash(teams_tbl, game->team2);

        /* Previously, team1 was the winner */
        if (game->score1 > game->score2) {

            /* Now, team1 is still the winner and doesn't need to update it's
             * victories */
            if (new_sc1 > new_sc2) {

                ;

            /* Now, team2 is the winner so, team2 gets one victory and team1
             * losses one victory */
            } else if (new_sc1 < new_sc2) {

                teams_tbl->table[t1_idx]->value->victories--;
                teams_tbl->table[t2_idx]->value->victories++;

            /* Now, match is a draw and team1 losses one victory */
            } else {

                teams_tbl->table[t1_idx]->value->victories--;

            }

        /* Previously, team2 was the winner */
        } else if (game->score1 < game->score2) {

            /* Now, team1 is the winner so, team1 gets one victory and team2
             * losses one victory */
            if (new_sc1 > new_sc2) {

                teams_tbl->table[t1_idx]->value->victories++;
                teams_tbl->table[t2_idx]->value->victories--;

            /* Now, team2 is still the winner and doesn't need to update it's
             * victories */
            } else if (new_sc1 < new_sc2) {

                ;

            /* Now, match is a draw so, team2 losses one victory */
            } else {

                teams_tbl->table[t2_idx]->value->victories--;

            }

        /* Previously, match was a draw */
        } else {

            /* Now, team1 is the winner */
            if (new_sc1 > new_sc2) {

                teams_tbl->table[t1_idx]->value->victories++;

            /* Now, team2 is the winner */
            } else if (new_sc1 < new_sc2) {

                teams_tbl->table[t2_idx]->value->victories++;

            /* Now, match is still a draw and there is no need to update
             * team's victories */
            } else {

                ;

            }

        }

        /* Updates game's scores */
        game->score1 = new_sc1;
        game->score2 = new_sc2;

    }

    /* Frees previously allocated temporary memory */
    free(name);

}


/* Prints, in alphabetical order, all team's names that won the most games */
void prints_top_teams(int lct, sl_list teams_lst) {

    /* Iterators */
    int i, j;

    /* Holds max score and number of teams with such score during iterations */
    int max[2] = {0, 0};

    /* Holds teams' list's size */
    int lst_size = teams_lst->size;

    /* Holds current node during iterations */
    sl_link node;

    /* Holds current team during iterations */
    fut_team team;

    /* Stores every team's name that has the max number of victories */
    char **bag_teams;

    /* If list has no teams, interrupts execution */
    if (sl_list_is_empty(teams_lst)) return ;

    /* Iterates over each node inside list and gets max victories and
     * number of teams with such score */
    for (i = 0, node = teams_lst->head; i < lst_size; i++, node = node->next) {

        /* Gets current team */
        team = node->value;

        /* If node has a higher number of victories, resets max and
         * stores new max victories */
        if (team->victories > max[0]) {

            max[0] = team->victories;
            max[1] = 1;

        /* If it has the same amount of victories, increases number
         * of teams with such score */
        } else if (team->victories == max[0]) {

            max[1]++;

        }

    }

    /* Allocates required memory for the teams with max victories */
    bag_teams = (char **) can_fail_calloc(max[1], sizeof(char*));

    /* Iterates over each node and gets teams with max score */
    for (i = 0, node = teams_lst->head, j = 0;
         i < lst_size;
         i++, node = node->next) {

        /* Holds current team */
        team = node->value;

        /* If team has the max number of victories, puts a pointer
         * towards it's name */
        if(team->victories == max[0]) {
            bag_teams[j++] = team->name;
        }

    }

    /* Sorts teams */
    qsort(bag_teams, max[1], sizeof(char*), string_cmp);

    /* Prints teams */
    printf("%d Melhores %d\n", lct, max[0]);
    for (i = 0; i < max[1]; ++i) {
        printf("%d * %s\n", lct, bag_teams[i]);
    }

    /* Frees previously allocated temporary memory */
    free(bag_teams);

}
