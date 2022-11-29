#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "teams.h"
#include "games.h"
#define MAX_STR_LEN 1024 /*strings maximum length*/


/*--------------Functions to manipulate team structure--------------*/

/*Function to create a new team with the given parameters*/
team *create_team(char * name){
    team * new_team;
    new_team = can_fail_malloc(sizeof(team));
    new_team -> name = can_fail_malloc(sizeof(char) *(strlen(name) + 1));
    strcpy(new_team -> name, name);
    new_team -> nr_wins = 0;
    new_team -> next = NULL;
    return new_team;
}

/*--------------Functions to manipulate teams hash table--------------*/

/*Function to initialize the team hash table*/
void table_t_init(team **team_t, long int m){
    long int i;
    for (i = 0; i < m; i++)
        *(team_t + i) = NULL;
}

/*Function that adds a team to the team hash table*/
team **add_team_to_table(team **teams_t, team *t, long int *max_len){
    long int m = *(max_len + 2), hash;
    hash = table_hash(t -> name, m);
    while(*(teams_t + hash) != NULL)
        hash = (hash + 1) % m;
    *(teams_t + hash) = t;
    (*(max_len + 3))++;
    /*if the number of elements is bigger then half the size of the
    table, expand it*/
    if (*(max_len + 3) > (m / 2))
        return expand_t(teams_t, max_len);
    else
        return teams_t;
}

/*Function to expand the size of the team hash table */
team **expand_t(team **teams_tab,long int *max_len){
    long int i, old_m;
    team **new_tab = can_fail_malloc(sizeof(link) * (*(max_len + 2)) * 2);
    old_m = *(max_len + 2);
    (*(max_len + 2)) = (*(max_len + 2)) * 2;
    table_t_init(new_tab, *(max_len + 2));
    for (i = 0; i < old_m; i++)
        if(*(teams_tab + i) != NULL){
            add_team_to_table(new_tab, *(teams_tab + i), max_len);
            (*(max_len + 3))--;
        }
    free(teams_tab);
    return new_tab;
}

/*Function that search for a team with the given name and returns
the pointer to the team*/
team *search_t(char *team_name, team **teams_tab, long int m){
    long int i = table_hash(team_name, m);
    while (*(teams_tab + i) != NULL){
        if(strcmp(team_name, (*(teams_tab + i)) -> name) == 0)
            return *(teams_tab + i);
        else
            i = (i + 1) % m;
    }
    return NULL;
}

/*Function that destroys the team hash table*/
void destroy_team_st(team *last_team){
    team * t = last_team, *aux;
    while(t != NULL){
        aux = t -> next;
        free(t -> name);
        free(t);
        t = aux;
    }
}
