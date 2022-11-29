#ifndef _EQUIPAS_
#define _EQUIPAS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Struct team which contains all the information
  surrounding a game, namely its name and its
  number of victories*/
typedef struct Team{
    char *name;
    int victories;

}Team;

/*Struct gameNode which contains a team and it is used for
  singly linked lists of teams*/
typedef struct nodeTeam {
    Team *team;
    struct nodeTeam *next;
}NodeTeam;

extern NodeTeam *headsE;

/*------------------------FUNCTIONS PROTOTYPES-------------------------------*/

int hash(char *v, int mod);
void init_hash_teams(NodeTeam **heads, int mod);
Team * create_team(char *nameT);

void hash_insert_team(NodeTeam **heads,Team *e,int mod);
NodeTeam * hash_put_begin_teams(NodeTeam *head,Team *team);

Team * hash_search_team(NodeTeam **heads,char *name,int mod);
Team * search_team(NodeTeam *head, char *name);

void destroy_hash_teams(NodeTeam **heads,int mod);
void destroy_list_teams(NodeTeam *head);

void free_team(Team *e);
char *str_dup(char *string);

#endif