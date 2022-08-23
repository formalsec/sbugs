#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hashMatch.h"
#include "hashTeam.h"
#include "strdup.h"
#include "stack.h"

/* Function that adds a match to the matches hashtable */
void addMatch(int commandCounter ,linkMatch *HashTableMatch, 
              linkTeam *HashTableTeam, StackNode **headSTACK, 
              StackNode **tailSTACK){
    char matchName[MAX_LENGTH], team1Name[MAX_LENGTH], team2Name[MAX_LENGTH];
    unsigned int score1, score2;
    int indexMatch, indexTeam1, indexTeam2;
    linkMatch listMatch, head;
    linkTeam list1, list2, team1, team2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%u:%u",
            matchName, team1Name, team2Name, &score1, &score2);

    /* The match is going to be registered in HashTableMatch[indexMatch] */
    indexMatch = hashFunction(matchName);
    /* listMatch contains the first match in HashTableMatchh[indexMatch] 
       ( if there are collisions ) */
    listMatch = HashTableMatch[indexMatch];

    /* indexTeam1 is the index of team1 in the team's Hashtable*/
    indexTeam1 = hashFunction(team1Name);
    list1 = HashTableTeam[indexTeam1];
    /* check1 is -1 if team1 hasn't been registererd yet */
    team1 = getTeam(list1, team1Name);

    /* indexTeam2 is the index of team2 in the team's Hashtable*/
    indexTeam2 = hashFunction(team2Name);
    list2 = HashTableTeam[indexTeam2];
    /* check2 is -1 if team2 hasn't been registererd yet */
    team2 = getTeam(list2, team2Name);

    /* Check if the match has already been registered */
    if (getMatch(listMatch, matchName) != NULL){
        printf("%d Jogo existente.\n", commandCounter);
    }
    /* Check if the teams have both been registered */
    else if (team1 == NULL || team2 == NULL){
        printf("%d Equipa inexistente.\n", commandCounter);
    }

    else {
        /*Check if we are introducing the firs*/
        if (listMatch == NULL){
            head = NULL;
            /* Add a new node at the hashtable's index */
            NewNodeMatch(&head, matchName, team1Name, team2Name, score1, score2);
            HashTableMatch[indexMatch] = head;
            /* Add the match's name to the stack as well*/
            addNode(headSTACK, tailSTACK, matchName);
        } 
        /* In case there's a collision we had the match after 
           the already existing matches */
        else {
            head = listMatch;
            /* Add a new node at the hashtable's index */
            NewNodeMatch(&head, matchName, team1Name, team2Name, score1, score2);
            HashTableMatch[indexMatch] = head;
            /* Add the match's name to the stack as well*/
            addNode(headSTACK, tailSTACK, matchName);
        }
        /* Adjust the team wins according to the score */
        if (whoWonTheGame(score1, score2) == 1){
            /* If team1 wins the game */
            team1->teamWins++;
        } else if (whoWonTheGame(score1, score2) == 2){
            /* If team2 wins the game */
            team2->teamWins++;
        }
    }
}

/* Function that deletes a match from the match hashtable */
void deleteMatch(int commandCounter, linkMatch *HashTableMatch, 
                 linkTeam *HashTableTeam, StackNode **headSTACK, 
                 StackNode **tailSTACK){
    int index, index1, index2, flag = 0;
    char matchName[MAX_LENGTH];
    linkMatch list, temp, prev;
    linkTeam list1, team1, list2, team2;

    /*Get the name of the match we want to delete*/
    scanf(" %[^:\n]", matchName);
    /*Generate the index through the hash function*/
    index = hashFunction(matchName);
    /*list contains only the struct(s) we want to check*/
    list = HashTableMatch[index];
    /*Get the rest of information about the match we want to delete*/
    temp = getMatch(list, matchName);
    /*Check if the given match exists*/
    if (temp == NULL){
        /*At this point we know the match does not exist*/
        printf("%d Jogo inexistente.\n", commandCounter);
    }
    /*The match exists so we want to delete it*/
    else {
        
        /*Refresh the scores*/
        if (temp->score1 > temp->score2){
            index1 = hashFunction(temp->team1);
            list1 = HashTableTeam[index1];
            team1 = getTeam(list1, temp->team1);
            /*If team1 won the game, remove the win*/
            team1->teamWins--;
        }
        else if (temp->score2 > temp->score1){
            index2 = hashFunction(temp->team2);
            list2 = HashTableTeam[index2];
            team2 = getTeam(list2, temp->team2);
            /*If team2 won the game, remove the win*/
            team2->teamWins--;
        }
        /* Delete match from the stack */
        deleteMatchStack(headSTACK, tailSTACK, matchName);
        /*If the hashtable contains only one game at the wanted index set flag 
          to 1 so that we can set the index's content to NULL after deleting the match*/
        if (list->next == NULL) {flag = 1;}
        /*Cycle through the elements of the list*/
        /*temp is an auxiliar variable so that we don't modify the original */
        /*prev is a pointer that points to the struct immediately
          before the one we are checking */
        for (temp=list, prev = NULL; temp != NULL;
             prev = temp, temp = temp->next){
            if (strcmp(matchName, temp->matchName)==0){
                /* If match is at the head of the list */
                if (temp == list){
                    HashTableMatch[index] = temp->next; return;
                }
                else { /* Otherwise keep going through the list */
                    prev->next = temp->next;
                }
                /* Free the memory allocated to the match */
                FreeNodeMatch(temp);
            }
        }
        if (flag == 1){
            /*If the flag is 1 set the content of the hashtable at index to NULL*/
            HashTableMatch[index] = NULL;
        }
    }
}

