#include "football_auxfunctions.h"

/* Initializes the Games database. */
Game_Link* initGameTable();

/* Initializes the Team database. */
Team_Link* initTeamTable();

/* Adds a Game to the database. */
void addGame(int l, Game_Link* headsG, 
List_Limits headsAndTail, Team_Link* headsT);

/* Lists the Games by insertion order. */
void listGames(int l, List_Limits headAndTail);

/* Finds the Game with the name given. */
void findGame(int l, Game_Link* heads);

/* Removes the Game with the name given. */
void removeGame(int l, Game_Link* headsG,
List_Limits headAndTail, Team_Link* headsT);

/* Changes the score of the Game with the name given. */
void changeScore(int l, Game_Link* heads, Team_Link* headsT);

/* Adds a Team to the database. */
void addTeam(int l, Team_Link* heads);

/* Finds the Team with the name given. */
void findTeam(int l, Team_Link* heads);

/* Lists the Teams with most wins. */
void findWinningTeams(int l, Team_Link* heads);

/* Cleares the Teams memory used. */
void freeTeams(Team_Link* heads);

/* Cleares the Games memory used. */
void freeGamesList(List_Limits headAndTail);

void freeGamesTable(Game_Link* heads);
