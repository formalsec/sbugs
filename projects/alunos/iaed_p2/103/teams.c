#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teams.h"

#define MAX_NAME        1024
#define HASH_TABLE_SIZE 1061

/*compare function for qsort*/
int compare(const void *a, const void *b){
    return strcmp(*(char**) a, *(char**) b);
}

/*custom implementation of strdup*/
char* myStrdup(char *string){
    char *new_string = (char*) can_fail_malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(new_string, string);
    return new_string;
}

/*hash function*/
int hash(char *string){
    int h = 0, a = 127;
    for (; *string != '\0'; string++)
        h = (a*h + *string) % HASH_TABLE_SIZE;
    return h;
}

/*initializes the hashtable of teams*/
team_node** makeHashTeams(){
    team_node **hash_table = (team_node**) can_fail_malloc(sizeof(team_node*) * HASH_TABLE_SIZE);
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
    return hash_table;
}

/*inserts a team at the begining of the list*/
team_node* insertBeginList(team_node *head, team *t){
    team_node *new_head = (team_node*) can_fail_malloc(sizeof(team_node));
    new_head->next = head;
    new_head->tptr = t;
    return new_head;
}

/*inserts a team in the hashtable*/
void insertTeam(team_node **hastable, team *t){
    int i = hash(t->name);
    hastable[i] = insertBeginList(hastable[i], t);
}

/*searches a list of teams for a team with a matching name*/
team* searchListTeams(team_node *head, char *name){
    while(head){
        if (!strcmp(head->tptr->name, name)){
            return head->tptr;
        }
        head = head->next;
    }
    return NULL;
}

/*searches for a team in the hastable*/
team* searchHashTeams(team_node **hastable, char *name){
    int i = hash(name);
    return searchListTeams(hastable[i], name);
}

/*frees all memory associated with the teams*/
void freeAllMemoryTeams(team_node **hashteams){
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++){
        team_node *t = hashteams[i];
        while (t){
            team_node *old = t;
            free(t->tptr->name);
            free(t->tptr);
            t = t->next;
            free(old);
        }
    }
    free(hashteams);
}

/*searches for a team and prints its data*/
void searchTeam(team_node **hastable, int line){
    char *name = (char*) can_fail_malloc(sizeof(char) * MAX_NAME);
    team *t;
    scanf(" %[^:\n]", name);
    t = searchHashTeams(hastable, name);
    if (!t){
        printf("%d Equipa inexistente.\n", line);
        free(name);
        return;
    }
    printf("%d %s %d\n", line, name, t->number_of_wins);
    free(name);
}

/*adds a team to the system*/
void addTeam(team_node **hashtable, int line){
    char *name = (char*) can_fail_malloc(sizeof(char) * MAX_NAME);
    team *t;
    scanf(" %[^:\n]", name);
    if (searchHashTeams(hashtable, name)){
        printf("%d Equipa existente.\n", line);
        free(name);
        return;
    }
    t = (team*) can_fail_malloc(sizeof(team));
    t->number_of_wins = 0;
    t->name = myStrdup(name);
    free(name);
    insertTeam(hashtable, t);
}

/*finds the teams that have won the most games, and list them lexicographically*/
void findChampions(team_node **hashtable, int line){
    int i, max_wins = -1, number_of_teams;
    for (i = 0; i < HASH_TABLE_SIZE; i++){
        if (hashtable[i] != NULL){
            team_node *t = hashtable[i];
            while (t){
                if (t->tptr->number_of_wins > max_wins){
                    max_wins = t->tptr->number_of_wins;
                    number_of_teams = 1;
                }
                else if (t->tptr->number_of_wins == max_wins){
                    number_of_teams++;
                }
                t = t->next;            
            }
        }
    }
    if (max_wins > -1){
        char **strings = (char**) can_fail_malloc(sizeof(char*) * number_of_teams);
        int j = 0;
        for (i = 0; i < HASH_TABLE_SIZE; i++){
            if (hashtable[i] != NULL){
                team_node *t = hashtable[i];
                while (t){
                    if (t->tptr->number_of_wins == max_wins){
                        strings[j] = t->tptr->name;
                        j++;
                    }
                    t = t->next;
                }
            }
        }
        qsort(strings, number_of_teams, sizeof(char*), compare);
        printf("%d Melhores %d\n", line, max_wins);
        for (i = 0; i < number_of_teams; i++){
            printf("%d * %s\n", line, strings[i]);
        }
        free(strings);
    }
}