/* Function that searches for a match in the matches hashtable */
void searchForMatch(int commandCounter, linkMatch *HashTableMatch){
    char matchName[MAX_LENGTH];
    int index;
    linkMatch list, temp;
    
    /* Get the name of the match we want to search */
    scanf(" %[^:\n]", matchName);
    /* If the match has been registered, it is at HashTableMatch[index] */
    index = hashFunction(matchName);
    list = HashTableMatch[index];
    /* temp contains all the info about the match we want */
    temp = getMatch(list, matchName);
    /* Check if the match hasn't been registered */
    if (temp == NULL){
        printf("%d Jogo inexistente.\n", commandCounter);
    }
    /* Proceed if it has */
    else {
        /* Print out the match's info */
        printf("%d %s %s %s %u %u\n",
                commandCounter, matchName, temp->team1, 
                temp->team2, temp->score1, temp->score2);
    }

}

/* Function that changes the score of a match in the hashtable */
void changeScore(int commandCounter, linkMatch *HashTableMatch, 
                 linkTeam *HashTableTeam){
    char matchName[MAX_LENGTH];
    int index, index1, index2, beforeChanging, afterChanging;
    unsigned int score1, score2;
    linkMatch list, temp;
    linkTeam list1, team1, list2, team2;

    scanf(" %[^:\n]:%u:%u", matchName, &score1, &score2);
    /* Get the index of the Hashtable where the match is*/
    index = hashFunction(matchName);
    /* List contains the first match at the given index */
    list = HashTableMatch[index];
     /* temp is the match we want to change the score of */
    temp = getMatch(list, matchName);
    /* Check if the match isn't in the table */
    if (temp == NULL){ printf("%d Jogo inexistente.\n", commandCounter); }
    else {
        /* Check who won the game before changing the score */
        beforeChanging = whoWonTheGame(temp->score1, temp->score2);
        /* Check who won the game after changing the score */
        afterChanging = whoWonTheGame(score1, score2);
        /* Proceed to change the score */
        temp->score1 = score1;
        temp->score2 = score2;
            /* Get team 1 */
            index1 = hashFunction(temp->team1);
            list1 = HashTableTeam[index1];
            team1 = getTeam(list1, temp->team1);
            /* Get team 2 */
            index2 = hashFunction(temp->team2);
            list2 = HashTableTeam[index2];
            team2 = getTeam(list2, temp->team2);
        /* Check if the result of the match changed 
           and if the initial result was a draw */
        if (beforeChanging == 0 && afterChanging != beforeChanging){
            if (afterChanging == 1)  { team1->teamWins++; } /* Team1 wins */
            else                     { team2->teamWins++; } /* Team2 wins */
        }
        /* If the initial result changed AND it wasn't a draw */
        else if (beforeChanging  !=  afterChanging){
            /* Check if the match is a draw */
            if (afterChanging == 0){
                if (beforeChanging == 1){
                    team1->teamWins--;
                }
                else {
                    team2->teamWins--;
                }
            }
            else {
                /* If team 1 had won before changing the score */
                if (beforeChanging == 1){
                    team1->teamWins--;
                    team2->teamWins++;
                }
                /* At this point we know that team 2 had won */
                else {
                    team2->teamWins--;
                    team1->teamWins++;
                }
            }
        }
    }
}

/* Function that adds a team to the teams hashtable */
void addTeam(int commandCounter, linkTeam *HashTableTeam){
    
    char teamName[MAX_LENGTH];
    int index;
    linkTeam list, head;

    /* Get the team's name through scanf */
    scanf(" %[^:\n]", teamName);
    /* Get the index of the hashtable */
    index = hashFunction(teamName);
    /* list contains the first team in HashTableTeam[index] */
    list = HashTableTeam[index];

    /* Check if the team has already been registered */
    if (teamInTable(list, teamName) != -1){
        printf("%d Equipa existente.\n", commandCounter);
    }
    else{
        
        /* If HashTableTeam[index] is NULL */
        if (list == NULL){
            head = NULL;
            NewNodeTeam(&head, teamName);
            HashTableTeam[index] = head;
        } 
        /* In case there's a collision */
        else {
            head = list;
            NewNodeTeam(&head, teamName);
            HashTableTeam[index] = head;
        }
    }
}

