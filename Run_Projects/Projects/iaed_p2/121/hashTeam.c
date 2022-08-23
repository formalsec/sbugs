#include <stdlib.h>
#include <string.h>
#include "hashTeam.h"
#include "strdup.h"


/* Function to add a new node to the teams hashtable */
void NewNodeTeam(linkTeam *head, char *teamName){
    /* Allocate the memory for the struct */
    linkTeam new_node = (linkTeam)malloc(sizeof(struct nodeTeam));
    new_node->teamName = mystrdup(teamName);
    new_node->teamWins = 0;
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

/* Function that creates a hashtable for all the teams */
linkTeam *CreateTableTeams(){
    int i;
    /* Allocate the necessary memory for the hashtable */
    linkTeam *hashtable = calloc(HASHTABLE_SIZE, sizeof(struct nodeTeam));
    /*Initialize all hashtable positions with NULL*/
    for (i = 0; i < HASHTABLE_SIZE; i++){hashtable[i] = NULL;}
    return hashtable;
}

/* Function that returns a team given it's name */
linkTeam getTeam(linkTeam list, char *teamName){
    linkTeam temp;
    /* Cycle through the teams in list */
    for (temp = list; temp != NULL; temp = temp->next){
        /* If it has the we are looking for return the team */
        if (strcmp(teamName,temp->teamName)==0)
            return temp;
    }
    /* Otherwise return NULL */
    return NULL;
}

/* Given the head of list and the team's name check if 
   the match has already been put in the hashtable */
int teamInTable(linkTeam list, char *teamName){
    int i;
    linkTeam temp = list;
    /* Cycle through the list */
    for (i=0; temp != NULL; i++){
        /* If it has the name we are looking for, return it's position 
           on the linked list */
        if (strcmp(teamName, temp->teamName)==0)
            return i;
        temp = temp->next;
    }
    /* Returns -1 if the team is not in the hashtable */
    return -1;
}

/* Function that frees all memory allocated for a given team */
void FreeNodeTeam(linkTeam toDelete){
    free(toDelete->teamName);
    free(toDelete);
}

/* Function that destroys (frees) the Hashtable */
void DestroyHashTeam(linkTeam *HashTableTeam){
    int i;
    linkTeam list, temp, next;
    /* Cycle through every index of the hashtable */
    for (i=0; i<HASHTABLE_SIZE; i++){
        list = HashTableTeam[i];
        temp = list;
        /* If there are teams, free the memory allocated */
        while (temp != NULL){
            next = temp->next;
            FreeNodeTeam(temp);
            temp = next;
        }
    }
}

/* Function that cycles through all the teams in the database 
   and gets the maximum number of wins */
int getMaxWins(linkTeam *HashTableTeam){
    int i, max = 0;
    linkTeam list, temp;

    /* Cycle through the Hashtable */
    for (i=0; i < HASHTABLE_SIZE; i++){
        list = HashTableTeam[i];
        /* Cycle through the linkedlist at index i */
        for (temp = list; temp != NULL ; temp = temp->next){
            /* If the number of wins is bigger than the already registered
               update max */
            if (temp->teamWins > max){
                max = temp->teamWins;
            }
        }
    }
    return max;
}