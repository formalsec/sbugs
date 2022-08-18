#ifndef _LT_
#define _LT_

#include <stdlib.h>
#include <stdio.h>
#include "Team_b2.h"

/* Structure List Node, has a team and a pointer to the next node */
typedef struct LTnode* LTlink;
struct LTnode {Team team; LTlink next;};

/* Returns NULL, the initial value of the head */
LTlink LTinit();
/* Allocs memory for a List Node. Returns a pointer to the Node */
LTlink LTnew(Team team);
/* Insert the team into the List acording to LTless */
LTlink LTinsert(LTlink LThead, Team team); /* Returns new head */
/* Deletes the team from the List */
LTlink LTdelete(LTlink LThead, Team team); /* Returns new head */
/* Prints the first members, the ones with the most wins */
void LTprint(LTlink LThead, int NL); 

/* Frees all nodes from the List. Returns NULL*/
LTlink LTclear(LTlink LThead);
/* Returns the team */
Team LTgetteam(LTlink link);

#endif