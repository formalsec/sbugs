#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "teams.h"


tLink tInsert_begin(tLink head, pTeam team)
/* inserts team in the top of list (head) */
{
    /* allocates memory for new team */
    tLink new = (tLink)can_fail_malloc(sizeof(struct tNode));
    if (head != NULL)
        head->prev = new;
    new->team = team;
    new->next = head;
    new->prev = NULL;
    return new;
}

tLink tRemove(tLink head, char *name)
/* removes team with name in (char), from list (head) */
{
    tLink aux;
    for (aux = head; aux != NULL; aux = aux->next)
    {
        if (strcmp(aux->team->name, name) == 0)
        {
            if (aux->prev != NULL)
              aux->prev->next = aux->next;

            if (aux->next != NULL)
              aux->next->prev = aux->prev;
        }
    }
    free(aux->team->name);
    free(aux->team);
    free(aux);
    return head;
}

pTeam tSearch(tLink head, char *name)
/* search for team in list (head), by its name */
{
    tLink aux;
    for (aux = head; aux != NULL; aux = aux->next)
    {
        if (strcmp(aux->team->name, name) == 0)
            return aux->team;
    }
    return NULL;
}

int tHash(char *v)
/* calculates the hash's list index where the team is */
{
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a*h + *v) % H_LEN;
    return h;
}

tLink* tInit(tLink *hash)
/* initiates the hash with NULL pointers */
{
    int i;
    hash = (tLink*) can_fail_malloc(H_LEN*sizeof(tLink));
    for (i = 0; i < H_LEN; i++)
        hash[i] = NULL;
    return hash;
}

pTeam tHTsearch(tLink *hash, char *name)
/* search for team in hashtable */
{
    int i = tHash(name);
    return tSearch(hash[i], name);
}

void tHTinsert(tLink *hash, pTeam team)
/* insert team in hashtable */
{
    int i = tHash(team->name);
    hash[i] = tInsert_begin(hash[i], team);
}

void tHTdelete(tLink *hash, char *name)
/* delete team from hashtable */
{
    int i = tHash(name);
    hash[i] = tRemove(hash[i], name);
}

int max_wins(tLink *hashTeam)
/* calculates the number of wins of the most winning team */
{
    int max = 0;
    int i;
    tLink aux;

    for(i = 0; i!= H_LEN; i++)
    {
        aux = hashTeam[i];
        while (aux != NULL)
        {
            if (aux->team->wins > max)
            {
                max = aux->team->wins;
            }
            aux = aux->next;
        }
    }
    return max;
}


tLink alphInsert(tLink tHead, pTeam team)
/* insert team in linked list (tHead), sorted alphabetically. */
{
    tLink new;
    tLink aux = tHead;
    new = (tLink)can_fail_malloc(sizeof(struct tNode));
    new->team = team;
    if (tHead == NULL)
    {
        new->next = tHead;
        new->prev = NULL;
        return new;
    }
    while(strcmp(aux->team->name, new->team->name) < 0 && aux->next != NULL)
        aux = aux->next;
    if (aux->next == NULL && strcmp(aux->team->name, new->team->name) < 0)
    {
        aux->next = new;
        new->prev = aux;
        new->next = NULL;
    }
    else
    {
        new->prev = aux->prev;
        if (aux->prev != NULL)
            aux->prev->next = new;
        aux->prev = new;
        new->next = aux;
        if (tHead == aux)
            tHead = new;
    }

    return tHead;
}

void freeTeam(pTeam t)
/* frees all the memory allocated for a team */
{
    free(t->name);
    free(t);
}
