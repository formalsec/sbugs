#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include "hashTeam.h"


teamlink push_team(teamlink head, TEAM i)
{
  teamlink aux = NEWNode_team(i, head);
  return aux;
}

teamlink remove_TEAM(teamlink head, teamKey k)
{
  teamlink current;
  teamlink prev;
  for (current = head, prev = 0; current; prev = current, current = current->next)
  {
    if (strcmp(k, current->TEAM->Teamname) == 0)
    {
      if (current == head)
      {
        head = current->next;
      }
      else
      {
        prev->next = current->next;
      }

      DELETENode_team(current);
      return head;
    }
    else
    {
      
    }

  }

  return head;
}

TEAM search_list_team(teamlink head, teamKey key)
{
  teamlink current;
  for (current = head; current; current = current->next)
  {
    if (strcmp(current->TEAM->Teamname, key) == 0)
    {
      return current->TEAM;
    }
    else
    {
      
    }

  }

  return 0;
}

void destroy_list_team(teamlink head)
{
  teamlink current;
  teamlink aux;
  if (!head)
  {
    return;
  }
  else
  {
    
  }

  for (current = head, aux = head->next; current; aux = current->next, DELETENode_team(current), current = aux)
  {
  }

}

teamlink *HASHinit_team()
{
  int i;
  teamlink *heads = (teamlink *) malloc(2371 * (sizeof(teamlink)));
  for (i = 0; i < 2371; i++)
  {
    heads[i] = 0;
  }

  return heads;
}

int hash_team(char *v)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (2371 - 1))
    h = ((a * h) + (*v)) % 2371;

  return h;
}

teamlink NEWNode_team(TEAM TEAM, teamlink next)
{
  teamlink x = malloc(sizeof(struct node));
  x->TEAM = TEAM;
  x->next = next;
  return x;
}

void DELETENode_team(teamlink node)
{
  deleteTeam(node->TEAM);
  free(node);
}

void insert_team(teamlink *heads, TEAM TEAM)
{
  int i = hash_team(TEAM->Teamname);
  heads[i] = push_team(heads[i], TEAM);
}

TEAM search_team(teamlink *heads, teamKey k)
{
  int i = hash_team(k);
  return search_list_team(heads[i], k);
}

void destroy_hash_team(teamlink *heads)
{
  int i;
  for (i = 0; i < 2371; i++)
  {
    destroy_list_team(heads[i]);
  }

  free(heads);
}
