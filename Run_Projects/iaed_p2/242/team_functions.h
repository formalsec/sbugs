#ifndef TEAM_FUNCTIONS_H
#define TEAM_FUNCTIONS_H

/****************************************/
/*	 Prototipo das funcoes das equipas	*/
/****************************************/

void init_hash_table_team(team** hash_table_team);
void HTinsert_team(char* t_name, team** hash_table_team);
void cmd_A(char* t_name, int NL, team** hash_table_team);
void cmd_P(char* t_name, int NL, team** hash_table_team);
void print_max(team** max_teams, int NL);
void cmd_g(team** max_teams, int NL, team** hash_t_team);
void FREEnode_team(team* t);
void destroy_teams_lst(team** list_t);
void destroy_teams(team** hash_table_team);
team* new_team(char* new_name, int n_wins);
team* insertBeginList_team(team* head, char *t_name, int wins);
team* hash_table_lookup_team(char* name, team** hash_table_team);
team* insert_alpha(team* head, char *t_name, int wins);
team* pop_team(team* head);
int get_max(team** hash_t);
int hash(char *name);

#endif