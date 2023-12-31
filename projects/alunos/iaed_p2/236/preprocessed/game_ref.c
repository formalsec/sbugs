#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "structures.h"


void printSingleGame(game *single_game, int NL);
game_reference *newReference(game *data)
{
  game_reference *new_game_reference = malloc(sizeof(game_reference));
  new_game_reference->data = data;
  new_game_reference->next = 0;
  new_game_reference->prev = 0;
  return new_game_reference;
}

game_reference *findReference(game_reference *head, char *name)
{
  game_reference *tmp = head;
  while (tmp != 0)
  {
    if (strcmp(tmp->data->name, name) == 0)
    {
      return tmp;
    }
    else
    {
      
    }

    tmp = tmp->next;
  }

  free(tmp);
  return 0;
}

void pushReference(game_reference **head, game_reference *new_game_reference)
{
  new_game_reference->next = *head;
  new_game_reference->prev = 0;
  if ((*head) != 0)
  {
    (*head)->prev = new_game_reference;
  }
  else
  {
    
  }

  *head = new_game_reference;
}

void deleteReference(game_reference **head, game_reference *node_to_delete)
{
  if ((*head) == node_to_delete)
  {
    *head = node_to_delete->next;
    if ((*head) != 0)
    {
      (*head)->prev = 0;
    }
    else
    {
      
    }

  }
  else
  {
    node_to_delete->prev->next = node_to_delete->next;
    if (node_to_delete->next != 0)
    {
      node_to_delete->next->prev = node_to_delete->prev;
    }
    else
    {
      
    }

  }

  node_to_delete->next = 0;
  node_to_delete->prev = 0;
  free(node_to_delete);
}

void printReference(game_reference *head, int NL)
{
  game_reference *tmp;
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  tmp = head;
  while (tmp->next != 0)
  {
    tmp = tmp->next;
  }

  while (tmp != 0)
  {
    printSingleGame(tmp->data, NL);
    tmp = tmp->prev;
  }

  free(tmp);
}

void freeReference(game_reference *head)
{
  game_reference *tmp;
  game_reference *current;
  if (head == 0)
  {
    return;
  }
  else
  {
    
  }

  current = head;
  while (current != 0)
  {
    tmp = current;
    current = current->next;
    free(tmp);
  }

}

