#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "games.h"
#include "teams.h"
#include "commands.h"
#define MAX_STR_LEN 1024 /*strings maximum length*/

/*Function that execute the command 'c'*/
void execute_command(char c, team *** teams_t_ptr, link **game_t_ptr,
                     link *game_list, team **last_team,
                     long int *cont, long int *max_len){
    switch(c){
            /*------------------MAIN_COMMAND---------------*/

            case 'a':
                *game_t_ptr = command_a(game_list, *game_t_ptr,
                                     *teams_t_ptr, cont, max_len);
                getchar();/* go to next line(read '\n')*/
                break;
            case 'A':
                *teams_t_ptr = command_A(*teams_t_ptr, last_team,
                                      cont, max_len);
                getchar();
                break;
            case 'l':
                command_l(game_list, cont);
                getchar();
                break;
            case 'p':
                command_p(*game_t_ptr, cont, *max_len);
                getchar();
                break;
            case 'P':
                command_P(*teams_t_ptr, cont, *(max_len + 2));
                getchar();
                break;
            case 'r':
                command_r(game_list, *game_t_ptr, *teams_t_ptr,
                          cont, max_len);
                getchar();
                break;
            case 's':
                command_s(*game_t_ptr, *teams_t_ptr, cont, max_len);
                getchar();
                break;
            case 'g':
                command_g(*last_team, cont, max_len);
                getchar();
                break;

        }
}

/*-------------------------------MAIN_FUNCTION----------------------------*/
/*FUNCTION THAT READS THE GIVEN COMMAND AND RETURN DE RESPECTIVE OUTPUT*/
int main (){

    /*command counter*/
    long int cont = 0;
    /*variable containing the max length of the game table,
    the number of elements in the game table,
    the max length of the teams table,
    and the number of elements in the teams table, respectively*/
    long int *max_len;
    /*variable that contains the character of the command to execute*/
    char c;
    /*hash table containing all games*/
    link *game_tab;
    /*hash table containing all teams*/
    team **teams_tab;
    /*pointer for the head and tail of the game list*/
    link *game_list;
    /*pointer to the last team*/
    team **last_team;

    /*init max_len*/
    max_len = malloc(sizeof(long int) * 4);
    *max_len = 883;
    *(max_len + 1) = 0;
    *(max_len + 2) = 883;
    *(max_len + 3) = 0;
    /*init the game hash table*/
    game_tab = malloc(sizeof(link) * (*max_len));
    table_g_init(game_tab, *max_len);
    /*init the team hash table*/
    teams_tab = malloc(sizeof(team*) * (*(max_len + 2)));
    table_t_init(teams_tab, *(max_len + 2));
    /*init the list containing the head and tail of the game list*/
    game_list = malloc(sizeof(link)*2);
    /*init the head of the game list*/
    *game_list = NULL;
    /*init the tail of the game list*/
    *(game_list + 1) = NULL;
    /*init the last team as empty*/
    last_team = malloc(sizeof(team*));
    *(last_team) = NULL;

    while((c = getchar()) != 'x'){
        execute_command(c, &teams_tab, &game_tab, game_list, last_team,
                        &cont, max_len);
    }

    /*destroy all tables*/
    free(max_len);
    destroy_game_st(game_list);
    free(game_list);
    free(game_tab);
    destroy_team_st(*last_team);
    free(last_team);
    free(teams_tab);

    return 0;
}
