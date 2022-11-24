#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "game.h"



ent * htGame_create(){
    /* Create hastable for games */
    int i;
    ent * ht = can_fail_malloc(sizeof(ent) * 1);
    ordListsize = 0;
    

    ht->entries = can_fail_malloc(sizeof(game *) * HASH_SIZE);

    for(i = 0; i < HASH_SIZE; i++){
        ht->entries[i] = NULL;
    }

    return ht;
}

void printGames(int num){
    /* Print games in order */
    int i;
    for(i = ordListsize - 1; i >= 0; i--){
        printf("%d %s %s %s %d %d\n", num, ordGameList[i].name, ordGameList[i].team[0]->name, ordGameList[i].team[1]->name, ordGameList[i].score[0], ordGameList[i].score[1]);
    }
}

game * htGame_search(ent * ht_g, char * name){
    /* Search for a game in the hashtable */
    int index;
    game * test;
    game * p;

    index = hash(name);
    test = ht_g->entries[index];
    if(test == NULL) return NULL;

    while(test != NULL){
        if(strcmp(test->name, name) == 0 && test->score[0] != -1){
            return test;
        }
        
        p = test;
        test = p->next;
    }
    return NULL;
} 


game * alloc(char * name, team * team1, team * team2, int score[2]){
    /* Allocate space for game */
    game * test = can_fail_malloc(sizeof(game));
    test->name = can_fail_malloc(strlen(name) + 1);

    strcpy(test->name, name);
    test->score[0] = score[0];
    test->score[1] = score[1];
    test->team[0] = team1;
    test->team[1] = team2;

    test->next = NULL;

    return test;
    
}

void ordListadd(game  g){
    /* Add game to the ordered List */
    int i;
    ordListsize++;
    ordGameList = can_fail_realloc(ordGameList, sizeof(game) * ordListsize);
    if(ordListsize > 1){
        for(i = (ordListsize - 1); i > 0; i--){
            ordGameList[i] = ordGameList[i - 1];
        }
    }
    ordGameList[0] = g;
}

void ordListremove(game g){
    /* Remove game from ordered List */
    int i, j;
    for(i = 0; i < ordListsize; i++){
        if(strcmp(ordGameList[i].name ,g.name) == 0){
            if(!(i == ordListsize - 1)){
                for(j = i; j < (ordListsize - 1); j++){
                    ordGameList[j] = ordGameList[j + 1];
                }
            }
            ordListsize--;
            ordGameList = can_fail_realloc(ordGameList, sizeof(game) * ordListsize);
            break;
        }
    }
}



void htGame_change(game * g, int score1, int score2){
    /* Change scores in the hashtable and in the ordered List*/
    int i;
    if(g->score[0] > g->score[1] && score1 < score2){
        removebestTeam(g->team[0]);
        g->team[1]->wins++;
        addbestTeam(g->team[1]);
    } else if(g->score[0] == g->score[1] && score1 < score2){
        g->team[1]->wins++;
        addbestTeam(g->team[1]);
    } else if(g->score[0] < g->score[1] && score1 > score2){
        removebestTeam(g->team[1]);
        g->team[0]->wins++;
        addbestTeam(g->team[0]);
    } else if(g->score[0] == g->score[1] && score1 > score2){
        g->team[0]->wins++;
        addbestTeam(g->team[0]);
    } else if(g->score[0] > g->score[1] && score1 == score2){
        removebestTeam(g->team[0]);
    } else if(g->score[0] < g->score[1] && score1 == score2){
        removebestTeam(g->team[1]);
    }
    g->score[0] = score1;
    g->score[1] = score2;
    for(i = 0; i < ordListsize; i++){
        if(strcmp(ordGameList[i].name, g->name) == 0){
            ordGameList[i].score[0] = score1;
            ordGameList[i].score[1] = score2;
            break;
        }
    }

}



int htGame_insert(ent * ht_g, tent * ht_t, char * name, char * team1, char * team2, int score[2]){
    int index;
    /* Put game in the game hashtable */
    game * test;
    game * p;
    game * check;
    team * t1;
    team * t2;

    check = htGame_search(ht_g, name);
    t1 = htTeam_search(ht_t, team1);
    t2 = htTeam_search(ht_t, team2);
    if(check != NULL) return 0; /* Return error because GAME ALREADY EXISTS*/
    if((!t1) || (!t2)) return -1; /* team doesnt exist */

    index = hash(name);
    test = ht_g->entries[index];

    if (test == NULL){
        ht_g->entries[index] = alloc(name, t1, t2, score);
        ordListadd(*ht_g->entries[index]);
        if(score[0] > score[1]){
            t1->wins++;
            addbestTeam(t1);
            }
        if(score[0] < score[1]) {
            t2->wins++;
            addbestTeam(t2);
            }
        return 1;
    }

    while(test != NULL && test->name != NULL){
        p = test;
        test = p->next;
    }

    p->next = alloc(name, t1, t2, score);
    ordListadd(*p->next);
    if(score[0] > score[1]) {
        t1->wins++;
        addbestTeam(t1);
        }
    if(score[0] < score[1]) {
        t2->wins++;
        addbestTeam(t2);
        }
    return 1;

}


void htGame_delete(ent * ht_g, char * name){
    /* Delete game from the game hashtable */
    int index;

    game * test;
    game * p;
    index = hash(name);
    
    if(strcmp(ht_g->entries[index]->name, name) == 0){
        test = ht_g->entries[index]; 
        if(test->score[0] > test->score[1]) {
            removebestTeam(test->team[0]);
        }
        if(test->score[0] < test->score[1]) {
            removebestTeam(test->team[1]);
        }
        ordListremove(*test);
        ht_g->entries[index] = ht_g->entries[index]->next;
        free(test->name);
        free(test);
        return;
    }
    for(test = ht_g->entries[index]; test->next != NULL; test = test->next){
        p = test->next;
        if(strcmp(p->name, name) == 0){
            test->next = p->next;
            if(p->score[0] > p->score[1]) {
                removebestTeam(p->team[0]);
            }
            if(p->score[0] < p->score[1]) {
                removebestTeam(p->team[1]);
            }
            ordListremove(*p);
            free(p->name);
            free(p);
            break;
        }
    }
}
