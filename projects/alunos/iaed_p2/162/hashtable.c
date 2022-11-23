#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int Hash(char *name, int size){
    int index = 0, a = 31415, b = 27183;
    while(*name != '\0'){
        a = a*b % (size-1);
        index = (a*index + *name) % size;
        name++;
    }
    return index;
}

gametable InitGameTable(int size){
    int i;
    gametable table_g;

    table_g.n_el = 0;
    table_g.last_idg = 0;
    table_g.size = size;
    table_g.table = (game**) can_fail_malloc(sizeof(game)*table_g.size);

    for(i = 0; i < table_g.size; i++){
        table_g.table[i]= NULL;
    }
    return table_g;
}

void InsertGame(game *game_v, gametable *table_g){
    int i;
    i = Hash(game_v->name, table_g->size);
    while(table_g->table[i] != NULL){
        i = (i+1) % table_g->size;
    }

    table_g->table[i] = game_v;
    ++table_g->last_idg;
    ++table_g->n_el;
}

gametable* ExpandGameTable(gametable *table_g){
    int i, idg = table_g->last_idg;
    game **old_table = table_g->table;

    *table_g = InitGameTable(2*table_g->size);

    for(i = 0; i < table_g->size/2; i++){
        if(old_table[i] != NULL){
            InsertGame(old_table[i], table_g);
        }
    }
    table_g->last_idg = idg;
    free(old_table);
    return table_g;
}

game* SearchGame(char *name, gametable *table_g){
    int i = Hash(name, table_g->size);
    while(table_g->table[i] != NULL){
        if((strcmp(table_g->table[i]->name, name)) == 0){
            return table_g->table[i];
        }
        else{
            i = (i+1) % (table_g->size);
        }
    }
    return NULL;
}

void DeleteGame(game *game_v, gametable *table_g){
    int j, i = Hash(game_v->name, table_g->size);
    game* aux1;
    while(table_g->table[i] != NULL){
        if(strcmp(table_g->table[i]->name, game_v->name) == 0){
            break;
        }
        else{
            i = (i+1) % table_g->size;
        }
    }
    if(table_g->table[i] == NULL){
        return;
    }
    free(table_g->table[i]->name);
    free(table_g->table[i]);

    table_g->table[i] = NULL;
    j = (i+1) % table_g->size;

    /* relocate other elements  */
    while(table_g->table[j] != NULL){
        aux1 = table_g->table[j];
        table_g->table[j] = NULL;
        InsertGame(aux1, table_g);
        j = (j+1) % table_g->size;
        /* Insert Game increment number of elements */
        --table_g->n_el;
    }
}

teamstable InitTeamTable(int size){
    teamstable table_t;
    int i;
    table_t.n_el = 0;
    table_t.size = size;
    table_t.table = (team**) can_fail_malloc(sizeof(team)*table_t.size);
    for(i = 0; i < table_t.size; i++){
        table_t.table[i] = NULL;
    }
    return table_t;
}

void InsertTeam(team *team_p, teamstable *table_t){
    int i = Hash(team_p->name, table_t->size);
    while(table_t->table[i] != NULL){
        i = (i+1) % table_t->size;
    }
    table_t->table[i] = team_p;
    ++table_t->n_el;
}

teamstable* ExpandTeamsTable(teamstable *table_t){
    int i;
    team **old_table = table_t->table;
    *table_t = InitTeamTable(2*table_t->size);
    for(i = 0; i < table_t->size/2; i++){
        if(old_table[i] != NULL){
            InsertTeam(old_table[i],table_t);
        }
    }
    free(old_table);
    return table_t;
}

team* SearchTeam(char *name, teamstable* table_t){
    int i = Hash(name, table_t->size);
    while(table_t->table[i] != NULL){
        if(strcmp(table_t->table[i]->name, name) == 0){
            return table_t->table[i];
        }
        else{
            i = (i+1) % table_t->size;
        }
    }
    return NULL;
}
