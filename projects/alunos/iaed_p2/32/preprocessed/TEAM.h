#ifndef TEAM_H
#define TEAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_STR 1024
#define M 256 /*Numero de caracteres ASCII*/


/*Estrutura que representa uma equipa*/
typedef struct team{
  char* name;
  int wins;
}*Team;

/*Estrutura usada para a lista ligada auxiliar para guardar as equipas
com mais vitorias*/
typedef struct team_name{
  Team team;
  struct team_name* next;
} *TeamsList;

/*
Estrutura usada para guardar as equipas na hashtable*/
typedef struct node{
  Team team;
  struct node *next;
} *link;


link* t_heads;

/*Lista ligada auxiliar para guardaras equipas com mais vitorias*/
TeamsList teams_list, teams_list_tail;



/*::::::::::::::::::::::FUNCOES PRINCIPAIS::::::::::::::::::::*/


void NewTeam(int line);
void SearchTeam(int line);
void MaxWins(int line);

/*:::::::::::::::::::::AUXILIARES HASHTABLE:::::::::::::::::::::*/

void TeamInit();
int hash_team(char* name);
link insertHashTeam(char* name, link head);
link searchHashTeam(char* name, link head);
void freeTeamHash();
void free_list(link head);

/*:::::::::::::::::::AUXILIARES LISTA LIGADA AUXILIAR:::::::::::::::::*/

link newTeamLink(char* name);
void increaseWins(char* name);
void decreaseWins(char* name);

void TeamListInit();
void freeTeamList(TeamsList t);
TeamsList newTeamIndex(Team team);
void insertTeamList(Team team);



#endif








/*void NewTeam(int line);
void SearchTeam(int line);
void MaxWins(int line);

void TreeInit();
node search_team(node p, char* name);
node insert(node p, char* team_name);
void increaseWins(char* name);
void decreaseWins(char* name);
char** number(node p, char** names);
void free_tree(node p);
void print_tree(node p);
*/
