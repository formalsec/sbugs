#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "team.h"

int hash(char * name) {
    int i, value;
    int len = strlen(name);
    value = 0;
    for(i = 0; i < len; i++){
        value = value + name[i];
    }
    value = value * 5;
    value = value % HASH_SIZE;
	return value;
}

void swap(int i, int j){
    team * t = bestTeams[i];
    bestTeams[i] = bestTeams[j];
    bestTeams[j] = t;
}
int part(int low, int high){
    int j;
    int i = (low - 1);

    for(j = low; j < high; j++){
        if(strcmp(bestTeams[j]->name,bestTeams[high]->name) < 0){
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return (i + 1);
}

void quicksortWins(int low, int high){
    if(low < high){
        int p = part(low, high);
        quicksortWins(low, p-1);
        quicksortWins(p+1, high);
    }
}

void removebestTeam(team * t){
    int i, j;
    if(teamsSize > 0 && bestTeams[0]->wins == t->wins){
        for(i = 0; i < teamsSize; i++){
            if(bestTeams[i] == t){
                break;
            }
        }
        for(j = i; j < (teamsSize - 1); j++){
            bestTeams[j] = bestTeams[j + 1];
        }
        t->wins--;
        teamsSize--;
        bestTeams = can_fail_realloc(bestTeams, sizeof(team *) * teamsSize);
    }
}

int inbestTeams(team *t){
    int i;
    for(i = 0; i < teamsSize; i++){
        if(t == bestTeams[i]) return 1;
    }
    return 0;
}

void addbestTeam(team * t){
    if(teamsSize == 0){
        teamsSize++;
        bestTeams = can_fail_realloc(bestTeams, sizeof(team *) * teamsSize);
        bestTeams[0] = t;
    }else{
        if(inbestTeams(t) == 1){
            teamsSize = 1;
            bestTeams = can_fail_realloc(bestTeams, sizeof(team *) * teamsSize);
            bestTeams[0] = t;
        } else if(inbestTeams(t) == 0 && t->wins == bestTeams[0]->wins){
            teamsSize++;
            bestTeams = can_fail_realloc(bestTeams, sizeof(team *) * teamsSize);
            bestTeams[teamsSize - 1] = t;
        }
    }
}

team * alloct(char * name){
    team * test = can_fail_malloc(sizeof(team));
    test->name = can_fail_malloc(strlen(name) + 1);

    strcpy(test->name, name);
    test->wins = 0;
    test->next = NULL;
    return test;
}

tent * htTeam_create(){
    int i;
    tent * ht = can_fail_malloc(sizeof(tent) * 1);
    teamsSize = 0;

    ht->entries = can_fail_malloc(sizeof(team *) * HASH_SIZE);

    for(i = 0; i < HASH_SIZE; i++){
        ht->entries[i] = NULL;
    }

    return ht;
}


team  * htTeam_search(tent * ht_t, char * name){
    int index;
    team * temp;
    team * p;

    index = hash(name);
    temp = ht_t->entries[index];

    if(temp == NULL){
        return NULL;
    }

    while(temp != NULL){
        if(strcmp(temp->name, name) == 0) return temp; /* Exists*/
        p = temp;
        temp = p->next;
    }
    return NULL;
}

int htTeam_insert(tent * ht_t, char * name){
    int index;
    team * test;
    team * p;

    index = hash(name);
    test = ht_t->entries[index];

    if(test == NULL){
        ht_t->entries[index] = alloct(name);
        addbestTeam(ht_t->entries[index]);
        return 1;
    }

    while(test != NULL){
        if(strcmp(test->name, name) == 0) return 0; /* Return error because it is no good  GAME ALREADY EXISTS*/
        p = test;
        test = p->next;
    }

    p->next = alloct(name);
    addbestTeam(p->next);
    return 1;

}

void presentOrdered(int debug){
    int i;
    if(teamsSize > 0){
        quicksortWins(0, teamsSize - 1);
        printf("%d Melhores %d\n", debug, bestTeams[0]->wins);
        for(i = 0; i < teamsSize; i++){
            printf("%d * %s\n", debug, bestTeams[i]->name);
        }
        return;
        if(teamsSize == 0) printf("%d * %s\n", debug, bestTeams[0]->name);
    }
    
}
