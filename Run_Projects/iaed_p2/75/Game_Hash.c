#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Game_Hash.h"
#include "Game.h"

/* Hash function for strings */
int hash_game(char* str, int M){
    int i = 0, a = 19163, b = 27183;
    for (; *str != '\0'; str++, a = a*b % (M-1)){
        i = (a*i + *str) % M;
    }
    return i;
}


/* Function intializes Hash Table of size size for Games*/
link_game* initGame_Hash(int size){
    link_game* p_hashgames= (link_game*)malloc(sizeof(link_game)*size);  /* creates vector of pointers to link_game of size size*/
    int i = 0;
    while (i < size){
        p_hashgames[i] = NULL;   /* Initialize every position of vector at NULL */
        i++;
    }
    return p_hashgames;         /* Head of Hash Table */
}


/* Function puts Game pointed by g in Hash Table pointed by h */
void insertGame_Hash(int size, link_game* h, Game* g){
    int i = hash_game(g -> pname, size);

    link_game ptaux = (link_game)malloc(sizeof(struct node_game)); /* Allocate size for node_game */
    ptaux -> pgame = g;

    /* Insert new node at beginning of position i of Hash Table */
    ptaux -> next = h[i];  
    h[i] = ptaux;             
}


/* Function removes Game pointed by g from Hash Table pointed by h */
void deleteGame_Hash(int size, link_game* h, char* g_name){
    int i = hash_game(g_name, size);
    link_game paux, previous = NULL;

    /* Run through list h[i] in search of game g_name */
    for(paux = h[i]; paux != NULL ; previous = paux, paux = paux ->next){ 
        if (strcmp(paux -> pgame -> pname, g_name) == 0){
            if(paux == h[i]){
                h[i] = paux -> next;              /* If first element on list */
            }
            else{
                previous -> next = paux -> next;  /* If not first element on list */
            }
            delGame(paux->pgame);                 /* Delete Game*/
            free(paux);
            break;
        }
    }
}


/* Function searches for game of name name in Hash Table, returns pointer to game */
Game* searchGame_Hash(int size, link_game* h, char* name){
    int i = hash_game(name, size);                          /* Get index of Hash Table in which to search team */
    link_game p_aux;

    for(p_aux = h[i]; p_aux != NULL; p_aux = p_aux -> next){
        if (strcmp(p_aux -> pgame -> pname, name) == 0) return p_aux -> pgame; /* Return pointer to game */
        ;
    }
    return NULL;  /* If not found return NULL */
}


/* Function destroys Hash_Table of games pointed by head */
void destroyGame_Hash(int size, link_game* head){
    int i;
    link_game p_aux, p_aux_delete;
    
    for(i=0; i < size; i++){           /* Run through Hash_Table vector */
        p_aux = head[i];
        while(p_aux != NULL){          /* Run through list in position i of Hash Table */
            delGame(p_aux -> pgame);   /* Delete Game */
           
            p_aux_delete = p_aux;      
            p_aux = p_aux -> next;     /* Point to next node */
            free(p_aux_delete);        /* Free current */               
        }
    }
    free(head);             /* Free vector of pointers */
}


/* Initializes auxiliary double linked list of pointers to games related to Game_Hash*/
lnk_dblist initGHash_auxList(){
    lnk_dblist head=NULL;
    return head;
}


/* Creates and inserts a new node at the end of the list*/
lnk_dblist insrtGHash_auxList(lnk_dblist head, Game* game){
    lnk_dblist ptr_aux = (lnk_dblist)malloc(sizeof(struct db_listnode));     /* Allocate space for new node */
    lnk_dblist ptr_endlist;

    ptr_aux -> pgame = game;
    ptr_aux -> next = NULL;
    
    if (head == NULL){           /* If list empty head is new node */
        head = ptr_aux;
        head -> previous = head; /* Previous pointer points to node itself */
        return head;
    }
    else {   
        
        ptr_endlist = head -> previous;     /* grab last element (head previous) with auxiliary pointer */

        ptr_endlist -> next = ptr_aux;      /* former last element now points to another node (ptr_aux) */
        ptr_aux -> previous = ptr_endlist;  /* new last element to point to previous */

        head -> previous = ptr_aux;         /* head previous points to new last element */
        return head;
    }
}


/* Removes node that contains pointer game */
lnk_dblist removGHash_auxList(lnk_dblist head, Game* game){
    lnk_dblist ptr_aux, ptr_aux2;

    for(ptr_aux = head; ptr_aux != NULL; ptr_aux = ptr_aux -> next){
        if (ptr_aux -> pgame == game){     

            if(ptr_aux == head){                 /* If node is first node of list*/
                if (head -> next == NULL){       /* If list is of size 1 free single node and return NULL */
                    free(ptr_aux);
                    return NULL;
                }
                else{                                /* List is of size > 1 */
                    ptr_aux2 = head -> next;         /* Grab next node */
                    ptr_aux2 -> previous = head -> previous;   /* Grab node previous to head (last) */
                    free(head);
                    return ptr_aux2;                /* Return new head */
                }
            }

            else{                               /* Case in which node is not first node */

                ptr_aux -> previous -> next = ptr_aux -> next;                      /* Link previous next  to next node */
                if (ptr_aux -> next == NULL) head->previous = ptr_aux->previous;    /* If node is last on list, update head->previous to new last node */
                else ptr_aux -> next -> previous = ptr_aux -> previous;            /* If not last on list, link next previous to previous node */
                free(ptr_aux);
                return head;
            }
        }
    }
    return head;
}


/* Destroys auxiliary double linked list pointed by head */
void destroyAux_List(lnk_dblist head){
    lnk_dblist p_node = head, p_previous;
    while (p_node != NULL){
        p_previous = p_node;       /* Grab current node with auxiliary pointer */
        p_node = p_node -> next;   /* Point to next node */
        free(p_previous);
    }
}