#ifndef TSTRUCT_H
#define TSTRUCT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "team.h"

typedef struct t_node
{
    team team;
    struct t_node * left;
    struct t_node * right;
    int height;
}* team_node;

void init_tree(team_node *);
void insert_team(team_node * , team);
team_node search_team(team_node *, char *);
int victories(team_node);
void in_order(team_node *, int, int);
void free_teams(team_node);

#endif