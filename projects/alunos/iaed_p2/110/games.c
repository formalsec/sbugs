#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashteams.h"
#include "teams.h"
#include "games.h"

Game gameInit(char* name, ptrTeam team1, ptrTeam team2, int score1, int score2){
    
    if(strlen(name) < MAXNAME){
        Game game = can_fail_malloc(sizeof(struct games));
        game->name = can_fail_malloc(sizeof(char*) * (strlen(name) + 1));  
  
        strcpy(game->name, name);
        game->t1 = team1;
        game->t2 = team2;
        game->t1score = score1;
        game->t2score = score2;
        /* Determine whether there's a winning team */
        if (score1>score2)
            game->t1->wins++;
        else if (score1<score2)
            game->t2->wins++;

        return game;
    }
    else  
       return NULL;        
}

int gameEmpty(Game game){
    return game == NULL;
}

char* gameName(Game game){
    if (!gameEmpty(game))
        return game->name;
    return NULL;
}

int gameScoreT1(Game game){
    if (!gameEmpty(game))
        return game->t1score;
    return 0;
}

int gameScoreT2(Game game){
    if (!gameEmpty(game))
        return game->t2score;
    return 0;
}

ptrTeam gameTeam1(Game game){
    if (!gameEmpty(game))
        return game->t1;
    return NULL;
}

ptrTeam gameTeam2(Game game){
    if (!gameEmpty(game))
        return game->t2;
    return NULL;
}

Game gameChangeScore(Game game, int score1, int score2){
    if (!gameEmpty(game)){
        game->t1score = score1;
        game->t2score = score2;
        return game;
    }
    return NULL;
}

void gamePrint(int NL, Game game){
    if (!gameEmpty(game)){
        printf("%d %s %s %s %d %d\n", NL, gameName(game), teamName(gameTeam1(game)), teamName(gameTeam2(game)), gameScoreT1(game), gameScoreT2(game));
        return;
    }
    
}

void gameDestroy(Game game){
    free(gameName(game));
    free(game);
}

