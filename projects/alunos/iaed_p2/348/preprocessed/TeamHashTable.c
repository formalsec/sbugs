#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TeamHashTable.h"
#include "Const.h"


Hash_Table_Team *mk_Team_Hash_Table()
{
  int i;
  Hash_Table_Team *pHT = malloc(sizeof(Hash_Table_Team));
  pHT->capacity = 1021;
  pHT->table = malloc((sizeof(Hash_Node_Team)) * pHT->capacity);
  for (i = 0; i < pHT->capacity; i++)
  {
    pHT->table[i] = 0;
  }

  return pHT;
}

int hash_key(char *name, int capacity)
{
  int h = 0;
  int a = 127;
  for (; (*name) != '\0'; name++)
    h = ((a * h) + (*name)) % capacity;

  return h;
}

void addToTeamHashList(char *teamName, Hash_Table_Team *t, int index)
{
  Hash_Node_Team *node = malloc(sizeof(Hash_Node_Team));
  Team *team = malloc(sizeof(Team));
  team->name = malloc((sizeof(char)) * (strlen(teamName) + 1));
  strcpy(team->name, teamName);
  team->gamesWon = 0;
  node->team = team;
  node->next = t->table[index];
  t->table[index] = node;
}

void free_node_team(Hash_Node_Team *pHN)
{
  free(pHN->team->name);
  free(pHN->team);
}

void freeTeamHash(Hash_Table_Team *t)
{
  int i;
  Hash_Node_Team *temp;
  for (i = 0; i < t->capacity; i++)
  {
    while (t->table[i])
    {
      temp = t->table[i]->next;
      free_node_team(t->table[i]);
      free(t->table[i]);
      t->table[i] = temp;
    }

  }

  free(t->table);
  free(t);
}

