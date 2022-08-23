#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipas.h"
#include "jogos.h"

/*Constants for the max size of a string, and the module of the hash tables*/
#define MAX_SIZE 1024
#define CONST_HASH 739


/*Function prototypes*/
void new_team();
void search_team_in_hash();
NodeGame * new_game();
void search_in_games_hash();
void change_score();
void print_games();
NodeGame * remove_game();
void more_victories();
char *str_dup();
int cmpstr();

/*NOTE: The structures used to save the games and teams in this program are:
            -Hash tables with external chaining for teams and games;
            -A singly linked list which contains pointers to the games
             (which I call "references") in the hash table of games
             that is ordered by order of insertion in the program.*/

int main()
{
    /*Variable initialization for the line 
    of input to which output corresponds*/
    unsigned long int NL = 1;
    
    char funcao;

    int Mod =  CONST_HASH;

    /*Initialization of the singly linked list that contains the pointer
      to each team in the data base by order of insertion in the program*/
    NodeGame *listRefs = NULL;
    
    /*Allocation of memory for the hash table that will contain all the teams
      that will be added to the program*/
    NodeTeam **headsT = (NodeTeam**) malloc(Mod*sizeof(NodeTeam));
    
    /*Allocation of memory for the hash table that will contain all the games
      that will be added to the program*/
    NodeGame **headsG = (NodeGame**) malloc(Mod*sizeof(NodeGame));

    /*Initialisation of the hash table that will contain the teams*/
    init_hash_teams(headsT, Mod);

    /*Initialisation of the hash table that will contain the games*/   
    init_hash_games(headsG,Mod);
    

    
    
    while((funcao = getchar()) != EOF){
        switch(funcao){   
            case('A'):
                /* Command -INPUT: name of the team(*char);
                           
                           -OUTPUT: nothing,except ERRORS.
                */
                new_team(headsT,Mod,NL);
                NL++;
                break;
            case('P'):
                /* Command -INPUT:  name of the team(*char);
                           
                           -OUTPUT: name of the team(*char), 
                                    no. of victories(int), or ERRORS.
                */
                search_team_in_hash(headsT,Mod,NL);
                NL++;
                break;
            case('a'):
                /* Command -INPUT:  name of the game(*char),
                                    name of team1(*char),
                                    name of team2(*char),
                                    score of team1(int)
                                    score of team2(int);
                           
                           -OUTPUT: nothing, except ERRORS;
                */
                listRefs = new_game(headsG,listRefs,headsT,Mod,NL);
                NL++;
                break;
            case('p'):
                /* Command -INPUT:  name of the team(*char);
                           
                           -OUTPUT: name of the game(*char),
                                    name of team1(*char),
                                    name of team2(*char),
                                    score of team1(int)
                                    score of team2(int), or ERRORS;
                */
                search_in_games_hash(headsG,Mod,NL);
                NL++;
                break;
            case('l'):
                /* Command -INPUT: nothing;
                           
                           -OUTPUT: name of the game(*char),
                                    name of team1(*char),
                                    name of team2(*char),
                                    score of team1(int)
                                    score of team2(int), of each team;
                */
                print_games(listRefs,NL);
                NL++;
                break;
            case('s'):
                /* Command -INPUT:  name of the game(*char),
                                    score of team1(int),
                                    score of team2(int);
            
                           -OUTPUT: nothing, except ERROR;
                */
                change_score(headsG,headsT,Mod,NL);
                NL++;
                break;
            case('r'):
                /* Command -INPUT:  name of the game(*char);
            
                           -OUTPUT: nothing, except ERROR;
                */
                listRefs = remove_game(headsG,listRefs,headsT,Mod,NL);
                NL++;
                break;
            case('g'):
                /* Command -INPUT:  nothing;
            
                           -OUTPUT: name of the team(*char), 
                                    of the teams with the most teams.
                */
                more_victories(headsT,Mod,NL);
                NL++;
                break;
            case('x'):
                /*Routine to free the memory of the program, when it is 
                  commanded to end*/
                destroy_hash_teams(headsT,Mod);
                destroy_refs_list(listRefs);
                destroy_hash_games(headsG,Mod);
            
                free(headsT);
                free(headsG);

                return 0;
                break;
            
        }
    }
    return 0;
}


/* Function that adds a new team to the system,
   namely to the hash table of teams*/
