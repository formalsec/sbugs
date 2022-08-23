#ifndef _BT_
#define _BT_

#include <stdlib.h>
#include <stdio.h>
#include "Team_b2.h"
#include "List_T2.h"

/* Structure Binary Tree Node, has a team and a pointer to the node in the left and the right*/
typedef struct BTnode *BTlink;
struct BTnode { Team team; BTlink l; BTlink r;};

/* Returns NULL, the initial value of the head */
BTlink BTinit();
/* Allocs memory for a Tree Node. Returns a pointer to the Node */
BTlink BTnew(Team team);
/* Returns the item with the maximum value in the Tree */
BTlink BTmax(BTlink link);

/* Insert the team into the Tree acording to less */
BTlink BTinsert(BTlink link, Team team); /* Returns new head */
/* Returns the Team associated with name in the tree */
Team BTsearch(BTlink link, char *name);
/* Deletes the team from the Tree */
BTlink BTdelete(BTlink link, Team team); /* Returns new head */

/* Traverses the tree adding to a list the teams with maximum wins. Returns number of teams added */
int Ttraverse(BTlink link, LTlink *head, int i);

/* Returns the team in the pointer link */
Team BTgetteam(BTlink link);
#endif