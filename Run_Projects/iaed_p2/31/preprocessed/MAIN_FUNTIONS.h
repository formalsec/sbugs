#ifndef MAIN_FUNTIONS_H
#define MAIN_FUNTIONS_H

/* Library. */

#include "GAME.h"


/* Main Fuctions. */

void add_game(Game ** game_hash, team ** team_hash, int NL);

void show_list_game(Game ** game_hash, int NL); 

void search_game(Game ** game_hash, int NL);

void change_score_game(Game ** game_hash, int NL);

void delete_game(Game ** game_hash, int NL);

void add_team(team ** team_hash, int NL);

void team_search(team ** team_hash, int NL);

void most_vitories(team ** team_hash, int NL);

#endif