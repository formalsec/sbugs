#include "games.h"

/******************************************************
*------------------------COMMANDS---------------------*
*-----------------------PROTOTYPES--------------------*
******************************************************/

void new_game(hash_table_games *game_ht, hash_table_teams *team_ht, h_t_ordered_list *lst, int NL);
void list_all_games(h_t_ordered_list *lst, int NL);
void search_game(hash_table_games *game_ht, int NL);
void delete_game(hash_table_games *game_ht, hash_table_teams *team_ht, h_t_ordered_list *lst, int NL);
void change_score(hash_table_games *game_ht, hash_table_teams *team_ht, int NL);
void new_team(hash_table_teams *team_ht, int NL);
void search_team(hash_table_teams *team_ht, int NL);
void find_winners(hash_table_teams *team_ht, list_names *head_lst_names, int NL);
void command_x(hash_table_games *game_ht, hash_table_teams *team_ht, h_t_ordered_list *lst);