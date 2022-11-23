#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "trees.h" 	/* Binary search tree based on slides */
#include "lista.h" 	/* Double linked list based on slides */

#define LINEMAX 1024/* Maximal characters in a string. */

char rd_ws(void); 	/* Reads whitespace from standard input. */
int rd_cmd(void);	/* Reads command from standard input. */

void cmd_a(link *head, link *last, Tree **g, Tree2 **t, int nl);		/* Adds a new game. */
void cmd_A(Tree2 **t, int nl);											/* Adds a new team. */
void cmd_l(link head, int nl);											/* List all the games in order of insertion. */
void cmd_p(Tree **g, int nl);											/* Searches for a game. */
void cmd_P(Tree2 **t, int nl);											/* Seaches for a team. */
void cmd_r(link *head, link *last, Tree **g,Tree2 **equipas, int nl);	/* Removes a game. */
void cmd_s(Tree **g, Tree2 **equipas, int nl);							/* Alters the score of a game. */
void cmd_g(Tree2 *t, int nl);											/* Finds teams with the most wins. */
void cmd_x(Tree *g, Tree2 *equipas);									/* Terminates the program. */

#endif