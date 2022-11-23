#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include "team.h"
#include "game.h"



int main(){
    char *command,*gameName,*team,*team2; 
    int  nGames=1,nCommand=1,score1,score2,M,MT1,MT2,i;
    TeamNode *t,*t2;
    GameNode *g;
    TeamNode* teamHashTable[MT];
    GameNode* gameHashTable[MG];
    
    /*inicializes the hashtables*/
    for(i=0;i<=MT-1;i++){
        teamHashTable[i]=NULL;
    }
    for(i=0;i<=MG-1;i++){
        gameHashTable[i]=NULL;
    }

    /*the command is only one letter*/
    command=can_fail_malloc(sizeof(char));
    do{
    /*scans the first letter, and skipps the spaces after*/
    scanf("%s%*[ ]",command);
    /*ignores the space after the command*/
    switch (*command){
        case 'a':
            gameName=can_fail_malloc(1023*sizeof(char));
            team=can_fail_malloc(1023*sizeof(char));
            team2=can_fail_malloc(1023*sizeof(char));
            /*scans the first string (until some : or \n appears)and skips all the : and \n*/
            scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d",gameName,team,team2,&score1,&score2);
            M=hashGame(gameName);
            MT1=hashTeam(team);
            MT2=hashTeam(team2);
            /*searches for the team1*/
            if(teamHashTable[MT1]==NULL){
                printf("%d Equipa inexistente.\n",nCommand);
                free(gameName);free(team);free(team2);
                break;
            }
            else{
                t=searchTeam(teamHashTable[MT1],team);
                if(t->exists==0){
                    printf("%d Equipa inexistente.\n",nCommand);
                    free(gameName);free(team);free(team2);
                    break;
                }
                else{
                    /*search for team2*/
                    if(teamHashTable[MT2]==NULL){
                        printf("%d Equipa inexistente.\n",nCommand);
                        free(gameName);free(team);free(team2);
                        break;
                    }
                    else{
                        t2=searchTeam(teamHashTable[MT2],team2);
                        if(t->exists==0){
                            printf("%d Equipa inexistente.\n",nCommand);
                            free(gameName);free(team);free(team2);
                            break;
                        }
                        else{
                            /*if the game is the first in its list*/
                            if(gameHashTable[M]==NULL){
                                gameHashTable[M]=addGame(NULL,gameName,t,t2,score1,score2,nGames);
                                nGames++;
                            }
                            else{
                                /*if the game already exists*/
                                g=searchGame(gameHashTable[M],gameName);
                                if(g->id!=0){
                                    printf("%d Jogo existente.\n",nCommand);
                                    free(gameName);free(team);free(team2);
                                    break;    
                                }
                                /*if the game didnt exist, add it*/
                                else{
                                    gameHashTable[M]=addGame(gameHashTable[M],gameName,t,t2,score1,score2,nGames);
                                }                                
                            }
                        }
                    }
                }
            }
            free(gameName);free(team);free(team2);
            nCommand++;
            break;

        case 'p':
            gameName=can_fail_malloc(1023*sizeof(char));
            scanf("%[^:\n]",gameName);
            M=hashGame(gameName);
            /*if the list is empty, there's no such game*/
            if(gameHashTable[M]==NULL){
                printf("%d Jogo inexistente.",nCommand);
                free(gameName);
                nCommand++;
                break;
            }
            else{              
                g=searchGame(gameHashTable[M],gameName);
                /*if the search function found a game*/
                if(g->id!=0){
                    printf("%d %s %s %s %d %d",nCommand,gameName,g->team1->name,g->team2->name,g->score1,g->score2);
                }
                /*if the search function didn't find anything*/
                else{
                    printf("%d Jogo inexistente.",nCommand);
                    free(gameName);
                    nCommand++;
                    break;
                }
            }
            free(gameName);
            nCommand++;
            break;

        case 'r':
            gameName=can_fail_malloc(1023*sizeof(char));
            scanf("%[^:\n]",gameName);
            M=hashGame(gameName);
            /*searches for the game on the hash table*/
            if(gameHashTable[M]==NULL){
                printf("%d Jogo inexistente.",nCommand);
                free(gameName);
                nCommand++;
                break;
            }
            else{
                g=searchGame(gameHashTable[M],gameName);
                if(g->id!=0){
                    /*if the game exists, delete it*/
                    gameHashTable[M]=deleteGame(gameHashTable[M],g);
                    nGames--;
                }
                else{
                    printf("%d Jogo inexistente.",nCommand);
                    free(gameName);
                    nCommand++;
                    break;
                }
            }
            free(gameName);
            nCommand++;
            break;

        case 's':
            gameName=can_fail_malloc(1023*sizeof(char));
            scanf("%[^:\n]:%d:%d",gameName,&score1,&score2);
            M=hashGame(gameName);
            /*searches for the game on the hashtable*/
            if(gameHashTable[M]==NULL){
                printf("%d Jogo inexistente.",nCommand);
                free(gameName);
                nCommand++;
                break;
            }
            else{
                g=searchGame(gameHashTable[M],gameName);
                if(g->id!=0)
                    /*if found, change the score*/
                    changeScore(g,score1,score2);
                else{
                    printf("%d Jogo inexistente.",nCommand);
                    free(gameName);
                    nCommand++;
                    break;
                }
            }
            free(gameName);
            nCommand++;
            break;

        case 'A':
            team=can_fail_malloc(1023*sizeof(char));
            scanf("%s",team);
            M=hashTeam(team);            
            /*if its not the first team in the node*/
            if(teamHashTable[M]!=NULL){
                /*searches if there's a team with that name*/
                t=searchTeam(teamHashTable[M],team);
                if(t->exists==0)
                    teamHashTable[M]=addTeam(teamHashTable[M],team);
                /*print error message if there is a team with that name*/
                else{
                    printf("%d Equipa existente.\n",nCommand);
                    free(team);
                    nCommand++;
                    break;
                }
            }
            else{
                /*it's the first element being inserted on the table*/
                teamHashTable[M]=addTeam(NULL,team);
            }
            free(team);
            nCommand++;
            break;
        
        case 'P':
            team=can_fail_malloc(1023*sizeof(char));
            scanf("%[^:\n]",team);
            M=hashTeam(team);
            /*if it's not the first team in the hashtable,search for it*/
            if(teamHashTable[M]!=NULL){
                t=searchTeam(teamHashTable[M],team);
            }
            else{
                /*then there's no team with that name*/
                printf("%d Equipa inexistente.\n",nCommand);
                free(team);
                nCommand++;
                break;
            }
            /*if search didnt return error, print the expected output*/
            if(t->exists==1)
                printf("%d %s %d\n",nCommand,t->name,t->wins);
            else
            /*then there wasn't a team with that name*/
                printf("%d Equipa inexistente.",nCommand);
            free(team);
            nCommand++;
            break;

        default:
            return 0;
    }
    }while(*command!='x');
    return 0;
}