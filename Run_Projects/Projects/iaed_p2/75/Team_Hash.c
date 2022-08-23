#include <stdlib.h>
#include <string.h>
#include "Team_Hash.h"
#include "Team.h"

/* Hash function for strings */
int hash_team(char* str, int M){
    int i = 0, a = 31415, b = 27183;
    for (; *str != '\0' ; str++, a = a*b % (M-1)){
        i = (a*i + *str) % M;
    }
    return i;
}


/* Function initializes Hash Table of size size for teams, returns pointer to it */
link_team* initTeam_Hash(int size){
    int i;
    link_team* head = (link_team*)malloc(sizeof(link_team)*size);  /* head is pointer to HashTable of teams */
    for(i=0; i < size; i++){
        head[i] = NULL;            /* intialize every position at NULL */
    }
    return head;
}


/* Function inserts team pointed by t in Hash Table pointed by h*/
void insertTeam_Hash(int size, link_team* h, Team* t){
    int i = hash_team(t->name, size);

    link_team ptr_node = (link_team)malloc(sizeof(struct node_team));  /* Creation of node to insert in HT*/
    
    ptr_node -> pteam = t;                 /* Node -> pteam points to team */

    /* Insertion of node at the beggining of list pointed by h[i] */
    ptr_node -> next = h[i];
    h[i] = ptr_node;
}


/* Function Deletes team pointed by t from Hash Table pointed by h*/
void deleteTeam_Hash(int size, link_team* h, char* name_delete){
    int i = hash_team(name_delete, size);

    link_team p_aux, p_previous_aux = NULL;
    for(p_aux = h[i]; p_aux != NULL; p_previous_aux = p_aux, p_aux = p_aux -> next){      /* Search for team */
        if(strcmp(p_aux -> pteam -> name, name_delete) == 0){
            if (p_aux == h[i]){                                              /* Case 1 - node is first of list h[i]*/
                h[i] = p_aux -> next;                                        /* Point head of list h[i] to next node */
            }
            else{                                                           /* Case 2 - node is not firs of list h[i] */
                p_previous_aux->next = p_aux->next;                         /* Point previous node to next node */ 
            }
            
            deleteTeam(p_aux -> pteam);       /* Delete Team */
            free(p_aux);                      /* Free node of list */
            break;                            /* Stop cycle because team was found and removed */
        }
    }
}


/* Function searches for team of name name in Hash Table pointed by h */
Team* searchTeam_Hash(int size, link_team* h, char* name){
    int i = hash_team(name, size);

    link_team aux_pointer = h[i];
    for(; aux_pointer != NULL; aux_pointer = aux_pointer->next){ /* Stop only if finds team or hits the end */
        if (strcmp(aux_pointer -> pteam -> name, name) == 0){
            return aux_pointer -> pteam;                         /* Return pointer to team */
        }
    }
    return NULL;  /* Return NULL if team not found */
}


/* Function destroys Hash_Table of teams pointed by head */
void destroyTeam_Hash(int size, link_team* head){
    int i;
    link_team p_aux, p_aux_2;
    for(i=0; i < size; i++){             /* Run through Hash_Table vector */
        p_aux = head[i];
        while(p_aux != NULL){            /* Run through list pointed by h[i] */
            deleteTeam(p_aux->pteam);   
            p_aux_2 = p_aux;             /* Grab node with auxiliary pointer */
            p_aux = p_aux ->next;        /* Advance main auxiliary pointer to next node */
            free(p_aux_2);               /* Free node */
        }
    }
    free(head); /* Free vector of pointers to lists */ 
}