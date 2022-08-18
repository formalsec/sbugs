#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "teams.h"
#define M 1051 /* Maximum size for the hashtable */

#ifndef hashteams_h
#define hashteams_h


typedef struct node{
    ptrTeam Team;               /* For a quick lookup/ insertion/ removal of elements, it was chosen to implement  */    
    struct node *next;          /* a hash table with external chaining */
}*link;

typedef link *heads;

typedef struct _maxes{          /* This struct was defined in order to improve efficiency on the last function, */
    int max;                    /*preventing another iteration throughout the whole hashtable three times to */
    int maxOcc;                 /*determine the necessary parameters*/
}maxes;

/*--------------------listInit-------------------------
INPUT: N/A
OUTPUT: list (struct link)
Initializes a list */
link listInit(); 

/*--------------------listAddNode-------------------------
INPUT: team (struct ptrTeam), next (pointer to the sucessor, where 'team' will be added)
OUTPUT: list with the new element (struct link)
Returns an updated list after inserting 'team' into it. */
link listAddNode(ptrTeam team, link next); 

/*--------------------listDeleteNode-------------------------
INPUT: node (struct link)
OUTPUT: list without the given element (struct link)
Returns an updated list after removing 'node' from it. */
void listDeleteNode(link node); 

/*--------------------getItem-------------------------
INPUT: node (struct link)
OUTPUT: data retrieved from node (struct ptrTeam)
Retrieves and returns a data from a given node */
ptrTeam getItem(link node); 

/*--------------------listEmpty-------------------------
INPUT: head of the list (struct link)
OUTPUT: TRUE/FALSE
Verifies whether a list is empty or not. */
int listEmpty(link head);

/*--------------------searchList-------------------------
INPUT: node (struct link), name (string)
OUTPUT: the link with name 'name' (struct link)
Searches and retrieves a link with a given name*/
link searchList(link head, char* name);

/*--------------------insertListEnd-------------------------
INPUT: head of a list (struct link), team (struct ptrTeam)
OUTPUT: list with the given link inserted into it
Inserts a link into a given list*/
link insertListEnd(link head, ptrTeam team);

/*--------------------destroyList-------------------------
INPUT: head of a list (struct link),
OUTPUT: N/A
Destroys every element from a given list*/
link destroyList(link head);

/*--------------------hash-------------------------
Hash function, calculates the index so as to minimize
collisions */
int hash(char* name);

/*--------------------hashInit-------------------------
INPUT: N/A
OUTPUT: hash table (struct heads)
Initializes a hash table */
heads hashInit();

/*--------------------hashEmpty-------------------------
INPUT: hash table (struct heads)
OUTPUT: TRUE/FALSE
Verifies whether a hash table is empty or not. */
int hashEmpty(heads hash);

/*--------------------hashInsert-------------------------
INPUT: hash table (struct heads), team (struct ptrTeam), NL
OUTPUT: hashtable with the new element (struct link)
Returns an updated hash table after inserting 'team' into it. */
void hashInsert(int NL, heads hashT, ptrTeam team);

/*--------------------hashSearch-------------------------
INPUT: hash table (struct heads), name (string)
OUTPUT: element of a hash table with name 'name' (struct link)
Searches and retrieves a link with a given name from a hash table*/
link hashSearch(heads heads, char* name);

/*--------------------hashDestroy-------------------------
INPUT: hash table (struct *link),
OUTPUT: N/A
Destroys every element from a given hash table*/
void hashDestroy(link* heads);

/*--------------------getHashMax-------------------------
INPUT: hash table (struct heads),
OUTPUT: maximum number of wins and its number of occurences (struct maxes)
Gets the max value of wins and its number of occurences in a hash table*/
maxes getHashMax(heads head);

/*--------------------getListMax-------------------------
INPUT: linked list (struct heads), maxes
OUTPUT: maximum number of wins and its number of occurences (struct maxes)
Auxiliary function that performs the same task, but in a linked list*/
maxes getListMax(link head, maxes maxes);

/*--------------------getHashStrings-------------------------
INPUT: hash table (struct heads), max, pointer of strings
OUTPUT: strings (char**)
returns the strings of the teams that had a maximum number of victories*/
char** getHashStrings(heads head, int max, char **strings);

/*--------------------getListStrings-------------------------
INPUT: linked list (struct heads), maxes
OUTPUT: strings (char*)
Auxiliary function that performs the same task, but in a linked list*/
char* getListStrings(link head, int max);


#endif

