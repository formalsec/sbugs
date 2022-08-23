#ifndef DATA_H
#define DATA_H


/*==========================USEFUL==========================*/
/*Puts the given string in reserved memory and returns the adress*/
char *NewString(char *string);



/*==========================TEAMS==========================*/
typedef struct dteam{

    /*Name of the team*/
    char *name;
    /*Number of wins of a team*/
    int wins;

} dteam;

/*Pointer to the dteam(data team) structure*/
typedef dteam *Team;


/*Creates a new team and returns its reserved memory adress*/
Team NewTeam(char *name);


/*Completely deletes a team*/
void DeleteTeam(Team team);


/*Returns the name of the team*/
char *NameTeam(Team team);


/*Returns the number of wins */
int Wins(Team team);


/*Changes the number of wins (increments or decrements of 1)*/
void ChangeWins(Team team, int n);



/*==========================GAMES==========================*/
typedef struct dgame{

    /*Name of a game*/
    char *name;
    /*Name of the first team*/
    char *team1;
    /*Name of the second team*/
    char *team2;
    /*Game score(team1, team2)*/
    int score[2];

} dgame;


/*Pointer to the dgame(data game) structure*/
typedef dgame *Game;


/*Creates a new game and returns its reserved memory adress*/
Game NewGame(char *name, char *team1, char *team2, int score1, int score2);


/*Completely deletes a game*/
void DeleteGame(Game game);


/*Returns the name of the game*/
char *NameGame(Game game);


/*Returns the name of the first team*/
char *Team1(Game game);


/*Returns the name of the second team*/
char *Team2(Game game);


/*Returns the score of the first team*/
int Score1(Game game);


/*Returns the score of the second team*/
int Score2(Game game);


/*Changes the score of the game*/
void ChangeScore(Game game, int score1, int score2);


#endif