#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*==========================AUXILIAR==========================*/
char *NewString(char *string){

    /*Size of the string with \0*/
    int size = strlen(string) + 1;

    /*Copies the string into the alocated adress*/
    char *string_adress = can_fail_malloc(size);
    string_adress = (char*) memcpy(string_adress, string, size);

    return string_adress;
}



/*==========================TEAMS==========================*/
Team NewTeam(char *name){
    /*Reserves memory for a data type Team*/
    Team team = (Team) can_fail_malloc(sizeof(dteam));

    /*Name of the team*/
    team->name = NewString(name);

    /*Initial number of wins*/
    team->wins = 0;

    return team;
}


void DeleteTeam(Team team){
    /*Frees the memory allocated for the team name*/
    free(team->name);

    /*Frees the memory allocated for the structure team*/
    free(team);
}


char *NameTeam(Team team){
    return team->name;
}


int Wins(Team team){
    return team->wins;
}


void ChangeWins(Team team, int n){
    /*Avoids negative wins*/
    if(team->wins > 0 || n > 0){
        team->wins += n;
    }
}



/*==========================GAMES==========================*/
Game NewGame(char *name, char *team1, char *team2, int score1, int score2){
    
    /*Reserves memory for a data type Game*/
    Game game = (Game) can_fail_malloc(sizeof(dgame));

    /*Name of the game*/
    game->name = NewString(name);

    /*Name of the first team*/
    game->team1 = NewString(team1);
    
    /*Name of the second team*/
    game->team2 = NewString(team2);

    /*Score of the first team*/
    game->score[0] = score1;

    /*Score of the second team*/
    game->score[1] = score2;

    return game;
}


void DeleteGame(Game game){
    /*Frees the memory allocated for the game name*/
    free(game->name);

    /*Frees the memory allocated for the first team name*/
    free(game->team1);

    /*Frees the memory allocated for the second team name*/
    free(game->team2);

    /*Frees the memory allocated for the structure game*/
    free(game);
}


char *NameGame(Game game){
    return game->name;
}


char *Team1(Game game){
    return game->team1;
}


char *Team2(Game game){
    return game->team2;
}


int Score1(Game game){
    return game->score[0];
}


int Score2(Game game){
    return game->score[1];
}


void ChangeScore(Game game, int score1, int score2){
    game->score[0] = score1;
    game->score[1] = score2;
}