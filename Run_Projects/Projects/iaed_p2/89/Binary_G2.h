#ifndef _BG_
#define _BG_

#include "Game_b2.h"

/* Structure Binary Tree Node, has a game and a pointer to the node in the left and the right*/
typedef struct BGnode *BGlink;
struct BGnode { Game game; BGlink l; BGlink r;};

/* Returns NULL, the initial value of the head */
BGlink BGinit();
/* Allocs memory for a Tree Node. Returns a pointer to the Node */
BGlink BGnew(Game game);
/* Returns the item with the maximum value in the Tree */
BGlink BGmax(BGlink link);

/* Insert the game into the Tree acording to less */
BGlink BGinsert(BGlink link, Game game); /* Return new head */
/* Returns the Game associated with name in the tree */
Game BGsearch(BGlink link, char *name);
/* Deletes the game from the Tree */
BGlink BGdelete(BGlink link, Game game); /* Return new head */

/* Traverses the tree adding to game all games. Returns number of games added */
int Traverse(BGlink link, Game *game, int i);

/* Returns the game in the pointer link */
Game BGgetgame(BGlink link);

#endif
