#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "strdup.h"

/* Function that creates a new node to add to the stack */
StackNode *NewNode(char *text){
    /* Allocate memory for the struct */
    StackNode *x =(StackNode*)malloc(sizeof(struct match));
    /* Allocate memory for the name of the team/match*/
    x->matchName = mystrdup(text);
    x->next = NULL;
    return x;
}

/* Function that inserts the new node in the stack */
StackNode* push(StackNode **head, StackNode **tail, StackNode *new){
    /* If the head is NULL, the new node becomes the head and the tail */
    if (*head == NULL){
        *head = new;
        *tail = new;
        return new;
    }
    /* Otherwise inserts the new node at the end of the stack */
    else {
        /* Insert element at the end of the list */
        (*tail)->next = new;
        /* Tail becomes the last element */
        *tail = new;
        /* Return the head after adding the new node */
        return *head;
    }
}

/* Function that inserts a new team at the beggining of the list */
StackNode *insertBegin(StackNode **head, StackNode *new){
    /* If head is NULL the head becomes the new node */
    if (*head == NULL){
        return new;
    } else {
        /* new points to the head and becomes the new head */
        new->next = *head;
        *head = new;
        return *head;
    }
}

/* Function that creates and adds a new node to the stack */
void addNode(StackNode **head, StackNode **tail, char *matchName){
    /* Create the new node */
    StackNode *new = NewNode(matchName);
    /* Add it to the end of the stack */
    *head = push(head, tail, new);
}

/* Function that creates and adds a new node to the stack */
void addNodeBegin(StackNode **head, char *matchName){
    /* Create the new node */
    StackNode *new = NewNode(matchName);
    /* Add it to the end of the stack */
    *head = insertBegin(head, new);
}

/* Functions that prints the teams on the stack according 
   to the requirements on command 'g' */
void printTeams(int commandCounter, StackNode **head){
    StackNode *temp = *head;
    /* Keep printing teams while the stack isn't NULL */
    while (isStackEmpty(&temp) != 1){
        /* Print the info */
        printf("%d * %s\n", commandCounter, temp->matchName);
        temp = temp->next;
    }
}

/* Function that frees all memory allocated to a node in the stack */
void FreeNodeStack(StackNode *toFree){
    free(toFree->matchName);
    free(toFree);
}

/* Function that deletes a team from the stack when given its name */
StackNode *deleteMatchStack(StackNode **head, StackNode **tail, char *matchName){
    StackNode *temp = *head, *prev;
    
    /* If the current match has the name we are looking for and it's in the head */
    if (strcmp(temp->matchName, matchName) == 0){
        if (temp->next == NULL) {tail = NULL;}
        /* Head becomes next element */
        *head = temp->next;
        /* Free the memory allocated to the match */
        FreeNodeStack(temp);
        return *head;
    }
    /* Cycle through while the match hasn't the name we are looking for */
    while (strcmp(temp->matchName, matchName) != 0){
        prev = temp;
        temp = temp->next;
    }

    /* If the match we want to delete is the last, set tail to the previous match*/
    if (temp == *tail) {*tail = prev;}
    /* When we find the right match link the previous match and the 
       one after the wanted match */
    prev->next = temp->next;
    /* Free the memory allocated to the match */
    FreeNodeStack(temp);
    /* Return the head after all modifications */
    return *head;
}

/* Function that pops the head of the stack */
void pop(StackNode **head){
    StackNode *temp = *head;
    /* The head becomes the second node in the stack */
    *head = temp->next;
    /* Free the memory allocated to node of the stack */
    FreeNodeStack(temp);
}

/* Function that destroys (frees) all the nodes in the stack */
void DestroyStack(StackNode **head){
    while (*head != NULL){
        pop(head);
    }
}

/* Function that returns 0 if a team is already in the stack (-1 if it isn't) */
int teamInStack(StackNode **head, char* teamName){
    StackNode *temp = *head;
    /* Cycle through the stack until a team with the wanted name if found */
    while (temp != NULL){
        if (strcmp(teamName, temp->matchName) == 0) {return 0;}
    temp = temp->next;
    }
    /* If there isn't a team in the stack with the given name return -1 */
    return -1;
}

/* Function that return 1 if stack is empty */
int isStackEmpty(StackNode **head){
    return *head == NULL;
}

/* Recursive function of Merge Sort */
StackNode* MergeAux(StackNode* a, StackNode* b){ 
    StackNode* temp = NULL; 
    /* Check if any of the structs are NULL */
    if (a == NULL) 
        return b; 
    else if (b == NULL) 
        return a; 
  
    /* Compare the strings and call MergeAux recursively */
    if (strcmp(a->matchName, b->matchName) < 0) { 
        /* Pick a */
        temp = a; 
        temp->next = MergeAux(a->next, b); 
    } else { 
        /* Pick b */
        temp = b; 
        temp->next = MergeAux(a, b->next); 
    } 
    /* Return the sorted list */
    return temp; 
} 
  
/* Auxiliar function to MergeSort algorithm */
void Partition(StackNode* source, StackNode** front, StackNode** back){ 
    StackNode *fast, *slow; 
    slow = source; 
    fast = source->next; 
  
    /* fast traverses the list always one node ahead of slow */
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
    /* At this point slow is before the midpoint in the list so split it in two */
    *front = source; 
    *back = slow->next; 
    slow->next = NULL; 
}

/* Merge Sort application to linked lists */
void MergeSort(StackNode** head){ 
    StackNode* temp = *head; 
    StackNode* a; 
    StackNode* b; 
  
    /* If the head is NULL or only has one element */
    if (temp == NULL || temp->next == NULL) { return; } 
  
    /* Separate head into two sublists, a and b */
    Partition(temp, &a, &b); 
  
    /* Recursively sort the sublists */
    MergeSort(&a); 
    MergeSort(&b); 
  
    /* head becomes the final sorted list */
    *head = MergeAux(a, b); 
}