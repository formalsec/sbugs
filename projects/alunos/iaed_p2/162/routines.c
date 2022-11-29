#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"


/* Adds win for team with bigger score */
void AddWin(game *game_v, int score1, int score2){
    if (score1 > score2) {
        ++game_v->team1->wins;
    }
    if (score2 > score1) {
        ++game_v->team2->wins;
    }
}


void __a__(teamstable *table_t, gametable *table_g, int NL){
    char name[MAXNAME], team1_c[MAXNAME], team2_c[MAXNAME];
    int score1, score2;
    game *game_v;
    team *team1,*team2;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",name, team1_c, team2_c, &score1, &score2);
    if(SearchGame(name, table_g) != NULL){
        printf("%d Jogo existente.\n", NL);
        return;
    }
    team1 = SearchTeam(team1_c, table_t);
    team2 = SearchTeam(team2_c, table_t);
    if(team1 == NULL || team2 == NULL){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    /* allocate memory for game structure and name */
    game_v = (game*)can_fail_malloc(sizeof(game));
    game_v->name = (char*)can_fail_malloc(sizeof(char)*(strlen(name) + 1));

    strcpy(game_v->name, name);
    game_v->team1 = team1;
    game_v->team2 = team2;
    game_v->score1 = score1;
    game_v->score2 = score2;
    game_v->id = table_g->last_idg;

    InsertGame(game_v, table_g);
    AddWin(game_v, score1, score2);

    if(table_g->n_el >= (table_g->size/2)){
        *table_g = *ExpandGameTable(table_g);
    }
}


void __A__(teamstable* table_t, int NL){
    team *team_v;
    char name[MAXNAME];
    scanf(" %[^:\n]", name);

    if(SearchTeam(name, table_t) != NULL){
        printf("%d Equipa existente.\n", NL);
        return;
    }
    /* allocate memory for team structure and name */
    team_v = (team*) can_fail_malloc(sizeof(team));
    team_v->name = (char*) can_fail_malloc(sizeof(char)*(strlen(name)+1));

    strcpy(team_v->name, name);
    team_v->wins = 0;

    InsertTeam(team_v, table_t);

    if(table_t->n_el >= table_t->size/2){
        *table_t = *ExpandTeamsTable(table_t);
    }
}

/* quicksort auxiliar function */
int partition(game **game_array, int left, int right){
    int i = left-1;
    int j = right;
    game *aux, *pivot = game_array[right];
    while( i < j ){
        while(game_array[++i]->id < pivot->id);
        while(game_array[--j]->id > pivot->id){
            if(j == left){
                break;
            }
        }
        if(i < j){
            aux = game_array[i];
            game_array[i] = game_array[j];
            game_array[j] = aux;
        }
    }
    aux = game_array[i];
    game_array[i] = game_array[right];
    game_array[right] = aux;
    return i;
}
/* sorting algorithm sorts by game id */
void quicksort(game ** game_array, int left,int right){
    int i;
    if(right <= left){
        return;
    }
    i = partition(game_array, left, right);
    quicksort(game_array, left, i-1);
    quicksort(game_array, i+1, right);
}

void __l__(gametable *table_g, int NL){
    game **game_array;
    int i, j = 0;
    game_array = (game**) can_fail_malloc(sizeof(game*)*table_g->size/2);
    for(i = 0; i < table_g->size; i++){
        if(table_g->table[i] != NULL){
            game_array[j] = table_g->table[i];
            ++j;
        }
    }
    quicksort(game_array, 0, j-1);
    for(i = 0; i < j; i++){
        printf("%d %s %s %s %d %d\n", NL, game_array[i]->name, game_array[i]->team1->name,
        game_array[i]->team2->name, game_array[i]->score1, game_array[i]->score2);
    }
    free(game_array);
}

void __p__(gametable *table_g, int NL){
    game *game_v;
    char name[MAXNAME];
    scanf(" %[^:\n]", name);
    game_v = SearchGame(name, table_g);
    if(game_v == NULL){
        printf("%d Jogo inexistente.\n", NL);
    }
    else{
        printf("%d %s %s %s %d %d\n", NL, game_v->name, game_v->team1->name,
        game_v->team2->name,game_v->score1,game_v->score2);
    }
}

void __P__(teamstable *table_t, int NL){
    team *team_v;
    char name[MAXNAME];
    scanf(" %[^:\n]", name);
    team_v = SearchTeam(name, table_t);
    if(team_v == NULL){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    printf("%d %s %d\n", NL, team_v->name, team_v->wins);
}

void __r__(gametable *table_g, int NL){
    game *game_v;
    char name[MAXNAME];
    scanf(" %[^:\n]", name);
    game_v = SearchGame(name, table_g);
    if(game_v == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /* subtract win in team that won the game */
    if(game_v->score1 > game_v->score2){
        --game_v->team1->wins;
    }
    if(game_v->score2 > game_v->score1){
        --game_v->team2->wins;
    }
    DeleteGame(game_v, table_g);
    --table_g->n_el;
}

void __s__(gametable *table_g, int NL){
    game *game_v;
    char name[MAXNAME];
    int score1, score2;
    scanf(" %[^:\n]:%d:%d", name, &score1, &score2);
    game_v = SearchGame(name, table_g);
    if(game_v == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /* subtract win if winner changes */
    if(game_v->score1 > game_v->score2){
        --game_v->team1->wins;
    }
    if(game_v->score2 > game_v->score1){
        --game_v->team2->wins;
    }
    game_v->score1 = score1;
    game_v->score2 = score2;
    AddWin(game_v, score1, score2);
}


int cmpstr(const void *a, const void *b){
    const char **aa = (const char **)a;
    const char **bb = (const char **)b;
    return strcmp(*aa, *bb);
}

void __g__(teamstable *table_t, int NL){
    int i, n_winners = 0, n_wins = 0;
    char **teamptr_array;
    teamptr_array = (char**) can_fail_malloc(sizeof(char*)*(table_t->size/2+1));
    for(i = 0; i < table_t->size; i++){
        if(table_t->table[i] != NULL){
            /* if n_wins changes restart counting */
            if(table_t->table[i]->wins > n_wins){
                n_wins = table_t->table[i]->wins;
                n_winners = 0;
            }
            /* add up all winners and insert in teams */
            if(table_t->table[i]->wins == n_wins){
                teamptr_array[n_winners] = table_t->table[i]->name;
                ++n_winners;
            }
        }
    }
    qsort(teamptr_array, n_winners, sizeof(char*), cmpstr);
    if(n_winners > 0){
        printf("%d Melhores %d\n", NL, n_wins);
    }
    for(i = 0; i < n_winners; i++){
        printf("%d * %s\n", NL, teamptr_array[i]);
    }
    free(teamptr_array);
}

void __x__(teamstable *table_t, gametable *table_g){
    int i;
    for(i = 0; i < table_t->size; i++){
        if(table_t->table[i] != NULL){
            free(table_t->table[i]->name);
            free(table_t->table[i]);
        }
    }
    free(table_t->table);
    for(i = 0; i < table_g->size; i++){
        if(table_g->table[i] != NULL){
            free(table_g->table[i]->name);
            free(table_g->table[i]);
        }
    }
    free(table_g->table);
}
