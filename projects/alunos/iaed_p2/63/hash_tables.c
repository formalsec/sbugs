#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hash_tables.h"

/*
* Description: calculates the hash.
*/
int hash_function(char array[]){

    int i;
    /*hash value*/
    int hash = 0;
    /*primes for calculations*/
    int a = 6679, b = 6053;
    /*length of the array*/
    int len = strlen(array);

    /*perfroms the calculations for each letter of the array*/
    for (i = 0; i <= len; i++, a = a * b % (M-1)){
        hash = (a * hash + array[i]) % M;
    }
    
    return hash;
}


/*
* Description: calculates the hash for teams.
*/
int hash_team(node_teams *node){
    return hash_function(node->t.name);
}


/*
* Description: calculates the hash for games.
*/
int hash_game(node_games *node){
    return hash_function(node->g.name);
}


/*
* Description: inserts a team in the hash table.
*/
void insert_team(node_teams **table, node_teams *node){

    /*index of the hashtable*/
    int index;

    /*gets the index*/
    index = hash_team(node);

    /*sets the next node in the table to NULL*/
    node->next_in_hash_table = NULL;

    /*if the list of the index is empty*/
    if (table[index] == NULL){
        /*sets the previous node to NULL and the head of the list to the new*/
        node->prev_in_hash_table = NULL;
        table[index] = node;
        return;
    }

    /*sets the next node of the index to the new*/
    table[index]->next_in_hash_table = node;
    /*and the previous of the new to the one in the index*/
    node->prev_in_hash_table = table[index];
    /*sets the index to the node inserted*/
    table[index] = node;
}


/*
* Description: inserts a game in the hash table.
*/
void insert_game(node_games **table, node_games *node){

    /*index of the hashtable*/
    int index;

    /*gets the index*/
    index = hash_game(node);

    /*if the list of the index is empty*/
    node->next_in_hash_table = NULL;

    /*if the list of the index is empty*/
    if (table[index] == NULL){
        /*sets the previous node to NULL and the head of the list to the new*/
        node->prev_in_hash_table = NULL;
        table[index] = node;
        return;
    }


    /*sets the next node of the index to the new*/
    table[index]->next_in_hash_table = node;
    /*and the previous of the new to the one in the index*/
    node->prev_in_hash_table = table[index];
    /*sets the index to the node inserted*/
    table[index] = node;
}


/*
* Description: checks if a team is in the hash table and returns it.
*              if it isn't, returns NULL.
*/
node_teams * in_table_teams(node_teams **table, node_teams *node){

    /*index of the hashtable*/
    int index;
    /*temporary node*/
    node_teams *tmp;

    /*gets the index*/
    index = hash_team(node);
    /*sets tmp to the node of the index*/
    tmp = table[index];

    /*if it is empty return NULL*/
    if (tmp == NULL){
        return NULL;
    }

    /*goes through the list of the index*/
    while (tmp != NULL){
        /*if the temporary has the same name as the one to be found returns it*/
        if (strcmp(tmp->t.name, node->t.name) == 0){
            return tmp;
        }
        /*goes to the previous that was inserted in the index*/
        tmp = tmp->prev_in_hash_table;
    }
    return NULL;
}


/*
* Description: checks if a game is in the hash table and returns it.
*              if it isn't, returns NULL.
*/
node_games * in_table_games(node_games **table, node_games *node){

    /*index of the hashtable*/
    int index;
    /*temporary node*/
    node_games *tmp;

    /*gets the index*/
    index = hash_game(node);
    /*sets tmp to the node of the index*/
    tmp = table[index];

    /*if it is empty return NULL*/
    if (tmp == NULL){
        return NULL;
    }

    /*goes through the list of the index*/
    while (tmp != NULL){
        /*if the temporary has the same name as the one to be found returns it*/
        if (strcmp(tmp->g.name, node->g.name) == 0){
            return tmp;
        }
        /*goes to the previous that was inserted in the index*/
        tmp = tmp->prev_in_hash_table;
    }
    return NULL;
}