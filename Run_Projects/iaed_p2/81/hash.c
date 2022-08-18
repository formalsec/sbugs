#include <stdlib.h>
#include <string.h>
#include "hash.h"


/* Receives a string and returns it's hash code */
int get_hash_value(char* word, int table_size) {

    /* Holds hash initial value and arbitrary prime number */
    int hash = 0, a = 127;

    /* Hashes every char of string */
    for (; *word != '\0'; word++) hash = (a * hash + *word) % table_size;

    /* Returns hashing index */
    return hash;
}


/* Creates hash table for teams */
hash_teams create_teams_hash_table(int table_size) {

    /* Allocates memory for table */
    hash_teams table = malloc(sizeof(struct my_hash_teams));

    /* Allocates memory for each node of table and initializes them as NULL */
    table->table = calloc(table_size, sizeof(struct sl_node));

    /* Stores table's max size */
    table->max_size = table_size;

    /* Since it was just created, it has zero elements in it */
    table->current_size = 0;

    /* Returns newly created table */
    return table;
}


/* Inserts a team inside the hash table */
void insert_team_hash(hash_teams table, sl_link team_node) {

    /* Gets hash value for team's name */
    int hash = get_hash_value(team_node->value->name, table->max_size);

    /* Finds a suitable position inside table */
    while(table->table[hash] != NULL) hash = (hash + 1) % table->max_size;

    /* Stores team node inside table */
    table->table[hash] = team_node;

    /* Updates amount of nodes inside table */
    table->current_size++;

    /* If table's capacity has reached 50%, expands it  */
    if (table->current_size > table->max_size/2)
        expands_team_hash(table);

}


/* Gets node's index which holds team's name. If not found, returns -1 */
int search_team_index_in_hash(hash_teams table, char* team_name) {

    /* Gets main index of the requested element */
    int hash = get_hash_value(team_name, table->max_size);

    /* Searches for team's name inside the table and, if found,
     * returns it's node's index */
    while (table->table[hash] != NULL) {

        /* Verifies if current node is the one we are looking for */
        if (strcmp(table->table[hash]->value->name, team_name) == 0) {

            return hash;

        } else {

            /* Gets next index value without going over table's size */
            hash = (hash + 1) % table->max_size;

        }

    }

    /* Returns -1 if not found */
    return -1;

}


/* Expands teams' hash table */
void expands_team_hash(hash_teams table) {

    /* Iterator */
    int i;

    /* Auxiliary variable for table's pointers */
    sl_link *aux = table->table;

    /* Resets and allocates more space for table's pointers */
    table->table = (sl_link*)
                    calloc(table->max_size * 2, sizeof(sl_link));

    /* Updates both sizes of new table */
    table->max_size = table->max_size * 2;
    table->current_size = 0;

    /* Iterates over each element inside old table's pointers and re-hashes
     * each one of them */
    for (i = 0; i < table->max_size / 2; i++) {
        if (aux[i] != NULL) {
            insert_team_hash(table, aux[i]);
        }
    }

    /* Frees old table's pointers' allocated memory */
    free(aux);

}


/* Deletes hash table for teams, clearing all memory */
void destroy_teams_hash(hash_teams table) {

    /* If table is not NULL, frees all memory related to it */
    if (table) {
        free(table->table);
        free(table);
    }

}


/* Creates hash table for games */
hash_games create_games_hash_table(int table_size) {

    /* Allocates memory for table */
    hash_games table = malloc(sizeof(struct my_hash_games));

    /* Initializes each node as NULL */
    table->table = calloc(table_size, sizeof(struct dl_node));

    /* Stores table's max size */
    table->max_size = table_size;

    /* Since it was just created, it has zero elements in it */
    table->current_size = 0;

    /* Returns newly created table */
    return table;
}


/* Inserts a game inside the hash table */
void insert_games_hash(hash_games table, dl_link game_node) {

    /* Gets hash value for game's name */
    int hash = get_hash_value(game_node->value->name, table->max_size);

    /* Finds a suitable position inside table */
    while(table->table[hash] != NULL) hash = (hash + 1) % table->max_size;

    /* Stores game node inside table */
    table->table[hash] = game_node;

    /* Updates amount of nodes inside table */
    table->current_size++;

    /* If table's capacity has reached 50%, expands it  */
    if (table->current_size > table->max_size/2) expands_games_hash(table);

    /* If table's capacity has reached 50%, expands it  */
    if (table->current_size > table->max_size/2)
        expands_games_hash(table);

}


/* Gets node's index inside table which holds game's name */
int search_game_index_in_hash(hash_games table, char* game_name) {

    /* Gets primary index of requested element */
    int hash = get_hash_value(game_name, table->max_size);

    /* Searches for game's name in table and, if found, returns it's index */
    while (table->table[hash] != NULL) {

        /* Verifies if current node is the one we are looking for */
        if (strcmp(table->table[hash]->value->name, game_name) == 0) {

            return hash;

        } else {

            /* Gets next index value without going over table's size */
            hash = (hash + 1) % table->max_size;

        }

    }

    /* Returns -1 if not found */
    return -1;

}


/* Expands games' hash table */
void expands_games_hash(hash_games table) {

    /* Iterator */
    int i;

    /* Auxiliary variable for table's pointers */
    dl_link *temp = table->table;

    /* Resets and allocates more space for table's pointers */
    table->table = (dl_link*)
                    calloc(table->max_size * 2, sizeof(dl_link));

    /* Updates both sizes of new table */
    table->max_size = table->max_size * 2;
    table->current_size = 0;

    /* Iterates over each element inside old table's pointers and re-hashes
     * each one of them */
    for (i = 0; i < table->max_size / 2; i++) {
        if (temp[i] != NULL) {
            insert_games_hash(table, temp[i]);
        }
    }

    /* Frees old table's pointers' allocated memory */
    free(temp);

}


/* Removes input game's node from the table */
void deletes_game_hash(hash_games table, int game_index) {

    /* Iterator */
    int i;

    /* Current iteration's node */
    dl_link node;

    /* Updates amount of nodes inside table */
    table->current_size--;

    /* Resets node's index inside table. We don't need to free node's memory
     * here because this function is going to be used after deleting the node
     * in another function */
    table->table[game_index] = NULL;

    /* Re-inserts node's posterior elements inside the table */
    for (i = (game_index + 1) % table->max_size;
         table->table[i] != NULL;
         i = (i + 1) % table->max_size) {

        /* Gets current iteration's node */
        node = table->table[i];

        /* Resets table's position */
        table->table[i] = NULL;

        /* Re-inserts node in table */
        insert_games_hash(table, node);

    }

}


/* Deletes hash table for games, clearing all memory */
void destroy_games_hash(hash_games table) {

    /* If table is not NULL, frees all memory */
    if (table) {
        free(table->table);
        free(table);
    }

}
