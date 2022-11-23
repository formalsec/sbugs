#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Teams.h"

/* hash function (the key is the name of the object) */
int hash(char *n, int M){
	int hvalue, a = 31415, b = 27183;

	for (hvalue = 0; *n != '\0'; n++, a = a*b % (M-1)){
		hvalue = (a*hvalue + *n) % M;
	}
	return hvalue;
}

/* inicializes and allocates all the info needed for the game System */
void Init_Teams(TS *ts){
	int i, M;
	ts->HTsize = THTsize;
	M = ts->HTsize;
	ts->headsteams = can_fail_malloc(M*sizeof(struct node)); 
	for (i = 0; i < M; i++) ts->headsteams[i] = NULL;	
	ts->list_teams = NULL;
	ts->Nteams = 0;
}

/*insertes the teams at the top the stack of teams */
pnode insertBeginList(pnode head, pnode new){
	new->next = head;
	return new;
}

/* receves a pointer to the team system */ 
void STinsert(TS *ts, pTeam team){
	int i;
	pnode new = can_fail_malloc(sizeof(struct node));
	new->t = team;
	new->next = NULL;
	i = hash(new->t->name, ts->HTsize);
	ts->headsteams[i] = insertBeginList(ts->headsteams[i], new);
	ts->list_teams = insertBeginList(ts->list_teams, new);
	ts->Nteams += 1;
}

/* Searches for the team in a list */
pTeam searchList(pnode node, char *name){
	for (;node; node = node->next){
		if (strcmp(node->t->name, name) == 0)
			return node->t; 
		else{
			continue;
		}
	}	
	return NULL;
}

/* Searches for the game in the hash table */
pTeam STsearch(char *name, TS *ts){
	int i=hash(name, ts->HTsize);
	return searchList(ts->headsteams[i], name);
}

/* Frees information related to the teams */
void free_node(pnode n){
	free(n->t->name);
	free(n->t);
	free(n);
}

/* frees all the memory remaining related to the teams */
void Deleteallinfo_T(TS *ts){
	while(ts->list_teams){
		pnode aux; 									
		aux = ts->list_teams;
		ts->list_teams = aux->next;
		free_node(aux);
	}
	free(ts->list_teams);
}
