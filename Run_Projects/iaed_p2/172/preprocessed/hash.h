#ifndef _HASH_
#define _HASH_
#include "structs.h"
#define h_size 50021  /* HashTable size */


/* Hash function, which determines where the info will be placed in the HashTable */
int hash(char *v, int M);


/*###################################*/
/* Games HashTable related functions */
/*###################################*/

/* Initializes the Games HashTable */
Game* STinitG(int M);


/* Adds a Game to the HashTable */
void STinsertG(Game g, int M, Game *stg);


/* Deletes a Game from the HashTable */
void STdeleteG(char* v, int M, Game *stg);


/* Searches for a Game in the HashTable */
Game STsearchG(char* v, int M, Game *stg);


/*###########################################################*/
/*###########################################################*/


/*###################################*/
/* Teams HashTable related functions */
/*###################################*/


/* Initializes the Teams HashTable */
Team* STinitT(int M);


/* Adds a Team to the HashTable */
void STinsertT(Team t, int M, Team *stt);


/* Deletes a Team from the HashTable */
void STdeleteT(char* v, int M, Team *stt);


/* Searches for a Team in the HashTable */
Team STsearchT(char* v, int M, Team *stt);

#endif
