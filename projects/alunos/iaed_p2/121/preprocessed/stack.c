#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "strdup.h"


StackNode *NewNode(char *text)
{
  StackNode *x = (StackNode *) malloc(sizeof(struct match));
  x->matchName = mystrdup(text);
  x->next = 0;
  return x;
}

StackNode *push(StackNode **head, StackNode **tail, StackNode *new)
{
  if ((*head) == 0)
  {
    *head = new;
    *tail = new;
    return new;
  }
  else
  {
    (*tail)->next = new;
    *tail = new;
    return *head;
  }

}

StackNode *insertBegin(StackNode **head, StackNode *new)
{
  if ((*head) == 0)
  {
    return new;
  }
  else
  {
    new->next = *head;
    *head = new;
    return *head;
  }

}

void addNode(StackNode **head, StackNode **tail, char *matchName)
{
  StackNode *new = NewNode(matchName);
  *head = push(head, tail, new);
}

void addNodeBegin(StackNode **head, char *matchName)
{
  StackNode *new = NewNode(matchName);
  *head = insertBegin(head, new);
}

void printTeams(int commandCounter, StackNode **head)
{
  StackNode *temp = *head;
  while (isStackEmpty(&temp) != 1)
  {
    printf("%d * %s\n", commandCounter, temp->matchName);
    temp = temp->next;
  }

}

void FreeNodeStack(StackNode *toFree)
{
  free(toFree->matchName);
  free(toFree);
}

StackNode *deleteMatchStack(StackNode **head, StackNode **tail, char *matchName)
{
  StackNode *temp = *head;
  StackNode *prev;
  if (strcmp(temp->matchName, matchName) == 0)
  {
    if (temp->next == 0)
    {
      tail = 0;
    }
    else
    {
      
    }

    *head = temp->next;
    FreeNodeStack(temp);
    return *head;
  }
  else
  {
    
  }

  while (strcmp(temp->matchName, matchName) != 0)
  {
    prev = temp;
    temp = temp->next;
  }

  if (temp == (*tail))
  {
    *tail = prev;
  }
  else
  {
    
  }

  prev->next = temp->next;
  FreeNodeStack(temp);
  return *head;
}

void pop(StackNode **head)
{
  StackNode *temp = *head;
  *head = temp->next;
  FreeNodeStack(temp);
}

void DestroyStack(StackNode **head)
{
  while ((*head) != 0)
  {
    pop(head);
  }

}

int teamInStack(StackNode **head, char *teamName)
{
  StackNode *temp = *head;
  while (temp != 0)
  {
    if (strcmp(teamName, temp->matchName) == 0)
    {
      return 0;
    }
    else
    {
      
    }

    temp = temp->next;
  }

  return -1;
}

int isStackEmpty(StackNode **head)
{
  return (*head) == 0;
}

StackNode *MergeAux(StackNode *a, StackNode *b)
{
  StackNode *temp = 0;
  if (a == 0)
  {
    return b;
  }
  else
  {
    if (b == 0)
    {
      return a;
    }
    else
    {
      
    }

  }

  if (strcmp(a->matchName, b->matchName) < 0)
  {
    temp = a;
    temp->next = MergeAux(a->next, b);
  }
  else
  {
    temp = b;
    temp->next = MergeAux(a, b->next);
  }

  return temp;
}

void Partition(StackNode *source, StackNode **front, StackNode **back)
{
  StackNode *fast;
  StackNode *slow;
  slow = source;
  fast = source->next;
  while (fast != 0)
  {
    fast = fast->next;
    if (fast != 0)
    {
      slow = slow->next;
      fast = fast->next;
    }
    else
    {
      
    }

  }

  *front = source;
  *back = slow->next;
  slow->next = 0;
}

void MergeSort(StackNode **head)
{
  StackNode *temp = *head;
  StackNode *a;
  StackNode *b;
  if ((temp == 0) || (temp->next == 0))
  {
    return;
  }
  else
  {
    
  }

  Partition(temp, &a, &b);
  MergeSort(&a);
  MergeSort(&b);
  *head = MergeAux(a, b);
}

