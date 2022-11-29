#ifndef TEAM_H
#define TEAM_H

/*  STRUCTS  */
typedef struct team{
	char *name;
	int victories;
} Team;

typedef struct team_node{
	Team t;
	struct team_node *next;
} Team_node;

typedef struct team_list_node{
	Team_node* t;
	struct team_list_node* next;
} Team_list_node;


/* MAIN FUNCTIONS */
Team_list_node* __A__(int nl, Team_node** head, Team_list_node* team_list);
void __P__(int nl, Team_node** head);
void __g__(int nl, int* max_victories, Team_list_node* team_list);

/* AUX FUNCTIONS */
Team_list_node* new_team_list_node(Team_node* t);
Team_list_node* insert_team_list(Team_node* team, Team_list_node* head);

#endif