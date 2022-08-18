#include "hashtable.h"
#include "data.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Initial size of the hashtables*/
#define SIZE 769
/*Max size of a input string*/
#define LENGTH 1024

/*Team win*/
#define WIN 1
/*Correction of a team number of wins
when a game score is changed*/
#define CORRECTION -1


/*==========================AUXILIAR==========================*/
/*Prints a team*/
void PrintTeam(Team team, int NL){
    printf("%d %s %d\n", NL, NameTeam(team), Wins(team));
}


/*Prints a game*/
void PrintGame(Game game, int NL){
    printf("%d %s %s %s %d %d\n", NL, NameGame(game), Team1(game),
                                  Team2(game), Score1(game), Score2(game));
}


/*First error related to teams*/
void ErrorTeam1(int NL){
    printf("%d Equipa existente.\n", NL);
}


/*Second error related to teams*/
void ErrorTeam2(int NL){
    printf("%d Equipa inexistente.\n", NL);
}


/*First error related to games*/
void ErrorGame1(int NL){
    printf("%d Jogo existente.\n", NL);
}


/*Second error related to games*/
void ErrorGame2(int NL){
    printf("%d Jogo inexistente.\n", NL);
}



/*==========================TEAMS==========================*/
void A(HT_Team Teams, int NL){
    char name[LENGTH];

    /*Reads the name of the team*/
    scanf(" %[^:\n]",name);

    /*If team exists*/
    if(SearchHT_Team(Teams, name) != NULL){
        ErrorTeam1(NL);
    }

    else{
        /*If not creates a new team and adds it to the hashtable*/
        InsertHT_Team(Teams, NewTeam(name));
    }
}


void P(HT_Team Teams, int NL){
    char name[LENGTH];
    Team team;

    /*Reads the name of the team*/
    scanf(" %[^:\n]", name);

    /*Finds the team*/
    team = SearchHT_Team(Teams, name);

    /*If team doesnt exist*/
    if(team == NULL){
        ErrorTeam2(NL);
    }

    /*If exist prints*/
    else{
        PrintTeam(team, NL);
    }
}



/*==========================Games==========================*/
void a(HT_Game Games, HT_Team Teams, List Glist, int NL){
    char game_name[LENGTH];
    char team1[LENGTH];
    char team2[LENGTH];
    int score1;
    int score2;
    Team T1;
    Team T2;

    /*Read the name of the game, team1, team2 and the score*/
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",game_name, team1, team2, &score1, &score2);

    /*Searches for both teams*/
    T1 = SearchHT_Team(Teams, team1);
    T2 = SearchHT_Team(Teams, team2);

    /*If the game already exists*/
    if( SearchHT_Game(Games, game_name) != NULL){
        ErrorGame1(NL);
    }

    /*If one or both teams dont exist*/
    else if(T1 == NULL || T2 == NULL){
        ErrorTeam2(NL);
    }

    else{
        /*Creates a new game and adds it to the hashtable*/
        InsertHT_Game(Games, NewGame(game_name, team1, team2, score1, score2));

        /*If team1 wins the game*/
        if(score1 > score2){
            /*Increases its score*/
            ChangeWins(T1, WIN);
        } 

        /*If team2 wins the game*/
        else if(score2 > score1){
            /*Increases its score*/
            ChangeWins(T2, WIN);
        }

        /*Ads the game to the game list*/
        Append_List(Glist, game_name);
    }
}


void p(HT_Game Games, int NL){
    char name[LENGTH];
    Game game;

    /*Reads the name of the game*/
    scanf(" %[^:\n]", name);

    /*Searches for the game in the hashtable*/
    game = SearchHT_Game(Games, name);

    /*If the game doesnt exist*/
    if(game == NULL){
        ErrorGame2(NL);
    }

    /*If it existe print the game*/
    else{
        PrintGame(game, NL);
    }
}


