#ifndef Games
#define  Games
#include "Teams.h"

/* Max size of a team name */
#define  MAXGNAME 1024

/* Maximum of teams stored */
#define  THGsize  1000

/* contains all the information about each game */
typedef struct Game{
	char        *name;
	pTeam        team1;
	int 	scoreteam1;
	pTeam        team2;
	int 	scoreteam2;
}*pGame;

/* node for the storing the input order of the Games */
typedef struct GNode{
	pGame 		     		g;
	struct GNode *next, *prev;
}*pGNode;

/* struct that maintains the input order */
typedef struct list{
	struct GNode *head, *last;
}*plist;

/* node of the Games hash table */
typedef struct nodeG{
	pGNode        gms;
	struct nodeG *next; 
}*pNode;

/* struct that encapsulates all the information related to the games */
typedef struct GameSystem{
	pNode  *headsgames;   
	plist  	      list;
	int  HTsize;
	int  number_games;
}GS;

/* inicializes and allocates all the info needed for the game System*/
void Init_Games(GS *gs);

/* 
inserts the game as the tail of the double 
linked list and in the correct position in the hash table
*/
void STinsertG(GS *gs, pGame game);

/* searches for a game in the System through the hash table */
pNode STsearchG(char *name, GS *gs);

/* 
Deleates a node form the hash table 
returning the altered hash table list 
*/
pNode remove_gameaux(pNode head, pGNode game);

/* alters the number of wins of a team when a score is altered */
void change_wins(pGNode gms, int scoret1, int scoret2);

/* frees all the memory remaining related to the games */
void Stop_Games(GS *gs);

#endif
 