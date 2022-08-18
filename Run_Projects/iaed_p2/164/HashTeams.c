#include "HashTeams.h"

/* Receives a size "m" and creates a new hash table of Teams, with that size,
initializing every entrance with NULL.*/
Team * HashTeamsInit(int * m){
    int i;
    Team * hash_table;
    hash_table = (Team*) malloc(sizeof(Team) * (*m));
    for (i = 0; i < *m; i++)
        hash_table[i] = NULL;   
    return hash_table;
}

/* Receives a hash table of Teams, a Team and a size. Inserts the Team in the hash table.*/
void HashTeamsInsert(Team * hash_table, Team t, int * m){
    /* "i" is the index on which the Team will be put on.*/
    int i = hash(TeamName(t), m);
    /* If there is a collision, the Team will be placed in the next available position.*/
    while (hash_table[i] != NULL)
        i = (i+1) % *m;
    hash_table[i] = t;
}

/* Receives a name, a size and a hash table. Returns the Team on the hash table if it exists, or
NULL if it doesn't exist.*/
Team TeamSearch(char * name, int * m, Team * hash_table){
    /* "i" is the index where the Team with "name" should be.*/
    int i = hash(name, m);
    /* If there is a collision, the positions until the NULL vector must be checked.*/
    while (hash_table[i] != NULL)
        if (eq(TeamName(hash_table[i]), name))
            return hash_table[i];
        else 
            i = (i+1) % *m;
    /* If the Team with name "name" is not found, the NULL vector is returned.*/
    return NULL;
}

/* Receives a hash table and the current number of Teams. Destroys every Team in it and the hash table itself.*/
void DestroyHashTeams(Team * hash_team, int * n_teams){
    int i = 0, count = 0;
    /* Variable "count" keeps track of how many Teams have been destroyed, and the cycle can stop when every Team have been destroyed.*/
    for (; count < *n_teams; i++)
        /* If a Team is found, it is destroyed.*/
        if (hash_team[i] != NULL){
            DestroyTeam(hash_team[i]);
            count++;
        }
    /* In the end, the hash table is destroyed.*/
    free(hash_team);
}

/* Receives a hash table of Teams, a number of Teams and the size of the hash table, expanding it to the double ans re-inserting
every Team. Returns the expanded hash table of Teams.*/
Team * ExpandTeams(Team * hash_team, int * n_teams, int * m){
    int i = 0, count = 0;
    Team * new_hash_team;
    /* The new size "m" is the double of the old one.*/
    (*m)*=2;
    /* "new_hash_team" is the hash table of Teams created from the new size.*/
    new_hash_team = HashTeamsInit(m);
    /* Every Team in the old hash table must be inserted in the new hash table.*/
    for (; count < *n_teams; i++)
        if (hash_team[i] != NULL){
            HashTeamsInsert(new_hash_team, hash_team[i], m);
            count++;
        } 
    /* The old hash table is destroyed.*/
    free(hash_team);
    return new_hash_team;
}
    

