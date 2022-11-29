#ifndef TEAM_H
#define TEAM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct team 
{
    char * name;
    int score;
}*team;

team create_team(char *);
void free_team(team);
void inc_score(team);
void dec_score(team);
void print_team(team, int);

#endif