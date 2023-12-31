#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "team.h"


int hashTeam(char *name)
{
  int h = 0;
  int a = 127;
  for (; (*name) != '\0'; name++)
    h = ((a * h) + (*name)) % 101;

  return h;
}

TeamNode *addTeam(TeamNode *head, char *n)
{
  TeamNode *new;
  new = malloc(sizeof(TeamNode));
  new->name = malloc(strlen(n) * (sizeof(char)));
  strcpy(new->name, n);
  new->wins = 0;
  new->exists = 1;
  if (head != 0)
  {
    new->next = head;
  }
  else
  {
    
  }

  return new;
}

TeamNode *searchTeam(TeamNode *head, char *n)
{
  TeamNode *node;
  TeamNode *ret;
  node = head;
  if (head == 0)
  {
    ret = malloc(sizeof(TeamNode));
    ret->exists = 0;
    return ret;
  }
  else
  {
    
  }

  if (strcmp(n, head->name) == 0)
  {
    return head;
  }
  else
  {
    
  }

  while (node->next != 0)
  {
    if (strcmp(n, node->name) == 0)
    {
      return node;
    }
    else
    {
      node = node->next;
    }

  }

  ret = malloc(sizeof(TeamNode));
  ret->exists = 0;
  return ret;
}

