#ifndef _STACK_
#define _STACK_

/* Struct defined for a node in the stack */
struct match{

    char *matchName;
    struct match *next;

};

typedef struct match StackNode;

/* Functions defined in stack.c */
StackNode *NewNode(char *text);

StackNode *push(StackNode **head, StackNode **tail, StackNode *new);

void printGames(StackNode **head);

void addNode(StackNode **head, StackNode **tail, char *matchName);

void addNodeBegin(StackNode **head, char *matchName);

StackNode *insertBegin(StackNode **head, StackNode *new);

void printTeams(int commandCounter, StackNode **head);

void FreeNodeStack(StackNode *toFree);

StackNode *deleteMatchStack(StackNode **head, StackNode **tail, char *matchName);

void pop(StackNode **head);

void DestroyStack(StackNode **head);

int isStackEmpty(StackNode **head);

StackNode* MergeAux(StackNode* a, StackNode* b);

void Partition(StackNode* source, StackNode** front, StackNode** back);

void MergeSort(StackNode** head);

#endif