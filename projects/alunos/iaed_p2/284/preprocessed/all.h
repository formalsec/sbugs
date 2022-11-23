#ifndef ALL_H
#define ALL_H

#include "constants.h"
#include "List.h"

/*--------------------*\
 * Funcoes principais *
\*--------------------*/

void add_game(long int NL, list* game_list, list* team_list);
void add_team(long int NL, list* team_list);
void list_games(long int NL, list* game_list);
void find_game(long int NL, list* game_list);
void find_team(long int NL, list* team_list);
void remove_game(long int NL, list* game_list);
void change_game(long int NL, list* game_list);
void get_winners(long int NL, list* team_list);

#endif /* ALL_H */