/* Function that searches for a team in the teams hashtable */
void searchForTeam(int commandCounter, linkTeam *HashTableTeam){
    
    char teamName[MAX_LENGTH];
    int index;
    linkTeam list, temp;

    /* Get the name of the team we want to search*/
    scanf(" %[^:\n]", teamName);
    /* Get the index of the hashtable */
    index = hashFunction(teamName);
    /* list contains the first team in HashTableTeam[index] */
    list = HashTableTeam[index];
    /* temp contains the info of the team we want */
    temp = getTeam(list, teamName);

    if (temp == NULL){
        /* The team hasn't been registered yet */
        printf("%d Equipa inexistente.\n", commandCounter);
    }
    else {
        
        printf("%d %s %d\n", commandCounter, temp->teamName, temp->teamWins);
    }
}

/* Function that shows all the matches in the database by order of introduction */
void showAllMatches(int commandCounter, linkMatch *HashTableMatch, 
                    StackNode **headSTACK){

    int index;
    StackNode *temp = *headSTACK;
    linkMatch match, list;

    /* Cycle through the matches in the stack until we reach NULL */
    while (isStackEmpty(&temp) != 1){
        /* index contains the index of the hashtable we want to check */
        index = hashFunction(temp->matchName);
        /* list is the first match at HashTableMatch[index] */
        list = HashTableMatch[index];
        /* match contains all the info of the match we want */
        match = getMatch(list, temp->matchName);
        /* Print the match's info */
        printf("%d %s %s %s %u %u\n",
                commandCounter, match->matchName, match->team1, 
                match->team2, match->score1, match->score2);
        /* Get the next match in the stack */
        temp = temp->next;
    }

}

/* Function that lists all the teams with the most wins */
void showBestTeams(int commandCounter, linkTeam *HashTableTeam, 
                   StackNode **StackTeams){
    
    int i, max = getMaxWins(HashTableTeam);
    linkTeam temp, list;
    
    /* Cycle through the team hashtable to get the maximum number of wins */
    for (i=0; i<HASHTABLE_SIZE; i++){
        /* List contains the team at index i */
        list = HashTableTeam[i];
        temp = list;
        /* Cycle through the teams at index i until we reach NULL */
        while (temp != NULL){
            /* Check if the number of wins is the same as max */
            /* Also check if the team isn't already in the stack */
            if (temp->teamWins == max ){
                    /* If the team meets the requirements add it to the stack*/
                    addNodeBegin(StackTeams, temp->teamName);
            }
        /* Get next team */
        temp = temp->next;
        }
    }

    /* Check if the stack is not empty */
    if (isStackEmpty(StackTeams) != 1){
        /* List all teams with max wins */
        printf("%d Melhores %d\n",commandCounter, max);
        /* Sort the linked list using Merge Sort */
        MergeSort(StackTeams);
        /* Print the sorted teams */
        printTeams(commandCounter, StackTeams);
    }
    /* Clear the stack so that if there is any change to the scores 
        the teams listed still meet the requirements */
    DestroyStack(StackTeams);
}

int main(){
    int commandCounter = 0;
    linkMatch *HashTableMatch = CreateTableMatches();
    linkTeam *HashTableTeam = CreateTableTeams();
    StackNode *StackMatches = NULL;
    StackNode *TailMatches = NULL;
    StackNode *StackTeams = NULL;
    char c;
    do{ switch(c = getchar()){
            case 'a':
                /* Add a match to the database */
                ++commandCounter;
                addMatch(commandCounter, HashTableMatch, HashTableTeam, 
                         &StackMatches ,&TailMatches); break;
            case 'l':
                ++commandCounter;
                /* List all the matches in the database */
                showAllMatches(commandCounter, HashTableMatch, &StackMatches); 
                break;
            case 'p':
                /* Search for a given match */
                ++commandCounter;
                searchForMatch(commandCounter, HashTableMatch); break;
            case 'r':
                /* Delete a match from the database */
                ++commandCounter;
                deleteMatch(commandCounter ,HashTableMatch, HashTableTeam, 
                            &StackMatches, &TailMatches); break;
            case 's':
                ++commandCounter;
                /* Change the score of an already existing match */
                changeScore(commandCounter ,HashTableMatch, HashTableTeam); break;
            case 'A':
                ++commandCounter;
                /* Add a team to the database */
                addTeam(commandCounter ,HashTableTeam); break;
            case 'P':
                ++commandCounter;
                /* Search for a given team */
                searchForTeam(commandCounter ,HashTableTeam); break;
            case 'g':
                ++commandCounter;
                /* List all the teams with the most wins */
                showBestTeams(commandCounter, HashTableTeam, &StackTeams); break;
            default:
                break;
        }
    } while (c != 'x');
    /* Free all the memory allocated for the match hashtable */
    DestroyHashMatch(HashTableMatch);
    free(HashTableMatch);
    /* Free all the memory allocated for the team hashtable */
    DestroyHashTeam(HashTableTeam);
    free(HashTableTeam);
    /* Free all the memory allocated for the match stack */
    DestroyStack(&StackMatches);
    free(StackMatches);
    /* Free all the memory allocated for the team stack */
    DestroyStack(&StackTeams);
    free(StackTeams);
    return 0;
}