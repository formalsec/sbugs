#include "utils.h"

typedef struct Teams {
    char team_name[MAX_BUFF];
    int matches_won;
    struct Teams * next;
} Teams;

int get_list_size(Teams * head);
Teams * add_team_to_list(Teams ** head, char *name);
Teams * delete_team_from_list(Teams ** head, char* t_name);
Teams * add_team_highest(Teams ** teams_highest, Teams ** teams, int highest_won);
Teams * increment_matches_won(Teams ** head, char* name);
Teams * decrement_matches_won(Teams ** head, char* name);
bool team_exists(Teams ** head, char* name);
int max_won(Teams ** head);
void print_matches_won(Teams ** head, char* name);
void print_team_list(int nl, Teams * head);
void free_teams(Teams * head);
void sort_teams_alpha(Teams ** head);