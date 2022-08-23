#ifndef TEAMS
#define TEAMS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trees.h"
#define MAX_TEAM_NAME 1024

typedef struct {
    char *name;
    short victs;
} team;

void del_team(void *);
int cmp_team_str(void *, void *);
int cmp_teams_nme(void *, void *);
int cmp_teams_vct(void *, void *);
void print_team(team *, int);
t_node *change_victs(t_node *, team *, int);

#endif