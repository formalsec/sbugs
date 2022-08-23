#ifndef TEAMS_H
#define TEAMS_H
#define MAXCHAR 1024
#define less(A,B) (strcmp(A,B) < 0)
#define exch(A,B) {team * t = A; A = B; B = t;}

typedef struct team_node {
	struct team_node * next;
	struct team_node * previous;
	char * name;
	int wins;
} team;


typedef struct {
	team * head;
	team * tail;
} Teams;

typedef struct {
	team ** slots;
	int size;
	int cap;
} HashTeams;


Teams * init_Tlist();
void destroy_Tlist(Teams * linkedlist);
void free_team_node(team * team_node);

HashTeams * init_HTtable(int size);
void destroy_HTtable(HashTeams * hashtable);

void new_team(Teams * teams, HashTeams * hashtable, int NL);
team * alloc_team(char team_name[MAXCHAR]);
void add_last_team(Teams * teams, team * new_team);
void add_team_to_hash(team * team_node, HashTeams * hashtable);

void lookfor_team(HashTeams * hashtable, int NL);
team * hash_lookfor_team(HashTeams * hashtable, char * name);

void remove_team_win(HashTeams * hashtable_teams, char * winner);
void add_team_win(HashTeams * hashtable_teams, char * new_winner);

void find_most_winning_teams(Teams * teams_list, int NL);

void clean_winning_teams(team ** W_teams, int i);
void print_winning_teams(team ** W_teams, int i, int NL, int max_wins);
void add_winning_team(team ** W_teams, team * team_x, int i);

void quicksort_teams(team ** W_teams, int l, int r);
int partition(team ** W_teams, int l, int r);

void resize_hashtable_teams(HashTeams * hashtable);
void init_new_team_slots(team ** new_slots, int new_cap);
void rehash_teams(HashTeams * hashtable, team ** new_slots, team ** old_slots, int new_cap);

#endif