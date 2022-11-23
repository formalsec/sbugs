#ifndef GAME_H
#define GAME_H
#include "structs.h"

/* removeGame(): This function removes the game from the hashtable and from the ordered games list */
orderedGames * removeGame(ht * game_ht, int cmd_count, orderedGames * head);

/* push(): Pushes the game into the ordered games list after adding it to the hashtable */
orderedGames * push(orderedGames * head, Game * game);

/* destroy(): Frees all the memory from the orderedGames list that was allocated  */
orderedGames * destroy(orderedGames * head);

/* print(): print all the games in the orderedGames list (insertion ordered) */
void print(orderedGames * head, int cmd_count);

#endif
