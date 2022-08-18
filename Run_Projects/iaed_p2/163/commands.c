#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable-structs.h"
#include "commands.h"

#define MAXSTRING 1023
#define MAXSTRING_VECTOR 100


link a(link* hashtable, int size_table, team_ptr team_list
       , link game_list , int nl){
           /*Adds a game to the system*/

    char *aux_name;
    char *aux_team1_name;
    char *aux_team2_name;
    int aux_score_team1;
    int aux_score_team2;
    char c;

    aux_name = (char*) malloc(sizeof(char) * MAXSTRING);
    aux_team1_name = (char*) malloc(sizeof(char) * MAXSTRING);
    aux_team2_name = (char*) malloc(sizeof(char) * MAXSTRING);

    /*gets input*/
    while((c = getchar() != ' '));
    scanf("%[^:]:%[^:]:%[^:]:%d:%d", aux_name, aux_team1_name, 
                        aux_team2_name, &aux_score_team1, &aux_score_team2);

    /*checks if already exists a game like this one*/
    if(LookUpInTable(hashtable, aux_name, size_table) == NULL)
    {
        /*checks if the teams exist*/
        if(LookUpTeams(team_list, aux_team1_name) != NULL){
            if(LookUpTeams(team_list, aux_team2_name) != NULL){

                /*updates variable games won to teams*/
                if(aux_score_team1 > aux_score_team2){
                    LookUpTeams(team_list, aux_team1_name)-> games_won += 1;
                }
                else if(aux_score_team2 > aux_score_team1){
                    LookUpTeams(team_list, aux_team2_name)->games_won += 1;
                }
                /*insert in hashtable*/
                InsertInTable(hashtable, size_table, aux_name, aux_team1_name
                            , aux_team2_name
                            , aux_score_team1, aux_score_team2);
                /*insert in game list for l command*/
                game_list = InsertGameList(game_list,aux_name, aux_team1_name
                            , aux_team2_name
                            , aux_score_team1, aux_score_team2);  
            }
            else{
                printf("%d Equipa inexistente.\n", nl);
            }
        }
        else{
            printf("%d Equipa inexistente.\n", nl);
        }
    }
    else{
        printf("%d Jogo existente.\n", nl);
    }

    free(aux_name);
    free(aux_team1_name);
    free(aux_team2_name);
    return game_list;
}

team_ptr A(team_ptr team_list, int nl){
    /*Adds a team to the system*/

    char *aux_team_name;
    char c;

    aux_team_name = (char*) malloc(sizeof(char) * MAXSTRING);

    /*gets input*/
    while((c = getchar() != ' '));
    scanf("%[^:\n]", aux_team_name);

    /*checks if already exists a team like this one*/
    if(LookUpTeams(team_list, aux_team_name) == NULL){
        team_list = InsertBeginTeamList(team_list, aux_team_name);
    }
    else{
        printf("%d Equipa existente.\n", nl);
    }

    free(aux_team_name);
    return team_list;
}

void p(link* hashtable, int size_table, int nl){
    /*finds game by name*/

    char *aux_game_name;
    char c;


    aux_game_name = (char*) malloc(sizeof(char) * MAXSTRING);

    /*gets input*/
    while((c = getchar() != ' '));
    scanf("%[^:\n]", aux_game_name);

    /*checks if game exists*/
    if(LookUpInTable(hashtable, aux_game_name, size_table) != NULL){
        game_ptr x = LookUpInTable(hashtable, aux_game_name, size_table);
        printf("%d %s %s %s %d %d\n", nl, x->game_name
                        , x->team1
                        , x->team2
                        , x->score_team1
                        , x->score_team2);
    }
    else{
        printf("%d Jogo inexistente.\n", nl);
    }

    free(aux_game_name);
}

void P(team_ptr team_list, int nl){
    /*finds a team by name*/
    char *aux_team_name;
    char c;

    aux_team_name = (char*) malloc(sizeof(char) * MAXSTRING);

    /*gets input*/
    while((c = getchar() != ' '));
    scanf("%[^:\n]", aux_team_name);

    /*checks if team exists*/
    if(LookUpTeams(team_list, aux_team_name) != NULL){
        team_ptr x = LookUpTeams(team_list, aux_team_name);
        printf("%d %s %d\n", nl
            , x->team_name
            , x->games_won);

    }
    else{
        printf("%d Equipa inexistente.\n", nl);
    }

    free(aux_team_name);
}

void l(link* hashtable, int size_table,link game_list, int nl){
    /*lists games by order of insertion*/
    link x;
    for(x=game_list; x != NULL; x = x->next){
        if(LookUpInTable(hashtable, x->this_game->game_name, size_table) != NULL){
            game_ptr g = LookUpInTable(hashtable, x->this_game->game_name, size_table);
            printf("%d %s %s %s %d %d\n", nl, g->game_name
                                                , g->team1
                                                , g->team2
                                                , g->score_team1
                                                , g->score_team2);
        }

    }


}

