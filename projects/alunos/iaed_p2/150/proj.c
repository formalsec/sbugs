#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "proj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Number of positions of teams and games hashtables */
#define M 1009



/* Adds new game to data base. */
void AddNewGame(char * name, char * team1, char * team2, int score1, int score2, TEAMlink * Teams, 
                GAMElink * Games, int * countInput, int * countGames, int * index) {
    Game *new = NULL;
    Team *t1 = TEAMsearch(team1, Teams);
    Team *t2 = TEAMsearch(team2, Teams);
    (*countInput)++;
    
    /* if the game is already in the data base prints error */
    if (GAMEsearch(name, Games) != NULL) {
        printf("%d Jogo existente.\n", *countInput);
    }
    /* if one or both teams are not in the data base prints error */
    else if (t1 == NULL || t2 == NULL) {
        printf("%d Equipa inexistente.\n", *countInput);
    }

    else {
        (*countGames)++;
        new = newGame(name, team1, team2, score1, score2, index);
        GAMEinsert(new, Games);
        
        /* increases number of victories of the winning team */
        if (score1 > score2) {
            t1->wins++;
        }
        else if (score1 < score2) {
            t2->wins++;
        }
        (*index)++;
    }
}


/* Adds new team to the data base. */
void AddNewTeam(char * name, TEAMlink *Teams, int * countInput) {
    Team *new = NULL;
    (*countInput)++;

    /* if team is already in the data base prints error */
    if (TEAMsearch(name, Teams) != NULL) {
        printf("%d Equipa existente.\n", *countInput);
    }

    else {
        new = newTeam(name);
        TEAMinsert(new, Teams);   
    }
}


/* Searches for a game in the data base and returns it. */
void SearchGame(char * name, GAMElink * Games, int * countInput) {
    Game *game = GAMEsearch(name, Games);
    (*countInput)++;

    /* if the game is not in the database prints error */
    if (game == NULL) {
        printf("%d Jogo inexistente.\n", *countInput);
    }

    else {
        printf("%d ", *countInput);
        printGame(game);
    }
}


/* Deletes a game from the data base. */
void DeleteGame(char *name, TEAMlink * Teams, GAMElink * Games, int * countInput, int * countGames) {
    Game *game = GAMEsearch(name, Games);
    Team *t1, *t2;
    (*countInput)++;

    /* if the game is not in the data base prints error */
    if (game == NULL) {
        printf("%d Jogo inexistente.\n", *countInput);
    }

    else {
        t1 = TEAMsearch(game->team1, Teams);
        t2 = TEAMsearch(game->team2, Teams);

        /* Subtract 1 win to the games winner */
        if (game->score1 > game->score2) {
            t1->wins--;
        }
        else if(game->score1 < game->score2) {
            t2->wins--;
        }
        GAMEdelete(name, Games);
        (*countGames)--;
    }
}


/* Changes the score of a game. */
void ChangeScore(char * name, int NewScore1, int NewScore2, TEAMlink * Teams, GAMElink * Games, int * countInput) {
    Game *game = GAMEsearch(name, Games);
    Team *team1, *team2;
    int OldScore1, OldScore2;
    (*countInput)++;

    /* if the game is not in the data base prints error */
    if (game == NULL) {
        printf("%d Jogo inexistente.\n", *countInput);
    }

    else {
        /* saves old scores and changes game's score for the new scores */
        OldScore1 = game->score1;
        OldScore2 = game->score2;
        game->score1 = NewScore1;
        game->score2 = NewScore2;

        team1 = TEAMsearch(game->team1, Teams);
        team2 = TEAMsearch(game->team2, Teams);
        
        /* changes teams' number of wins if necessary */
        if (OldScore1 > OldScore2) {
            if (NewScore1 < NewScore2) {
                team1->wins--;
                team2->wins++;
            }
            else if (NewScore1 == NewScore2) {
                team1->wins--;
            }
        }
        else if (OldScore1 < OldScore2) {
            if (NewScore1 > NewScore2) {
                team1->wins++;
                team2->wins--;
            }
            else if (NewScore1 == NewScore2) {
                team2->wins--;
            }
        }
        else if (OldScore1 == OldScore2) {
            if (NewScore1 > NewScore2) {
                team1->wins++;
            }
            else if (NewScore1 < NewScore2) {
                team2->wins++;
            }
        }
    }
}


/* Searches for a team in the data base. */
void SearchTeam(char * name, TEAMlink * Teams, int * countInput) {
    Team *team = TEAMsearch(name, Teams);
    (*countInput)++;

    /* if team is not in the data base prints error */
    if (team == NULL) {
        printf("%d Equipa inexistente.\n", *countInput);
    }

    else {
        printf("%d ", *countInput);
        printTeam(team);
        printf(" %d\n", team->wins);
    }
}


/* Function used in qsort() - compares games index. */
int CompIndex(const void *a, const void *b) {
    Game *game1, *game2;
    game1 = *(Game **) a;
    game2 = *(Game **) b;

    return (game1->index - game2->index);
}


/* Lists games for insertion order. */
void ListsGames(GAMElink * Games, int * countGames, int * countInput) {
    Game **GamesList;
    GAMElink head;
    int i, j = 0;
    (*countInput)++;

    /* stops if there are no games in the data base */
    if (*countGames < 0) return;

    GamesList = can_fail_malloc(sizeof(Game *) * (*countGames + 1));

    /* puts all games in the array */
    for (i = 0; i < M; i++) {
        head = Games[i];
        while (head) {
            GamesList[j] = head->game;
            head = head->next;
            j++;
        }
    }
    /* sorts the array by index(insertion) order */
    qsort(GamesList, *countGames + 1, sizeof(Game *), CompIndex);

    /* prints all games */
    for (i = 0; i <= *countGames; i++) {
        printf("%d ", *countInput);
        printGame(GamesList[i]);
    }

    free(GamesList);
}


/* Function used in qsort() - compares teams names. */
int CompFunc(const void *a, const void *b) {
    Team *team1, *team2;
    team1 = *(Team **) a;
    team2 = *(Team **) b;

    return strcmp(team1->name, team2->name);
}


/* Lists teams with more wins by lexicographic order. */
void ListsBestTeams(TEAMlink * Teams, int * countInput) {
    int i, j = 0, BestScore = 0, countTeams = -1;
    Team **TeamsList;
    TEAMlink head;
    (*countInput)++;

    /* searches for the biggest number of wins and counts how many teams have it */
    for (i = 0; i < M; i++) {
        head = Teams[i];
        while (head) {
            if (head->team->wins == BestScore) {
                countTeams++;
            }
            else if (head->team->wins > BestScore) {
                countTeams = 0;
                BestScore = head->team->wins;
            }
            head = head->next;
        }
    }

    /* stops if there are no teams in the data base */
    if (countTeams < 0) return;

    TeamsList = can_fail_malloc(sizeof(Team *) * (countTeams + 1));

    /* puts teams with the biggest number of wins in the array */
    for (i = 0; i < M; i++) {
        head = Teams[i];
        while(head) {
            if (head->team->wins == BestScore) {
                TeamsList[j] = head->team;
                j++;
            }
            head = head->next;
        }
    }

    /* sorts the array by lexicographic order of teams names */
    qsort(TeamsList, countTeams + 1, sizeof(Team *), CompFunc);

    /* prints all temas in the array */
    printf("%d Melhores %d\n", *countInput, BestScore);
    for (i = 0; i <= countTeams; i++) {
        printf("%d * ", *countInput);
        printTeam(TeamsList[i]);
        printf("\n");
    }

    free(TeamsList);
}





