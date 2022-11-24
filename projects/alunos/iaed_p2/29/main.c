#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "game.h"


#define MAX_INPUT_SIZE 1024
#define MAX_ENTERED 4100

ent * hashGames;
tent * hashTeams;
int debug;
int end;


void processaLinha(char * input){
    
    switch(input[0])
    {
        case 'a':
        {
            int final, scoretot[2];
            char name[MAX_INPUT_SIZE], team1[MAX_INPUT_SIZE], team2[MAX_INPUT_SIZE], score1[4], score2[4];
            /*strtok(input, " ");*/
            strcpy(name, strtok(input + 2,":"));
            strcpy(team1, strtok(NULL, ":"));
            strcpy(team2, strtok(NULL, ":"));
            strcpy(score1, strtok(NULL, ":"));
            strcpy(score2, strtok(NULL, "\n"));
            
            scoretot[0] = atoi(score1);
            scoretot[1] = atoi(score2);
            final = htGame_insert(hashGames, hashTeams, name, team1, team2, scoretot);
            if(final == -1) printf("%d Equipa inexistente.\n", debug);
            if(final == 0) printf("%d Jogo existente.\n", debug);
            break;
        }
        case 'A':
        {
            int final;
            char name[MAX_INPUT_SIZE];
            strcpy(name, strtok(input + 2,"\n"));
            final = htTeam_insert(hashTeams, name);
            if(final == 0) printf("%d Equipa existente.\n", debug);
            break;
        }
        case 'l':
        {
            printGames(debug);
            break;
        }
        case 'p':
        {
            game * test;
            char name[MAX_INPUT_SIZE];
            strcpy(name, strtok(input + 2,"\n"));
            test = htGame_search(hashGames, name);
            if(test == NULL){
                printf("%d Jogo inexistente.\n", debug);
            } else {
                printf("%d %s %s %s %d %d\n", debug, name, test->team[0]->name, test->team[1]->name, test->score[0],test->score[1]);
            }
            break;
        }
        case 'r':
        {
            char name[MAX_INPUT_SIZE];
            strcpy(name, strtok(input + 2,"\n"));
            if(htGame_search(hashGames, name) == NULL){
                printf("%d Jogo inexistente.\n", debug);
                break;
            }
            htGame_delete(hashGames, name);
            break;
        }
        case 's':
        {
            /* Change score */
            int s1,s2;
            char name[MAX_INPUT_SIZE], score1[4], score2[4];
            game * t;
            strtok(input, " ");
            strcpy(name, strtok(NULL,":"));
            strcpy(score1, strtok(NULL, ":"));
            strcpy(score2, strtok(NULL, "\n"));
            s1 = atoi(score1);
            s2 = atoi(score2);
            t = htGame_search(hashGames, name);
            if(t == NULL){
                printf("%d Jogo inexistente.\n", debug);
                break;
            }
            htGame_change(t, s1, s2);
            break;
        }
        case 'P':
        {
            team * t;
            char name[MAX_INPUT_SIZE];
            strcpy(name, strtok(input + 2,"\n"));
            t = htTeam_search(hashTeams, name);
            if(t == NULL){
                printf("%d Equipa inexistente.\n", debug);
                break;
            }
            printf("%d %s %d\n",debug, name, t->wins);
            break;
        }
        case 'g':
        {
            presentOrdered(debug);
            break;
        }
        case 'x':
        {
            end = 1;
            break;
        }
    }
        
            
}
int main(){
    hashGames = htGame_create();
    hashTeams = htTeam_create();
    dummy = can_fail_malloc(sizeof(game));
    dummy->score[0] = -1;
    dummy->name = NULL;
    debug = 0;
    end = 0;
    do{
        char linha[MAX_ENTERED];
        debug++;
        /* Leitura de inputs */
        fgets(linha, MAX_ENTERED, stdin);
        processaLinha(linha);
    }while(end == 0);
    return 0;
}