void new_team(NodeTeam **headsT,int mod,unsigned long int NL)
{
    char nameTeam[MAX_SIZE];
    Team *errorCheck;
    Team *newTeam;
    scanf(" %[^:\n]", nameTeam);

    /*Condition that verifies if the team already exists in the database*/
    errorCheck = hash_search_team(headsT,nameTeam,mod);
    if(errorCheck != NULL){
        printf("%lu Equipa existente.\n", NL);
        return;
    }

    newTeam = create_team(nameTeam);

    hash_insert_team(headsT,newTeam,mod);

}

/*Function that searches for a team in the database, namely in the
  hash table of teams, and prints out the name and the team victories*/
void search_team_in_hash(NodeTeam **headsT,int mod,unsigned long int NL)
{
    char nameTeam[MAX_SIZE];
    Team *teamHash;
    scanf(" %[^:\n]", nameTeam);

    teamHash = hash_search_team(headsT,nameTeam,mod);
    
    /*Condition that verifies if the team already exists in the database*/
    if(teamHash == NULL){
        printf("%lu Equipa inexistente.\n", NL);
        return;
    }

    printf("%lu %s %d\n", NL, teamHash->name, teamHash->victories);

}

/* Function that adds a new team to the system,
   namely to the hash table of teams, and the
   reference list that is sorted by order of insertion
   in the system*/
NodeGame * new_game(NodeGame **headsG,NodeGame *headRefs,
                    NodeTeam **headsT,int mod,unsigned long int NL)
{
    char nameGame[MAX_SIZE];
    char nameTeam1[MAX_SIZE];
    char nameTeam2[MAX_SIZE];
    int score1, score2;
    Team *team1, *team2;
    Game *errorCheck, *newGame;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nameGame,
                                            nameTeam1,
                                            nameTeam2,
                                            &score1,
                                            &score2);

    /*Condition that verifies if the game already exists in the database*/
    errorCheck = hash_search_game(headsG,nameGame,mod);
    if(errorCheck != NULL){
        printf("%lu Jogo existente.\n",NL);
        return headRefs;
    }

    /*Condition that verifies if both teams are in the database,
      if not, then return an error
    */
    team1 = hash_search_team(headsT,nameTeam1,mod);
    team2 = hash_search_team(headsT,nameTeam2,mod);
    if(team1 == NULL || team2 == NULL){
        printf("%lu Equipa inexistente.\n", NL);
        return headRefs;
    }
    
    /*If team1 has more goals than team2, then add a victory
      to team1 in the hash table of teams
    */
    if(score1 > score2){
        team1->victories++;
    }

    /*Else, if team2 has more goals than team2, then add a victory
      to team2 in the hash table of teams
    */
    else if(score2 > score1){
        team2->victories++;
    }

    newGame = create_game(nameGame,nameTeam1,nameTeam2,score1,score2);

    /*adding the game to the reference list and the hash table of games*/
    hash_insert_game(headsG,newGame,mod);
    headRefs = hash_put_begin_games(headRefs,newGame);

    return headRefs;


}

/*Function that searches for a game in the database, namely in the
  hash table of games, and prints out the name of the game, the names of
  the teams that are competing in the game, and the scoreboard of the game*/
void search_in_games_hash(NodeGame **headsG,int mod,unsigned long int NL)
{
    char nameGame[MAX_SIZE];
    Game *gameHash;

    scanf(" %[^:\n]", nameGame);

    gameHash = hash_search_game(headsG,nameGame,mod);

    /*Condition that verifies if the game is in the hash of games*/
    if(gameHash == NULL){
        printf("%lu Jogo inexistente.\n",NL);
        return;
    }

    printf("%lu %s %s %s %d %d\n",NL,gameHash->name,
                                  gameHash->team1,
                                  gameHash->team2,
                                  gameHash->score1,
                                  gameHash->score2);

}

/*Function that changes the score of a game, and alters the current winner
  of the game if the score changes which team is winning, or if the game is tied*/
void change_score(NodeGame **headsG,NodeTeam **headsT,int mod,unsigned long int NL)
{
    char nameGame[MAX_SIZE];
    char *nameTeam1,*nameTeam2;
    int score1,score2;
    Team *team1, *team2;
    Game *game;
    
    scanf(" %[^:\n]:%d:%d",nameGame,&score1,&score2);

    game = hash_search_game(headsG,nameGame,mod);
    
    /*Condition that verifies if the game is in the hash of games*/
    if(game == NULL){
        printf("%lu Jogo inexistente.\n", NL);
        return;
    }

    nameTeam1 = game->team1;
    nameTeam2 = game->team2;

    team1 = hash_search_team(headsT,nameTeam1,mod);
    team2 = hash_search_team(headsT,nameTeam2,mod);

    if(score1 > score2 && game->score2 > game->score1){
        team1->victories++;
        team2->victories--;
    }
    else if(score2 > score1 && game->score1 > game->score2){
        team1->victories--;
        team2->victories++;
    }
    else if(score1 > score2 && game->score1 == game->score2){
        team1->victories++;
    }
    else if(score2 > score1 && game->score1 == game->score2){
        team2->victories++;
    }
    else if(score1 == score2 && game->score1 > game->score2){
        team1->victories--;
    }
    else if(score1 == score2 && game->score2 > game->score1){
        team2->victories--;
    }

    hash_change_score(headsG,nameGame,score1,score2,mod);

}

