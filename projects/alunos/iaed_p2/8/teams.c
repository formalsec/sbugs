#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myLib.h"
#include "competition.h"
#include "game.h"
#include "teams.h"
#include "team.h"



unsigned long hashCode(char* str) {
    unsigned long i = 0;
    int j;
    for (j=0; str[j]; j++)
        i += str[j];
    return i % MAX_TEAMS;
}

/* Cretes a TeamsDataItem */
TeamsDataItem * teams_create_item(Team *t) {
    
    extern char* strdup(const char*);
    /* Creates a pointer to a new hash table item */
    TeamsDataItem * item = (TeamsDataItem*) can_fail_malloc (sizeof(TeamsDataItem));
    EXIT_IF_ERROR("teams_create_item: can_fail_malloc");

    item->key  = strdup(t->name);
    item->team = t;
    return item;
}

/*Creates new teams*/
Teams * teams_new(){
    
    Teams * tt = (Teams*) can_fail_malloc(sizeof(Teams));
    EXIT_IF_ERROR("teams_new: can_fail_malloc 1");

    tt->count = 0;
    tt->items = (TeamsDataItem**) can_fail_calloc(MAX_TEAMS, sizeof(TeamsDataItem*));
    EXIT_IF_ERROR("teams_new: can_fail_malloc 2");

    return tt;
}


void teams_free_item(TeamsDataItem * item) {

    /* Frees an item */
    free(item->key);
    team_free(item->team);
    free(item);
}

void teams_free(Teams *tt) {
    int i;
    ERROR_IF_NULL(tt, "teams_free", exit(EXIT_FAILURE));


    /* Percorremos o hashArray para fazer free dos teams */
    for (i=0; i<MAX_TEAMS; i++) {
        if ( tt->items[i]!=NULL )
            teams_free_item(tt->items[i]);
    }

    /* free do hashArray */
    free(tt->items);

    /* free do teams */
    free(tt);
}

/* Adds team to teams */
void teams_add(Teams *tt, Team * t) {

    int hashIndex;
    TeamsDataItem * di;

    ERROR_IF_NULL(tt, "teams_add", exit(EXIT_FAILURE));

    if (tt->count == MAX_TEAMS) {
        printf("Hash table is full");
        exit(1);
    }

    hashIndex = hashCode(t->name);
    di        = teams_create_item(t);

    while(tt->items[hashIndex]!=NULL) {
        /*go to next cell*/
        ++hashIndex;
        /*wrap around the table*/
        hashIndex = hashIndex % MAX_TEAMS;
    }

    tt->items[hashIndex] = di;
    tt->count++;
}


Team * teams_get_team(Teams *tt, char *team_name) {
    int hashIndex;
    int steps;
    TeamsDataItem * di;

    ERROR_IF_NULL(tt, "teams_get_team", exit(EXIT_FAILURE));

    hashIndex = hashCode(team_name);
    di = tt->items[hashIndex];
    steps = 1;

    while ( steps!=MAX_TEAMS && di!=NULL && strcmp(team_name, di->key) !=0 ) {
        hashIndex++;
        steps++;
        di = tt->items[hashIndex];
    }

    if (di==NULL)
        return NULL;
    else
        return di->team;
}
