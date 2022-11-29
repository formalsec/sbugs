#ifndef _HASHTEAM_
#define _HASHTEAM_

#include "Team.h"


/****** structure ******/

typedef struct TEAMnode {
    Team *team;
    struct TEAMnode *next;
}*TEAMlink;


/**************** prototypes ******************/

/* Initializes Teams hashtable. */
TEAMlink * TEAMinit();

/* Searches for a team in the hashtable. */
Team * TEAMsearch(char * name, TEAMlink * Teams);

/* Inserts a team in the hashtable. */
void TEAMinsert(Team * team, TEAMlink * Teams);

/* Deletes a team from the hashtable. */
void TEAMdelete(Team * team, TEAMlink * Teams);

/* Frees all memory attached to the hashtable. */
void TEAMSfree(TEAMlink *Teams);

/* Returns index by doing the sum of all 
characters of the team name module M. */
int hash(char * name);


#endif