void r(HT_Game Games, HT_Team Teams, List Glist, int NL){
    char name[LENGTH];
    int score1;
    int score2;
    Team T1;
    Team T2;
    Game game;

    /*Reads the name of the game*/
    scanf(" %[^:\n]", name);

    /*Seatches for the game in the hashtable*/
    game = SearchHT_Game(Games, name);

    /*If the game doesnt exist*/
    if(game == NULL){
        ErrorGame2(NL);
    }

    else{
        /*Obtains the score of the game*/
        score1 = Score1(game);
        score2 = Score2(game);

        /*Obtains the teams of the game*/
        T1 = SearchHT_Team(Teams ,Team1(game));
        T2 = SearchHT_Team(Teams ,Team2(game));

        /*Removes the game from the hashtable and the list*/
        RemoveHT_Game(Games, game);
        Remove_List(Glist, name);

        /*Needs to decrease the number of wins of the team
        that won the game*/
        if(score1 > score2){
            ChangeWins(T1, CORRECTION);
        }

        else if(score1 < score2){
            ChangeWins(T2, CORRECTION);
        }
    }
}


void s(HT_Game Games, HT_Team Teams, int NL){
    char name[LENGTH];
    int score1;
    int score2;
    int old_score1;
    int old_score2;
    Game game;
    Team T1;
    Team T2;

    /*Reads the name of the game and the new score*/
    scanf(" %[^:\n]:%d:%d", name, &score1, &score2);

    /*Searches the game in the hashtable*/
    game = SearchHT_Game(Games, name);

    /*If it doesnt exist*/
    if(game == NULL){
        ErrorGame2(NL);
    }

    else{
        /*Obtains the old score of the game*/
        old_score1 = Score1(game);
        old_score2 = Score2(game);

        /*Changes the score of the game*/
        ChangeScore(game, score1, score2);

        /*Obtains the teams of the game*/
        T1 = SearchHT_Team(Teams ,Team1(game));
        T2 = SearchHT_Team(Teams ,Team2(game));

        /*Changes the number of wins depending on the old score an the new*/
        if(old_score1 > old_score2 && (score1 < score2 || score1 == score2)){
            ChangeWins(T1, CORRECTION);
            if(score1 < score2){
                ChangeWins(T2, WIN);
            }
        }

        else if(old_score1 < old_score2 && (score1 > score2 || score1 == score2)){
            ChangeWins(T2, CORRECTION);
            if(score1 > score2){
                ChangeWins(T1, WIN);
            }
        }

        else if(old_score1 == old_score2){
            if(score1 > score2){
                ChangeWins(T1, WIN);
            }

            else if(score1 < score2){
                ChangeWins(T2, WIN);
            }
        }
    }
}



/*==========================INFORMATION==========================*/
void l(HT_Game Games, List Glist, int NL){
    Node aux = Glist->head;
    Game game;
    char *name;

    /*It goes through the list printing the games*/
    while(aux != NULL){
        /*Name of the game*/
        name = aux->name;

        /*Searches the game in the hashtable*/
        game = SearchHT_Game(Games, name);

        /*Prints*/
        PrintGame(game, NL);

        /*Nest Node in the list*/
        aux = aux->next;
    }
}


void g(HT_Team Teams, int NL){
    /*Buil-in function of hashtable.h
    Not done in here because its excution would break the abstraction*/
    HighestWin(Teams, NL);
}



/*==========================MAIN==========================*/
int main(){
    char command = 0;
    int NL = 0;
    
    /*Creates a new for games list*/
    List Glist = NewList();

    /*Initiates the team hashtable*/
    HT_Team Teams = NewHT_Team(SIZE);

    /*Initiates the game hashtable*/
    HT_Game Games = NewHT_Game(SIZE);


    while(command != 'x'){
        switch(command = getchar()){
        
        /*TEAM COMMANDS*/
            case 'A':{
                NL++;
                A(Teams, NL); 
                break;
            }

            case 'P':{
                NL++;
                P(Teams, NL);
                break;
            }

        /*GAME COMMANDS*/
            case 'a':{
                NL++;
                a(Games, Teams, Glist, NL);
                break;
            }

            case 'p':{
                NL++;
                p(Games, NL);
                break;
            }

            case 'r':{
                NL++;
                r(Games, Teams, Glist, NL);
                break;
            }

            case 's':{
                NL++;
                s(Games, Teams, NL);
                break;
            }

        /*INFORMATION COMMANDS*/
            case 'l':{
                NL++;
                l(Games, Glist, NL);
                break;
            }

            case 'g':{
                NL++;
                g(Teams, NL);
                break;
            }
        }
    }

    /*Frees all allocated memory*/
    DeleteHT_Game(Games);
    DeleteHT_Team(Teams);
    Delete_List(Glist);

    return 0;
}
