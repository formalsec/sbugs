#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "hashtable_team.h"
#include "hashtable_game.h"

#define TABLE_SIZE 20000

/* creates a hashtable to store the teams */

ht_team *ht_create_hteam(void) {

    int i = 0;
    /* allocate table */
    ht_team *hashtable = can_fail_malloc(sizeof(ht_team) * 1);

    /* allocate table entries */
    hashtable->entries = can_fail_malloc(sizeof(entry_team) * TABLE_SIZE);

    /* set each entry to null */

    for (; i < TABLE_SIZE; ++i) {
        hashtable->entries[i] = NULL;
    }
    return hashtable;
}

/* allocs the hashtable entry */

entry_team *ht_pair_team(TEAM *team) {

    /* allocate the entry */
    entry_team *entry = can_fail_malloc(sizeof(entry_team));

    /* assign the team */
    entry->team = team;

    /* next starts out null */
    entry->next = NULL;

    return entry;
}

/* hash function that returns the key to a slot in the hashtable */

unsigned int hash_team(char *team) {
    unsigned int value = 0;
    unsigned int i = 0;
    unsigned int len = strlen(team);


    for (; i < len; ++i) {
        value = value * 37 + team[i];
    }

    /* make sure value < TABLE_SIZE */
    value = value % TABLE_SIZE;

    return value;
}

/* function that inserts a game in the hashtable */

void ht_set_team(int line, ht_team *hashtable, TEAM *team) {

    entry_team *prev = NULL;
    unsigned int slot = hash_team(team->name);

    /* try to look up an entry set */
    entry_team *entry = hashtable->entries[slot];

    /* no entry means slot empty, insert if it is */
    if (entry == NULL) {
        hashtable->entries[slot] = ht_pair_team(team);
        return;
    }



    /* walk through each entry until either the end is reached or a matching key is found */
    while (entry != NULL) {
        /* check key */
        if (strcmp(entry->team->name, team->name) == 0) {
            /* match found, replace value */
            printf("%d Equipa existente.\n", line);
            free(team->name);
            free(team);
            return;
        }

        /* go to next */
        prev = entry;
        entry = prev->next;
    }

    /* if reached the end without a match, add new */
    prev->next = ht_pair_team(team);
}

/* function returns a team from the hashtable given the team's name */

TEAM *ht_get_team(ht_team *hashtable, char *team) {
    unsigned int slot = hash_team(team);

    /* tries to find a valid slot */
    entry_team *entry = hashtable->entries[slot];

    /* no slot means no entry */
    if (entry == NULL) {
        return NULL;
    }

    /* walk through each entry in the slot if there is more than one */
    while (entry != NULL) {
        /* return team if found */
        if (strcmp(entry->team->name, team) == 0) {
            return entry->team;
        }

        /* walk to next key if available */
        entry = entry->next;
    }

    /* reaching here means there was one or more entries but no matches */
    return NULL;
}

/* function frees all allocated memory inside the hashtable */

void ht_dump_team(ht_team *hashtable) {
    entry_team *temp = NULL;
    entry_team *entry = NULL;
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        if (hashtable->entries[i] != NULL) {
            entry = hashtable->entries[i];

            while (entry != NULL) {
                temp = entry->next;
                free(entry->team->name);
                free(entry->team);
                free(entry);
                entry = temp;
            }
            temp = entry;
            free(temp);
        }
    }
}

/* function that finds the max value of games won in the hashtable of teams (command 'g') */

void find_max(ht_team *hashtable, int line) {
    entry_team *temp = NULL;
    entry_team *entry = NULL;
    int i;
    int maxTeamNumber = 0;
    int max = 0;
    for (i = 0; i < TABLE_SIZE; i++) {
        if (hashtable->entries[i] != NULL) {
            entry = hashtable->entries[i]->next;
            if (hashtable->entries[i]->team->gameswon > max) {
                max = hashtable->entries[i]->team->gameswon;
                maxTeamNumber = 1;
            }
            else if (hashtable->entries[i]->team->gameswon == max) {
                maxTeamNumber++;
            }
            while (entry != NULL) {
                if (entry->team->gameswon > max) {
                    max = entry->team->gameswon;
                    maxTeamNumber = 1;
                }
                else if (entry->team->gameswon == max) {
                    maxTeamNumber++;
                }
                temp = entry->next;
                entry = temp;
            }
        }
    }
    order_array(hashtable, max, maxTeamNumber, line);
}

/* aux function that orders the newly made array of teams with the most games won */

void order_array(ht_team *hashtable, int max, int maxTeamNumber, int line) {
    entry_team *temp = NULL;
    entry_team *entry = NULL;
    int i = 0, j = 0;
    TEAM teams[100000];
    for (i = 0; i < TABLE_SIZE; i++) {
        if (hashtable->entries[i] != NULL) {
            entry = hashtable->entries[i]->next;
            if (hashtable->entries[i]->team->gameswon == max) {
                teams[j] = *hashtable->entries[i]->team;
                j++;
            }
            while (entry != NULL) {
                if (entry->team->gameswon == max) {
                    teams[j] = *hashtable->entries[i]->team;
                    j++;
                }
                temp = entry->next;
                entry = temp;
            }
        }
    }
    if(maxTeamNumber > 1) {
        mergesort_alphabet(teams, 0, maxTeamNumber - 1);
        printf("%d Melhores %d\n", line, max);
        for (i = 0; i < maxTeamNumber; i++) {
            printf("%d * %s\n", line, teams[i].name);
        }
    } else if (maxTeamNumber == 1){
        printf("%d Melhores %d\n", line, max);
        printf("%d * %s\n", line, teams[0].name);
    }
}

/* aux function for mergesort */

void merge_alphabet(TEAM a[], int left, int m, int right){
    int i = 0, j = 0, k = 0;
    for (i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for(j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for(k = left; k <= right; k++){
        if(strcmp(aux[j].name, aux[i].name) < 0){
            a[k] = aux[j--];
        }
        else {
            a[k] = aux[i++];
        }
    }
}

/* sorting algorithm that sorts the array alphabetically */

void mergesort_alphabet(TEAM a[], int l, int r){
    int m = (r+l)/2;
    if (r <= l)
        return;
    mergesort_alphabet(a, l, m);
    mergesort_alphabet(a, m+1, r);
    merge_alphabet(a, l, m, r);
}

/* returns a team given a certain name */

TEAM *getTeam(char *name) {
    TEAM *team = can_fail_malloc(sizeof(TEAM));
    team->name = can_fail_malloc(strlen(name) + 1);
    strcpy(team->name, name);
    team->gameswon = 0;

    return team;
}