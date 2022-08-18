#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "games.h"

#ifndef gameslinked_h
#define gameslinked_h

typedef struct gamenode *gamelink;

typedef struct _gamelist{
    gamelink head;
    gamelink tail;
}*gamelist;

struct gamenode{            /*For efficiency purposes, it was chosen to implement a circular doubly linked list, with pointers that keep track of the beginning*/
    Game game;              /*and end of the list, in order to facilitate the insertion process */
    struct gamenode* next;
    struct gamenode* prev;
};

/*---------------------------------------game_listInit---------------------------
INPUT: N/A
OUTPUT: Struct of type gamelist, ready to store games.*/
gamelist game_listInit(); /* Inicializa uma lista vazia, pronta a armazenar elementos */

/*---------------------------------------game_listAddNode---------------------------
INPUT: game (struct Game), prev, next (struct gamelink)
OUTPUT: Struct of type gamelist 
Initializes a node, ready to be inserted in the games' data structure.*/
gamelink game_listAddNode(Game game, gamelink prev, gamelink next);

/*---------------------------------------game_listDeleteNode---------------------------
INPUT: node (struct gamelink)
OUTPUT: N/A 
Finds and deletes a certain node from a list*/
void game_listDeleteNode(gamelink node); /* Recebe um node e apaga o da lista*/

/*---------------------------------------game_listEmpty---------------------------
INPUT: node (struct gamelink)
OUTPUT: successor of given node (struct gamelink) 
Verifies if a given list is empty.*/
int game_listEmpty(gamelist head);

/*---------------------------------------game_searchList---------------------------
INPUT: list (struct gamelist), key (string)
OUTPUT: element with name 'key' (gamelink) */
gamelink game_searchList(gamelist list, char* key);

/*---------------------------------------game_destroyList---------------------------
INPUT: NL, list (struct gamelist), key (string), news1, news2 (new scores)
OUTPUT: gamelist with the updated scores
Updates the scores of a given game in a given list*/
gamelist game_changeScore(int NL, gamelist list, char* key, int news1, int news2);

/*---------------------------------------game_removeList---------------------------
INPUT: list (struct gamelist), node2Delte (struct gamelink)
OUTPUT: gamelist without the given node
Updates the list, removing the given node from it*/
gamelist game_removeList(gamelist list, gamelink node2Delete);

/*---------------------------------------game_showList---------------------------
INPUT: NL, list (struct gamelist)
OUTPUT: N/A
Prints every game form a given list*/
void game_showList(int NL, gamelist list);

/*---------------------------------------game_insertListEnd---------------------------
INPUT: list (struct gamelist), game ( struct Game)
OUTPUT: list (gamelist) 
Inserts a given element to the list*/
gamelist game_insertListEnd(gamelist list, Game game);

/*---------------------------------------game_destroyList---------------------------
INPUT: list (struct gamelist)
OUTPUT: N/A
Destroys a given list.*/
void game_destroyList(gamelist list);

#endif