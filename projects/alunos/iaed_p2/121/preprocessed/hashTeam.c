#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "hashTeam.h"
#include "strdup.h"


void NewNodeTeam(linkTeam *head, char *teamName)
{
  linkTeam new_node = (linkTeam) malloc(sizeof(struct nodeTeam));
  new_node->teamName = mystrdup(teamName);
  new_node->teamWins = 0;
  new_node->next = 0;
  if ((*head) == 0)
  {
    *head = new_node;
  }
  else
  {
    new_node->next = *head;
    *head = new_node;
  }

}

linkTeam *CreateTableTeams()
{
  int i;
  linkTeam *hashtable = calloc(1087, sizeof(struct nodeTeam));
  for (i = 0; i < 1087; i++)
  {
    hashtable[i] = 0;
  }

  return hashtable;
}

linkTeam getTeam(linkTeam list, char *teamName)
{
  linkTeam temp;
  for (temp = list; temp != 0; temp = temp->next)
  {
    if (strcmp(teamName, temp->teamName) == 0)
    {
      return temp;
    }
    else
    {
      
    }

  }

  return 0;
}

int teamInTable(linkTeam list, char *teamName)
{
  int i;
  linkTeam temp = list;
  for (i = 0; temp != 0; i++)
  {
    if (strcmp(teamName, temp->teamName) == 0)
    {
      return i;
    }
    else
    {
      
    }

    temp = temp->next;
  }

  return -1;
}

void FreeNodeTeam(linkTeam toDelete)
{
  free(toDelete->teamName);
  free(toDelete);
}

void DestroyHashTeam(linkTeam *HashTableTeam)
{
  int i;
  linkTeam list;
  linkTeam temp;
  linkTeam next;
  for (i = 0; i < 1087; i++)
  {
    list = HashTableTeam[i];
    temp = list;
    while (temp != 0)
    {
      next = temp->next;
      FreeNodeTeam(temp);
      temp = next;
    }

  }

}

int getMaxWins(linkTeam *HashTableTeam)
{
  int i;
  int max = 0;
  linkTeam list;
  linkTeam temp;
  for (i = 0; i < 1087; i++)
  {
    list = HashTableTeam[i];
    for (temp = list; temp != 0; temp = temp->next)
    {
      if (temp->teamWins > max)
      {
        max = temp->teamWins;
      }
      else
      {
        
      }

    }

  }

  return max;
}

