#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "teams.h"

/* Frees team and string associated                                           */
void del_team(void *t){
    free(((team*) t)->name);
    free(t);
    return;
}

/* Compares string with a pointer to a team, alphabetically                   */
int cmp_team_str(void *str, void *t){
    return strcmp((char*) str, ((team*) t)->name);
}

/* Compares two teams, alphabetically                                         */
int cmp_teams_nme(void *a, void *b){
    return strcmp(((team*) a)->name, ((team*) b)->name);
}

/* Compares two teams by their score, if same then alphabetically             */
int cmp_teams_vct(void *a, void *b){
    if(((team*) a)->victs != ((team*) b)->victs){
        return ((team*) a)->victs - ((team*) b)->victs;
    }
    return strcmp(((team*) a)->name, ((team*) b)->name);
}

/*Prints given team with input input line                                     */
void print_team(team *t, int in_line){
    printf("%d %s %d\n", in_line, t->name, t->victs);
    return;
}

/* Removes given node from team tree, updates score and then inserts back     */
t_node *change_victs(t_node *root, team *t, int dif){
    root = tree_remove(root, cmp_teams_vct, t);
    t->victs += dif;
    return tree_insert(root, cmp_teams_vct, t);
}