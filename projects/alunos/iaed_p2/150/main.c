#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "proj.h"
#include <stdio.h>


/* Maximum dimension of game's and team's names */
#define DIM 1024



/* Reads the first char(command) of each input and manage all footbal games and teams 
in the data base depending on the command. */
int main() {
    char command, name[DIM], team1[DIM], team2[DIM];
    int score1, score2, NewLine = 0, nGames = -1, indexGames = 0;
    int *countInput = &NewLine;        /* number of input lines */
    int *countGames = &nGames;         /* number of games in the data base */
    int *index = &indexGames;          /* games label to know insertion order */
    TEAMlink *Teams;
    GAMElink *Games;

    Games = GAMEinit();               /* inicializes the games hash */
    Teams = TEAMinit();               /* inicializes the teams hash */

    /* Does the instructions depending on the first character of each line of the input.
    The cicle ends when the first character of the line is 'x'. */
    while ((command = getchar()) != 'x') {
        switch (command) {
            case 'a':
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &score1, &score2);
                AddNewGame(name, team1, team2, score1, score2, Teams, Games, countInput, 
                           countGames, index);
                break;

            case 'A':
                scanf(" %[^:\n]", name);
                AddNewTeam(name, Teams, countInput);
                break;  

            case 'p':
                scanf(" %[^:\n]", name);
                SearchGame(name, Games, countInput);   
                break; 

            case 'r':
                scanf(" %[^:\n]", name);
                DeleteGame(name, Teams, Games, countInput, countGames);
                break;

            case 's':
                scanf(" %[^:\n]:%d:%d", name, &score1, &score2);
                ChangeScore(name, score1, score2, Teams, Games, countInput);
                break;

            case 'P':
                scanf(" %[^:\n]", name);
                SearchTeam(name, Teams, countInput);
                break;

            case 'l':
                ListsGames(Games, countGames, countInput);
                break;

            case 'g':
                ListsBestTeams(Teams, countInput);
                break;
        }
    }
    
    TEAMSfree(Teams);
    GAMESfree(Games);

    return 0;
}