#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashtableGame.h"

/* Delete game flag */
#define DELETED 1


/* Calculates the given power of a number.
*  @params: base - number to multiply;
*           exp - exponent by which the base is multiplied.
*  @returns: int containing the result.
*/
static int power(int base, int exp)
{
    int i, res;
    res = 1;

    for(i = 0; i < exp; i++)
    {
        res = res*base;
    }

    return res;
}

/* Calculates an hash given a key and a given factor;
*  First hash function using double hashing method.
*  @params: factor - size of the hashtable;
*           key - key to hash.
*  @returns: int containing the hashed result representing an index
*            on the hashtable.
*/
static int hash(int factor, char *key)
{
    int hash, len, a, i;

    hash = 0;
    a = power(factor, 2);
    len = strlen(key);

    for(i = 0; i < len; i++)
    {
        a = (a*len)%(factor-1);
        hash = ((a*hash)+(*(key+i)))%factor;
    }

    return hash;
}

/* Calculates an hash given a key and a given factor;
*  Second hash function using double hashing method.
*  @params: factor - size of the hashtable;
*           key - key to hash.
*  @returns: int containing the hashed result representing an index
*            on the hashtable.
*/
static int hash2(int factor, char *key)
{
    int mod;
    mod = (*key+strlen(key))*3;
    return 1+(mod*hash(factor, key));
}

/* Initializes a new hashtable for storing games.
*  @params: factor - initial size of the hashtable;
*           size - number of games on the hashtable.
*  @returns: pointer to new hashtable.
*/
HTG *newHTG(int factor, int size)
{
    int i;
    HTG *table;

    /* Allocates memory and sets the hashtable's properties */
    table = (HTG*) can_fail_malloc(sizeof(HTG));
    table->size = size;
    table->factor = factor;
    table->items = (Game**) can_fail_malloc(sizeof(Game*)*factor);

    /* Sets all hashtable entries to NULL */
    for(i = 0; i < factor; i++)
    {
        table->items[i] = NULL;
    }

    return table;
}

/* Inserts a game into the hashtable.
*  @params: table - pointer to an hashtable;
*           game - pointer to a game.
*  @returns: void.
*/
void insertHTG(HTG *table, Game *game)
{
    int i, k, factor;
    char *key;
    Game **vector;
    
    key = game->name;
    factor = table->factor;
    vector = table->items;

    /* Double hash the key with the given factor */
    i = hash(factor, key);
    k = hash2(factor, key);

    /* Find an empty slot and insert the game */
    while(vector[i] != NULL && !vector[i]->isDeleted)
    {
        i = (i+k)%factor; 
    }

    vector[i] = game;

    /* Increment hashtable size */
    table->size++;
}

/* Deletes a game from the hashtable, by marking it as deleted.
*  @params: table - pointer to hashtable;
*           game - pointer to game.
*  @returns: void.
*/
void deleteHTG(HTG *table, Game *game)
{
    int i, k, factor;
    char *key;
    Game **vector;

    key = game->name;
    factor = table->factor;
    vector = table->items;

    /* Double hash the key with the given factor */
    i = hash(factor, key);
    k = hash2(factor, key);

    /* Find game */
    while(vector[i] != NULL)
    {
        if(!strcmp(vector[i]->name, key))
        {
            break;
        }
        else
        {
            i = (i+k)%factor;
        }
    }

    /* Return if the given game is not on the hashtable */
    if(vector[i] == NULL)
    {
        return;
    }

    /* Mark game as deleted */
    vector[i]->isDeleted = DELETED;

    /* Decrement hashtable size */
    table->size--;
}

/* Finds game on hashtable given its name.
*  @params: table - pointer to hashtable;
*           name - name of the game.
*  @returns: pointer to game, NULL if game not found.
*/
Game *getGame(HTG *table, char *name)
{
    int i, k, factor;
    Game **vector;
    
    factor = table->factor;
    vector = table->items;

    /* Double hash the key with the given factor */
    i = hash(factor, name);
    k = hash2(factor, name);

    /* Find game */
    while(vector[i] != NULL && !vector[i]->isDeleted)
    {
        if(!strcmp(vector[i]->name, name))
        {
            return vector[i];
        }
        else
        {
            i = (i+k)%factor;
        }
    }

    return NULL;
}

/* Frees the allocated memory of the hashtable.
*  @params: table - pointer to hashtable.
*  @returns: void.
*/
void freeHTG(HTG *table)
{
    int i, size, factor;
    Game **vector;

    size = table->size;
    factor = table->factor;
    vector = table->items;

    /* Free the allocated memory for the games */
    if(size >= 0)
    {
        for(i = 0; i < factor; i++)
        {
            if(vector[i] != NULL)
            {
                freeGame(vector[i]);
            }
        }
    }

    /* Free the allocated memory for the hashtable */
    free(vector);
    free(table);
}