link r(link* hashtable, int size_table
        , link game_list, team_ptr team_list, int nl){
            /*Deletes a game by name*/

    char *aux_game_name;
    char c;


    aux_game_name = (char*) malloc(sizeof(char) * MAXSTRING);

    /*gets input*/
    while((c = getchar() != ' '));
    scanf("%[^:\n]", aux_game_name);

    /*checks if game exists*/
    if(LookUpInTable(hashtable, aux_game_name, size_table) != NULL){
        
        /*makes changes to the variable games won to the teams*/
        if(LookUpTeams(team_list
        , LookUpInTable(hashtable, aux_game_name, size_table)->team1)->games_won > LookUpTeams(team_list
        , LookUpInTable(hashtable, aux_game_name, size_table)->team2)->games_won){

            LookUpTeams(team_list
        , LookUpInTable(hashtable, aux_game_name, size_table)->team1)->games_won -= 1;
        }
        else if(LookUpTeams(team_list
        , LookUpInTable(hashtable, aux_game_name, size_table)->team1)->games_won < LookUpTeams(team_list
        , LookUpInTable(hashtable, aux_game_name, size_table)->team2)->games_won){
             LookUpTeams(team_list
        , LookUpInTable(hashtable, aux_game_name, size_table)->team2)->games_won -= 1;
        }
        /*removes*/
        game_list = Remove(game_list, aux_game_name);
        RemoveFromTable(hashtable, size_table, aux_game_name);
    }
    else{
        printf("%d Jogo inexistente.\n", nl);
    }

    free(aux_game_name);
    return game_list;
}

link s(link* hashtable, int size_table, link game_list
        , team_ptr team_list, int nl){
            /*changes score of a game by name*/

    char *aux_game_name;
    int aux_score_team1;
    int aux_score_team2;
    char c;

    aux_game_name = (char*) malloc(sizeof(char) * MAXSTRING);

    /*gets input*/
    while((c = getchar() != ' '));
    scanf("%[^:]:%d:%d", aux_game_name, 
                        &aux_score_team1,&aux_score_team2);

    if(LookUpInTable(hashtable, aux_game_name, size_table) != NULL){
        if(LookUpInTable(hashtable, aux_game_name, size_table)->score_team1 < LookUpInTable(hashtable, aux_game_name, size_table)->score_team2){

            if(aux_score_team1 > aux_score_team2)
                LookUpTeams(team_list
                    , LookUpInTable(hashtable, aux_game_name, size_table)->team2)->games_won -= 1;

        }
        else if(LookUpInTable(hashtable, aux_game_name, size_table)->score_team1 > LookUpInTable(hashtable, aux_game_name, size_table)->score_team2){

            if(aux_score_team2 > aux_score_team1)
                LookUpTeams(team_list
                    , LookUpInTable(hashtable, aux_game_name, size_table)->team1)->games_won -= 1;

        }

        LookUpInTable(hashtable, aux_game_name, size_table)->score_team1 = aux_score_team1;
        LookUpInTable(hashtable, aux_game_name, size_table)->score_team2 = aux_score_team2;

        game_list = ChangeScore(game_list, aux_game_name
                        , aux_score_team1, aux_score_team2);
 
    }
    else{
        printf("%d Jogo inexistente.\n", nl);
    }

    free(aux_game_name);
    return game_list;  
}


int compareStr(const void *pa, const void *pb){
    /*compares strings*/
    int r = strcmp(pa, pb);
    if(r == 0)
        return 0;
    else
        if(r>0)
            return 1;
        else
            return -1;
}

void g(team_ptr team_list, int nl){
    /*finds the teams that won the most 
        and prints by alphabetic order*/
    
    int biggest_n_games_won = 0;
    char * team_names[MAXSTRING_VECTOR];
    int teams_array_size = 0;
    int i;

    /*checks if the team list isnt empty*/
    if(team_list != NULL){

        /*gets the biggest number of games won*/
        team_ptr x;
        for(x= team_list; x!= NULL; x = x->next){
            if(x->games_won >= biggest_n_games_won)
                biggest_n_games_won = x->games_won;
        }

        /*assigns array to sort size*/
        for(x= team_list; x!= NULL; x = x->next){
            if(x->games_won == biggest_n_games_won)
                teams_array_size++;
        }

        /*Fills array with the teams*/
        for(i = 0, x= team_list; x!= NULL; i++, x = x->next){
            if(x->games_won == biggest_n_games_won){
                team_names[i] = (char*) malloc(sizeof(char) * (strlen(x->team_name)+1));
                strcpy(team_names[i], x->team_name);
            }
        }

        qsort(team_names, teams_array_size, sizeof(char*), compareStr);

        printf("%d Melhores %d\n", nl, biggest_n_games_won);
        for(i = 0; i < teams_array_size; i++){
            printf("%d * %s\n", nl, team_names[i]);
            free(team_names[i]);
        }
    }
}