#ifndef TEAMS_H
#define TEAMS_H

/* estrutura de uma equipa */
typedef struct stru_team{
	char * t_name;	/* nome da equipa */
	int n_wins;		/* numero de vitorias */
} team;

/* estrutura de um node de uma lista de equipas duplamente ligada */
typedef struct stru_node_teams{
	team * p_t;								/* ponteiro para uma equipa */
	struct stru_node_teams * next, * prev;	/* ponteiros para o node anterior e seguinte */
} node_dlist_teams;

/* estrutura de uma lista duplamente ligada de equipas */
typedef struct{
	node_dlist_teams * head, * last;	/* ponteiros para o primeiro e ultimo node */
} dlist_teams;

/* delcaracao das funcoes da gestao das estruturas de equipas */
int hashf(char * string);
char * string_alloc(char * string);
team * new_team(char * t_name);
void free_team(team * p_t);
dlist_teams * mk_dlist_teams();
void free_node_dlist_teams(node_dlist_teams * n_dl);
void free_dlist_teams(dlist_teams * dl);
void rm_node_dlist_teams(dlist_teams * dl, node_dlist_teams * n_dl);
node_dlist_teams * addlast_dlist_teams(dlist_teams * dl, team * p_t);
dlist_teams ** init_hasht_teams();
void insert_hasht_t(dlist_teams ** hasht_t, team * p_t);
node_dlist_teams * search_hasht_t(dlist_teams ** hasht_t, char * t_name);
void free_teams(dlist_teams ** hasht_t);

#endif