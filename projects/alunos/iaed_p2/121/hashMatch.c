#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "hashMatch.h"
#include "strdup.h"

/* Function that returns the ASCII code for a given char in a string */
int CharAt(char *text, int pos){
    return text[pos];
}

/* Function that calculates the index of a given string in its respective hashtable*/
int hashFunction(char *text){
    unsigned int i;
    int final = 7;
    for (i=0; i < strlen(text); i++){
        final = G*final + CharAt(text, i);
    }
    /* If final is < 0 */
    if (final < 0){
        final *= -1;
    }
    return final % HASHTABLE_SIZE;
}

/* Function to add a new node to the matches hashtable */
void NewNodeMatch(linkMatch *head, char *matchName, char *team1,
                        char *team2, unsigned int score1, unsigned int score2){
    /* Allocate memory for the struct */
    linkMatch new_node = (linkMatch)can_fail_malloc(sizeof(struct nodeMatch));
    /* Allocate memory for all the strings in the struct */
    new_node->matchName = mystrdup(matchName);
    new_node->team1 = mystrdup(team1);
    new_node->team2 = mystrdup(team2);
    new_node->score1 = score1;
    new_node->score2 = score2;
    new_node->next = NULL;

    /* If the list is empty, insert at the head */
    if (*head == NULL){
        *head = new_node;
    } 
    /* If there are collision insert at the end of the linkedlist */
    else {
        new_node->next = *head;
        *head = new_node;
    }
}

/*Function that returns a match given its position on the list*/
linkMatch getMatch(linkMatch list, char *matchName){
    linkMatch temp;
    /* Cycle through the matches in the list until we reach the match we want*/
    for (temp = list; temp != NULL; temp = temp->next){
        /* Check if the match's name is the same we are looking for */
        if (strcmp(matchName, temp->matchName)==0)
            /* Return the match */
            return temp;
    }
    /*Returns NULL if the match is not in the hashtable*/
    return NULL;
}

/*Auxiliar functions that frees all the memory allocated for a match*/
void FreeNodeMatch(linkMatch toDelete){
    if (toDelete != NULL){
        /* Free all the memory allocated for a node */
        free(toDelete->matchName);
        free(toDelete->team1);
        free(toDelete->team2);
        free(toDelete);
    }
}

/*Function that creates a hashtable for all the matches*/
linkMatch *CreateTableMatches(){
    int i;
    /* Allocate the memory necessary for the hashtable */
    linkMatch *hashtable = can_fail_calloc(HASHTABLE_SIZE, sizeof(struct nodeMatch));
    /* Initialize the hashtable to NULL */
    for (i = 0; i < HASHTABLE_SIZE; i++){hashtable[i] = NULL;}
    return hashtable;
}

/* Function that given a score calculates the winner */
int whoWonTheGame(int score1, int score2){
    /* If team1 won the game */
    if (score1 > score2)
        return 1;
    /* If team2 won the game */
    else if (score1 < score2)
        return 2;
    /* Draw */
    else 
        return 0;
}

/* Function that destroys (frees) the Hashtable */
void DestroyHashMatch(linkMatch *HashTableMatch){
    int i;
    linkMatch list, next, temp;
    /* Cycle through every index of the hashtable */
    for (i=0; i<HASHTABLE_SIZE; i++){
        list = HashTableMatch[i];
        temp = list;
        /* If there are matches, free the memory allocated */
        while (temp != NULL){
            next = temp->next;
            FreeNodeMatch(temp);
            temp = next;
        }
        list = NULL;
    }
}