/*Recursive function that uses delayed operations to print out the games
  (since it needs to be in the reversed order of head to tail) by the
  order of insertion in the database, using the singly linked list of
  references(pointers) to the games on the hash table of games*/
void print_games(NodeGame *head,unsigned long int NL)
{

    if(head == NULL){
        return;
    }

    print_games(head->next,NL);

    printf("%lu %s %s %s %d %d\n",NL,
                                  head->game->name,
                                  head->game->team1,
                                  head->game->team2,
                                  head->game->score1,
                                  head->game->score2);
}


/*Function that removes a game from the hash table of games, and also the
  pointer of wanted game from the list of references*/
NodeGame * remove_game(NodeGame **headsGames,NodeGame *headRefs,
                       NodeTeam **headsTeams,int mod,unsigned long int NL)
{
    char nameGame[MAX_SIZE];
    Game *gameHash;
    Team *teamAux;
    int score1,score2;

    scanf(" %[^:\n]", nameGame);

    gameHash = hash_search_game(headsGames,nameGame,mod);

    /*Condition that  verifies if the game is in the hash of games*/
    if(gameHash == NULL){
        printf("%lu Jogo inexistente.\n",NL);
        return headRefs;
    }

    score1 = gameHash->score1;
    score2 = gameHash->score2;

    /*If team1 is winning, then remove the win from the hash of teams*/
    if(score1 > score2){
        teamAux = hash_search_team(headsTeams,gameHash->team1,mod);
        teamAux->victories--;
    }
    /*If team2 is winning, then remove the win from the hash of teams*/
    else if(score2 > score1){
        teamAux = hash_search_team(headsTeams,gameHash->team2,mod);
        teamAux->victories--;
    }

    /*Removing the pointer to the hash table of games from the refernce list*/
    headRefs = remove_el_list(headRefs,nameGame);

    /*Removing the game from the hash table*/
    hash_remove_game(headsGames,nameGame,mod);

    return headRefs;
}

/*Function that prints out all the games of the database that have the most
  number of victories by lexicographic order*/
void more_victories(NodeTeam **headsT, int mod, unsigned long int NL)
{
    int currentMoreWins = 0;
    int i,j;
    NodeTeam *current;
    char **teamsMoreWins;

    int numTeams = 0;

    /*for cycle that will iterate the hash table of games, checking
      for the number of most wins by any team*/
    for(i = 0; i < mod; i++){
        current = headsT[i];
        while(current != NULL){
            if(currentMoreWins < current->team->victories){
                currentMoreWins = current->team->victories;
                numTeams = 0;
            }
            if(currentMoreWins == current->team->victories){
                numTeams++;
            }
            current = current->next;
        }
    }

    /*if there aren't any teams with a victory,
      the command shall not return nothing*/
    if(numTeams == 0){
        return;
    }

    j = 0;

    /*Allocating memory for a singly linked list of team names
      that will contain the teams with most wins*/
    teamsMoreWins = (char**) malloc(sizeof(char*) * numTeams);

    /*for cycle that will iterate the hash table of teams, to add the
      teams with most wins to the linked list created*/
    for(i = 0; i < mod; i++){
        current = headsT[i];
        while(current != NULL){
            if(currentMoreWins == current->team->victories){
                teamsMoreWins[j] = current->team->name;
                j++;
            }
            current = current->next;
        }
    }

    /*sorting the teams by lexicographic order*/
    qsort(teamsMoreWins,numTeams,sizeof(char*),cmpstr);


    /*printing the name of the teams in the linked list*/
    printf("%lu Melhores %d\n",NL,currentMoreWins);
    for(i = 0; i < numTeams;i++){
        if(teamsMoreWins[i] != NULL)
            printf("%lu * %s\n",NL,teamsMoreWins[i]);
    }

    /*freeing the memory of the auxiliar linked lists*/
    free(teamsMoreWins);


}



/*Auxiliary function for qsort to sort by lexicographic order*/
int cmpstr(const void *a, const void *b)
{
   return strcmp(*(char **)a, *(char **)b);
}

