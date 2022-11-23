#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "games.h"


gLink gInsert_begin(gLink head, pGame game)
/* inserts game in the top of a list (head) */
{
    gLink new = (gLink)can_fail_malloc(sizeof(struct gNode));
    if (head != NULL)
        head->prev = new;
    new->game = game;
    new->next = head;
    new->prev = NULL;
    return new;
}

gLink gRemove(gLink head, char *name)
/* removes game from a list, searching for its name */
{
    gLink aux;
    for (aux = head; aux != NULL; aux = aux->next)
    {
        if (strcmp(aux->game->name, name) == 0)
        {   
            /* only elem in list */    
            if(aux->prev == NULL && aux->next == NULL)
                head = NULL;
            
            /* first elem of list */
            else if (aux->prev == NULL)
            {
                if (aux == head)
                    head = aux->next;
                aux->next->prev = NULL;
            }

            /* last elem of list */
            else if (aux->next == NULL)
            {
                aux->prev->next = NULL;
            }

            else
            {   
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;
            }
            
            break;
        }
    }
    free(aux);
    return head;
}

pGame gSearch(gLink head, char *name)
/* search for game in list, by its name */
{
    gLink aux;
    for (aux = head; aux != NULL; aux = aux->next)
    {
        if (strcmp(aux->game->name, name) == 0)
        {   
            return aux->game;
        }
    }
    return NULL;
}

int gHash(char *v)
/* calculates the hash's list index where the game is */
{
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a*h + *v) % H_LEN;
    return h;
}

gLink* gInit(gLink *hash)
/* initiates the hashtable with NULL pointers */
{
    int i;
    hash = (gLink*) can_fail_malloc(H_LEN*sizeof(gLink));
    for (i = 0; i < H_LEN; i++)
        hash[i] = NULL;
    return hash;
}

pGame gHTsearch(gLink *hash, char *name)
/* search for a game in hashtable */
{
    int i = gHash(name);
    return gSearch(hash[i], name);
}

void gHTinsert(gLink *hash, pGame game)
/* insert a game in hashtable */
{
    int i = gHash(game->name);
    hash[i] = gInsert_begin(hash[i], game);
}

void gHTdelete(gLink *hash, char *name)
/* delete a game from hashtable */
{
    int i = gHash(name);
    hash[i] = gRemove(hash[i], name);
}

void freeGame(pGame g)
/* frees all the memory allocated for a game */
{
    free(g->team1);
    free(g->team2);
    free(g->name);
    free(g);
}
