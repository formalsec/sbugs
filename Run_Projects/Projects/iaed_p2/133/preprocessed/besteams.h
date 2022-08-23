#ifndef BESTEAMS_H
#define BESTEAMS_H

/*
    funtions
*/

/*initializing the list of best teams*/
void init_list_teams(char **best_teams, int N);
/*clear the teams*/
void clear_list_teams(char **best_teams, int N);
/*inserts a team into the list of best teams*/
void search_and_add_teams_list(teams **lst_teams, char **best_teams, int number);
/*free s the list of best teams*/
void free_list_teams(char **best_teams);
/*prints the list of best teams*/
void print_best_teams(char **best_teams, int nl, int max);
/*compare two strings for the q sort*/
int cmpstrings(const void*a, const void*b);
/*sort the list of best games accordingly*/
void sort_the_list(char **best_teams);

#endif