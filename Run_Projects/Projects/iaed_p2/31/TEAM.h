#ifndef TEAM_H
#define TEAM_H

/* Library. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* The dimension of hash. */
#define HASH_SIZE 15


/* Structure of a team. */
typedef struct stru_team{
    char *name;
    int vitories;
    struct stru_team *next;
} team;


/* Auxiliar functions of teams. */

team ** init_team(team ** team);

int hash(char * name);

team * create_team(char * name);

team * push_team(char * name, team * last);

team * pop_team(team * head);

team * destroy_index_team(team * team_index);

team ** destroy_full_team(team ** team_hash);

team * get_team(team ** team_hash, char * name);

void list_put_team(team ** team, char * name, int NL);

team * add_order_team(team * order_team, char * name);

#endif