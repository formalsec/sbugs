#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "teams.h"

/******************************************************
*-------------------AUXILIAR FUNCTIONS----------------*
*----------------------DECLARATION--------------------*
******************************************************/

/*Initializes the teams hash table*/
hash_table_teams *create_ht_team(int size){
	
	int i;
	hash_table_teams *new;
	
	if(size < 1)
		return NULL;

	if((new = can_fail_malloc(sizeof(hash_table_teams))) == NULL)
		return NULL;

	if((new->table = can_fail_malloc(sizeof(list_teams*)*size)) == NULL)
		return NULL;

	for(i = 0; i < size; i++)
		new->table[i] = NULL;

	new->size = size;
	
	return new;
}

int hash_teams(hash_table_teams *team_ht, char *v){

    int h, a = 31415, b = 27183;

    /* iterates through the letters of the name and uses 
    a hashing algorithm to find a position for team */
    for (h = 0; *v != '\0'; v++, a = a*b % (team_ht->size - 1)){
        h = (a*h + *v) % team_ht->size;
	}
	
    return h;
}

/*Inserts a team in the hash table*/
void insertBegin_teams(hash_table_teams *team_ht, char *v){

	list_teams *new;
	
	int h = hash_teams(team_ht, v);

	new = can_fail_malloc(sizeof(list_teams));
	new->name = can_fail_malloc(sizeof(char)*(strlen(v)+1));

	new->victories = 0;
	strcpy(new->name, v);

	new->next = team_ht->table[h];
	team_ht->table[h] = new;
}

/*Searches for a team in the hash table, if it finds it returns the team, if not returns NULL*/
list_teams *search_team_aux(hash_table_teams *team_ht, char *v){
	
	list_teams *list;
	int h = hash_teams(team_ht, v);

	for(list = team_ht -> table[h]; list != NULL; list = list->next){
		if(strcmp(v, list->name) == 0)
			return list;
	}

	return NULL;
}

/*Compares two names and return 0 if they are equal, negative if the 
ASCII value of the first unmatched characterr is less than second and 
if the ASCII value of the first unmatched character ir greater than 
second*/
int compare_names(list_names *y, list_names *z){

	return strcmp(y->team_name, z->team_name);
}

/*Inserts a team name in the list in alphabetical order*/
list_names *insert_name_list(list_names *head_lst_names, char *name){

	list_names *y = can_fail_malloc(sizeof(list_names));

	y->team_name = name;
	y->next = NULL;

	if(head_lst_names == NULL || compare_names(y, head_lst_names) < 0){
		y->next = head_lst_names;
		return y;
	}
	
	else{

		list_names *z = head_lst_names;

		while(z->next != NULL && compare_names(y, z->next) >= 0){
			z = z->next;
		}

		y->next = z->next;
		z->next = y;
		return head_lst_names;
	}
} 

/*Prints all the teams names of the list*/
void print_list_names(list_names *head_lst_names, int NL){

	list_names *t, *lst_names_aux = head_lst_names;

	for(t = head_lst_names; t != NULL; t = t->next)
		printf("%d * %s\n", NL, t->team_name);
	
	while(lst_names_aux != NULL){
		
		lst_names_aux = head_lst_names->next;
		free(head_lst_names);
		head_lst_names = lst_names_aux;
	}
}