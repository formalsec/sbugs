#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR	1024    /* Max value for the length of a string to read. */
#define SG		   1049    /* Dim of the games hashtable.                   */
#define ST	      1049    /* Dim of the teams hashtable.                   */

/* Game is pointer to a struct that contains the database 
of a game, its name, teams playing and the score.         */
typedef struct stru_Game{
    char* name,* team1,* team2;
    unsigned int score1, score2;
}* Game;

/* Game_Link is a pointer to a node of a list of Games; it
   contains the Game item and the previous and next node.  */
typedef struct node_G{
	Game item;
    struct node_G* prev;
	struct node_G* next;
}* Game_Link;

/* Team is a pointer to a struct that contains the database of
   a Team, its name and the number of victories (games won).   */
typedef struct stru_Team{
    char* name;
    int victories;
}* Team;

/* Team_Link is a pointer to a node of a list of Teams; it
   contains the Team item and the previous and next node.  */
typedef struct node_T{
	Team item;
	struct node_T* next;
}* Team_Link;

/* List_Limits is a pointer to a struct containing the head and tail of the
   Games list; This is useful for the insertion at the end of the list.     */
typedef struct connected_list{
    Game_Link head;
    Game_Link tail;
}* List_Limits;
