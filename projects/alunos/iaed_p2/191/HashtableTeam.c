#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashtableTeam.h"

/* Delete team flag */
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

/* Initializes a new hashtable for storing teams.
*  @params: factor - initial size of the hashtable;
*           size - number of teams on the hashtable.
*  @returns: pointer to new hashtable.
*/
HTT *newHTT(int factor, int size)
{
    int i;
    HTT *table;

    /* Allocates memory and sets the hashtable's properties */
    table = (HTT*) can_fail_malloc(sizeof(HTT));
    table->size = size;
    table->factor = factor;
    table->items = (Team**) can_fail_malloc(sizeof(Team*)*factor);

    /* Sets all hashtable entries to NULL */
    for(i = 0; i < factor; i++)
    {
        table->items[i] = NULL;
    }

    return table;
}

/* Inserts a team into the hashtable.
*  @params: table - pointer to an hashtable;
*           team - pointer to a team.
*  @returns: void.
*/
void insertHTT(HTT *table, Team *team)
{
    int i, k, factor;
    char *key;
    Team **vector;
    
    key = team->name;
    factor = table->factor;
    vector = table->items;

    /* Double hash the key with the given factor */
    i = hash(factor, key);
    k = hash2(factor, key);

    /* Find an empty slot and insert the team */
    while(vector[i] != NULL) 
    {
        i = (i+k)%factor; 
    }

    vector[i] = team;
    
    /* Increment hashtable size */
    table->size++;
}

/* Deletes a team from the hashtable, by marking it as deleted.
*  @params: table - pointer to hashtable;
*           team - pointer to team.
*  @returns: void.
*/
void deleteHTT(HTT *table, Team *team)
{
    int i, k, factor;
    char *key;
    Team **vector;

    key = team->name;
    factor = table->factor;
    vector = table->items;

    /* Double hash the key with the given factor */
    i = hash(factor, key);
    k = hash2(factor, key);

    /* Find team */
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

    /* Return if the given team is not on the hashtable */
    if(vector[i] == NULL)
    {
        return;
    }

    /* Mark team as deleted */
    vector[i]->isDeleted = DELETED;

    /* Decrement hashtable size */
    table->size--;
}

/* Finds team on hashtable given its name.
*  @params: table - pointer to hashtable;
*           name - name of the team.
*  @returns: pointer to team, NULL if team not found.
*/
Team *getTeam(HTT *table, char *name)
{
    int i, k, factor;
    Team **vector;
    
    factor = table->factor;
    vector = table->items;

    /* Double hash the key with the given factor */
    i = hash(factor, name);
    k = hash2(factor, name);

    /* Find team */
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
void freeHTT(HTT *table)
{
    int i, size, factor;
    Team **vector;

    size = table->size;
    factor = table->factor;
    vector = table->items;

    /* Free the allocated memory for the teams */
    if(size >= 0)
    {
        for(i = 0; i < factor; i++)
        {
            if(vector[i] != NULL)
            {
                freeTeam(vector[i]);
            }
        }
    }

    /* Free the allocated memory for the hashtable */
    free(vector);
    free(table);
}