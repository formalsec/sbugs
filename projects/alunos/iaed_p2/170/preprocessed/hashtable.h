#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "data.h"


/*==========================TEAMS==========================*/
/*Struct that represents an hashtable for Teams*/
typedef struct teamht{

    /*Hashtable*/
    Team *ht;
    /*Number of team in the hashtable*/
    int num;
    /*The max size of the hashtable*/
    int size;

}teamht;

/*Pointer to the teamht(team hashtable) structure)*/
typedef struct teamht *HT_Team;


/*Initiates the team hashtable, with the given size*/
HT_Team NewHT_Team(int size);


/*Completely deletes the team hashtable*/
void DeleteHT_Team(HT_Team Teams);


/*Inserts a team into the team hashtable*/
void InsertHT_Team(HT_Team Teams, Team team);


/*Searches for a team in the hashtable and returns its adress
or NULL if it doesnt exist*/
Team SearchHT_Team(HT_Team Teams, char *name);


/*Increases the hashtable size by double*/
void ExpandHT_Team(HT_Team Teams);


/*Prints the teams that have the highest win*/
void HighestWin(HT_Team Teams, int NL);



/*==========================GAMES==========================*/
/*Struct that represents an hashtable for games*/
typedef struct gameht{

    /*Hashtable*/
    Game *ht;
    /*Number of games in the hashtable*/
    int num;
    /*Size of the hastable*/
    int size;
}gameht;


/*Pointer to the hashtable for games*/
typedef struct gameht *HT_Game;


/*Initiates the game hashtable, with the given size*/
HT_Game NewHT_Game(int size);


/*Completely deletes the game hashtable*/
void DeleteHT_Game(HT_Game games);


/*Inserts a gamits index
or a negative number if the game doesnt exist*/
void InsertHT_Game(HT_Game games, Game game);


/*Removes a game from the game hashtable*/
void RemoveHT_Game(HT_Game games, Game game);


/*Searches for a game in the hashtable and returns its adress
or NULL if it doesnt exist*/
Game SearchHT_Game(HT_Game games, char *name);


/*Returns the game adress in the index i*/
Game GameHT(HT_Game games ,int i);


/*Increases the hashtable size by double*/
void ExpandHT_Game(HT_Game games);


#endif