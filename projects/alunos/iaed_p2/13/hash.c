#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "games.h"
#include "hash.h"
#include "list.h"

/* Created two instances of hash tables 
 * Two instances allow for faster searches and allows for a game to have the same name as a team
 * (There is no unicity constraint between said abstractions)
*/
static hash *games;
static hash *teams;

/* Returns an unsigned int between 0 and HASH_SIZE represents the position in the hash map 
 * that a specified string ocuupies
*/
unsigned int hashCode(char *str) {
        unsigned long hash = 5381;
        int pos, c;

        while((c=*str++))
            hash = ((hash << 5) + hash) + c;
        pos = hash % HASH_SIZE;
        return pos;
}
 /* Initialize hash map, allocates memory for both hashes
 */
void HASHinit() {
    int i;

    games = (hash *) can_fail_malloc (HASH_SIZE * sizeof(hash));
    teams = (hash *) can_fail_malloc (HASH_SIZE * sizeof(hash));

    /* Set all pointers to NULL */
    for(i = 0; i < HASH_SIZE; i++) {
        games[i] = NULL;
        teams[i] = NULL;
    }
}

/* Inserts a Team into the teams hash map
*/
void hashInsertTeam(Team *team) {
    hash new = (hash) can_fail_malloc (sizeof(struct hash_node));

    new->id = nameOfTeam(team);
    new->item = (void *) team;
    new->next = NULL;

    hashInsert(teams, new, nameOfTeam(team));
}

/* Inserts a Game into the games hash map
*/
void hashInsertGame(Game *game) {
    hash new = (hash) can_fail_malloc (sizeof(struct hash_node));

    new->id = getName(game);
    new->item = (void *) game;
    new->next = NULL;

    hashInsert(games, new, getName(game));
}

/* Insert item into specified hash map 
*/
void hashInsert(hash *table, hash item, char *str) {
    unsigned int pos = hashCode(str); 
    hash aux;

    /* If hash map index does not contain items */
    if(table[pos] == NULL)
        table[pos] = item;

    else {
        for (aux = table[pos]; aux->next != NULL; aux = aux->next);
        aux->next = item;
    } 
}

/* Search hash map games for a Game with specified name "str"
 * Return pointer to said Game
*/
Game *searchGameHash(char *str) {
    Game * game = (Game *) hashSearch(games, str);
    return game;
}

/* Search hash map teams for a Team with specified name "str"
 * Return pointer to said Team
*/
Team *searchTeamHash(char *str) {
    Team * team = (Team *) hashSearch(teams, str);
    return team;
}

/* Search specified hash map for an Item with specified name "str"
 * Return pointer to said Item
*/
void *hashSearch(hash *table, char *str) {
    unsigned int pos = hashCode(str);
    hash aux;

    if (table[pos] == NULL)
        return NULL;

    for (aux = table[pos]; aux != NULL; aux = aux->next) {
        if (!strcmp(str, aux->id))
            return aux->item;
    }
    
    return NULL;
}

/* Remove Game from hash map games and return pointer to said Game
 * (Only games can be removed)
 * Free hash node
*/
void *hashRemove(char *str) {
    unsigned int pos = hashCode(str);
    item returnItem;
    hash aux, prev = NULL;

    /* Iterate through all Games until one is found with the specified name 
     * or until hash index ends 
     * */
    for(aux = games[pos]; aux != NULL && strcmp(aux->id, str); aux = aux->next)
        prev = aux;
    
    if(aux != NULL){ /* If such an item was found */
        if(prev != NULL) /* If the found Item wasn't the first Game in the hash index */    
            prev->next = aux->next;
    
        else
            games[pos] = aux->next;

        returnItem =aux->item;
        free(aux);
        return returnItem;
    }

    return NULL;
}

/* Clear a specified hash map.
 * Free all allocated items and hash nodes in said hash map.
*/
void particularHashClean(hash *head, void(* freeItem)(void *item)) {
    hash aux, prev;
    int i;
    for(i = 0; i < HASH_SIZE; i++) {
        for(aux = head[i]; aux != NULL; aux = prev) {
            prev = aux->next;
            freeItem(aux->item);
            free(aux);
        }
    }
}

/* Clear all hash maps.
 * Free all allocated
*/
void hashClean() {
    particularHashClean(games, freeGame);
    particularHashClean(teams, freeTeam);
    free(games);
    free(teams);
}

/* Query on the teams hash map. 
 * Return value is an array with the names of all teams with the most wins .
 * Parameter length gets changed to length of list .
 * Parameter wins gets changed to the highest amount of wins. 
*/
char **getBestTeams(int *length, unsigned int *wins) {
    /* Amount represents array length. High represents maximum wins recorded. */
    int i, amount = 0, high = 0;
    char **out = (char **) can_fail_malloc(sizeof(char *)); /* Returned array of strings */
    hash aux;

    for(i = 0; i < HASH_SIZE; i++) {
        for(aux = teams[i]; aux != NULL; aux = aux->next)
            /* If said team's amount of wins is the same as high
             * add to array and increment amount.
            */
            if(amountOfWins(aux->item) == high) {
                amount++;
                /* Increase array's length to accomodate new team name */
                out = (char **) can_fail_realloc(out, sizeof(char *) * amount);
                out[amount - 1] = nameOfTeam(aux->item);
            }
            /* If said team's amount of wins is higher than high
            */
            else if(amountOfWins(aux->item) > high) {
                amount = 1;
                /* Reset array's length to one */
                out = (char **) can_fail_realloc(out, sizeof(char *));
                out[0] = nameOfTeam(aux->item);
                high = amountOfWins(aux->item);
            }
    }

    *length = amount;
    *wins = high;
    return out;
}