#ifndef _PROJ_
#define _PROJ_

#include "hashGame.h"
#include "hashTeam.h"


/************************** prototypes ***************************/

/* Adds new game to data base. */
void AddNewGame(char * name, char * team1, char * team2, int score1, 
                int score2, TEAMlink * Teams, GAMElink * Games, 
                int * countInput, int * countGames, int * index);

/* Adds new team to the data base. */
void AddNewTeam(char * name, TEAMlink * Teams, int * countInput);

/* Searches for a game in the data base and returns it. */
void SearchGame(char * name, GAMElink * Games, int * countInput);


/* Searches for a team in the data base. */
void SearchTeam(char * name, TEAMlink * Teams, int * countInput);

/* Deletes a game from the data base. */
void DeleteGame(char * nome, TEAMlink * Teams, GAMElink * Games, 
                int * countInput, int * countGames);

/* Changes the score of a game. */
void ChangeScore(char * name, int NewScore1, int NewScore2, 
                TEAMlink * Teams, GAMElink * Games, int * countInput);

/* Lists games for insertion order. */
void ListsGames(GAMElink * Games, int * countGames, int * countInput);

/* Lists teams with more wins by lexicographic order. */
void ListsBestTeams(TEAMlink * Teams, int * countInput);


#endif