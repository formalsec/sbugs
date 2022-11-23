#ifndef TEAM_H
#define TEAM_H
typedef struct node{        /* lista de equipas */
    char *name;
    struct node *next;
}*link;

void add_team(link *teams,char buffer[1024]);
void print_teams(link* teams);
int find(link *teams, char buffer[1024],int contador);
int existing_team(link *hashtable,char buffer[1024]);
void free_list(link *teams);
void free_node(link n);
#endif
