#ifndef games_h
#define games_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teams.h"

typedef struct games{
    char* name;     /*Games' name*/
    ptrTeam t1;     /*Teams that played eachother in the match*/
    ptrTeam t2;
    int t1score;    /*Goals scored in the match*/
    int t2score;
}*Game;

/*---------------------------------------gameInit------------------------------------------------
INPUT: name (Name of the game), team1 e team2 (Struct ptrTeam), score1 e score2 (Score of the game)
OUTPUT: Struct of type Game, ready to be inserted in the games' data structure.*/
Game gameInit(char* name, ptrTeam team1, ptrTeam team2, int score1, int score2);

/*---------------------------------------gameDestroy----------------------------------------------
INPUT: Struct of type Game
OUTPUT: N/A
Destroys the game.*/
void gameDestroy(Game game);

/*---------------------------------------gameEmpty----------------------------------------------
INPUT: Struct of type Game
OUTPUT: TRUE/ FALSE
Verifies whether a game is NULL or not.*/
int gameEmpty(Game game);

/*----------gameName--------------
INPUT: Struct of type Game
OUTPUT: char*, Games' name
Verifies whether a game is NULL.*/
char* gameName(Game game);

/*----------gameScoreT1/gameScoreT2--------------
INPUT: Structs of type Game
OUTPUT: int, the score of team1 or team2 of struct Game
Returns a score of a team from 'game'*/
int gameScoreT1(Game game);
int gameScoreT2(Game game);

/*----------gameTeam1/gameTeam2--------------
INPUT: Structs of type Game
OUTPUT: struct ptrTeam 
Returns a team from struct 'game'*/
ptrTeam gameTeam1(Game game);
ptrTeam gameTeam2(Game game);

/*----------gameChangeScore--------------
INPUT: Structs of type Game, score1 and score2 (new scores)
OUTPUT: struct Game 
Changes a games' scores*/
Game gameChangeScore(Game game, int score1, int score2);

/*----------gamePrint--------------
INPUT: NL (input line), game (Struct Game)
OUTPUT: N/A 
Prints a game.*/
void gamePrint(int NL, Game game);

#endif


