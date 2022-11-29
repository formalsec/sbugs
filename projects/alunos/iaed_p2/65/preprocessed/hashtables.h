#ifndef HASHTABLES_H_INCLUDED
#define HASHTABLES_H_INCLUDED

#include "linked_lists.h"

int hash(char *, int);



/*-------------funcoes para hashtable de jogos-------------*/
nodeGame * search_game_ht(nodeGame * [], char *, int);

void add_game_ht(nodeGame * [], indexNode **, char *, int, int, int, char *, char *, int);

void del_game_ht(nodeGame * [], char *, int);

void print_game(int, Game *);

void destroy_games_ht(nodeGame * [], indexNode *);



/*-------------funcoes para hashtable de equipas--------------*/
nodeTeam * search_team_ht(nodeTeam * [], char *, int);

void add_team_ht(nodeTeam * [], indexNode **, char *, int);

void change_wins_directly(nodeTeam *, int);

void print_team(int, Team *);

void destroy_teams_ht(nodeTeam * [], indexNode *);

#endif