#ifndef COMMANDS_H
#define COMMANDS_H

/*-----------------------------------COMMANDS-----------------------*/

link *command_a(link* games_list, link* game_tab,
               team ** teams, long int *cont, long int *max_len);

team **command_A(team **teams, team **last_teams,
                 long int *cont, long int *max_len);

void command_l(link *game_list, long int *cont);

void command_p(link *game_tab, long int *cont, long int m);

void command_P(team **teams_tab, long int *cont, long int m);

void command_s(link *game_t, team **teams_t,
               long int *cont, long int *max_len);

void delete_game(link *game_list, link *game_tab, team **teams_tab,
                 long int node_ptr, long int *max_len);

void command_r(link *game_list, link *game_tab, team **teams_tab,
               long int *cont, long int *max_len);

int comp_strings(const void *str1, const void *str2);

void print_list(char **strs, long int len,
                long int nr_wins, long int cont);

long int winner_list(char **win_list, team *last_team,
                long int *max_wins);

void command_g(team *last_team, long int *cont, long int *max_len);

#endif /* COMMANDS_H */

