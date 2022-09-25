/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "TEAM.h"


void NewTeam(int line)
{
  int i;
  link l;
  char *name = malloc((sizeof(char)) * 1024);
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  i = hash_team(name);
  l = searchHashTeam(name, t_heads[i]);
  if (!l)
  {
    t_heads[i] = insertHashTeam(name, t_heads[i]);
    freeTeamList(teams_list);
    TeamListInit();
  }
  else
  {
    printf("%d Equipa existente.\n", line);
  }

  free(name);
}

void SearchTeam(int line)
{
  char *name = malloc((sizeof(char)) * 1024);
  link l;
  int i;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  getchar();
  i = hash_team(name);
  l = searchHashTeam(name, t_heads[i]);
  if (l != 0)
  {
    printf("%d %s %d\n", line, name, l->team->wins);
  }
  else
  {
    printf("%d Equipa inexistente.\n", line);
  }

  free(name);
}

void MaxWins(int line)
{
  int i;
  int max = -1;
  link l;
  link index;
  TeamsList gl;
  getchar();
  if (teams_list == 0)
  {
    for (i = 0; i < 256; i++)
    {
      for (index = t_heads[i]; index != 0; index = index->next)
      {
        if (index->team->wins > max)
        {
          if (teams_list != 0)
          {
            freeTeamList(teams_list);
            TeamListInit();
          }
          else
          {
            
          }

          max = index->team->wins;
          insertTeamList(index->team);
        }
        else
        {
          if (index->team->wins == max)
          {
            insertTeamList(index->team);
          }
          else
          {
            
          }

        }

      }

    }

  }
  else
  {
    
  }

  if (teams_list != 0)
  {
    i = hash_team(teams_list->team->name);
    l = searchHashTeam(teams_list->team->name, t_heads[i]);
    printf("%d Melhores %d\n", line, l->team->wins);
    for (gl = teams_list; gl != 0; gl = gl->next)
    {
      printf("%d * %s\n", line, gl->team->name);
    }

  }
  else
  {
    
  }

}

void increaseWins(char *name)
{
  int i = hash_team(name);
  link l = searchHashTeam(name, t_heads[i]);
  l->team->wins++;
}

void decreaseWins(char *name)
{
  int i = hash_team(name);
  link l = searchHashTeam(name, t_heads[i]);
  l->team->wins--;
}

link newTeamLink(char *name)
{
  size_t size;
  link l = malloc(sizeof(struct node));
  l->team = malloc(sizeof(struct team));
  size = strlen(name) + 1;
  l->team->name = malloc((sizeof(char)) * size);
  strncpy(l->team->name, name, size);
  l->team->wins = 0;
  l->next = 0;
  return l;
}

int hash_team(char *name)
{
  return name[0] % 256;
}

void TeamInit()
{
  int i;
  teams_list = 0;
  teams_list_tail = 0;
  t_heads = (link *) malloc((sizeof(link)) * 256);
  for (i = 0; i < 256; i++)
    t_heads[i] = 0;

}

link insertHashTeam(char *name, link head)
{
  link aux;
  link prev;
  if (head == 0)
  {
    head = newTeamLink(name);
  }
  else
  {
    for (aux = head, prev = 0; aux != 0; prev = aux, aux = aux->next)
    {
      if (strcmp(aux->team->name, name) < 0)
      {
        if (aux->next == 0)
        {
          aux->next = newTeamLink(name);
          break;
        }
        else
        {
          
        }

      }
      else
      {
        if (aux == head)
        {
          head = newTeamLink(name);
          head->next = aux;
          break;
        }
        else
        {
          prev->next = newTeamLink(name);
          prev->next->next = aux;
          break;
        }

      }

    }

  }

  return head;
}

link searchHashTeam(char *name, link head)
{
  link aux;
  for (aux = head; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->team->name, name) == 0)
    {
      return aux;
    }
    else
    {
      
    }

  }

  return 0;
}

void free_list(link head)
{
  if (head != 0)
  {
    free(head->team->name);
    free(head->team);
    free_list(head->next);
    free(head);
  }
  else
  {
    
  }

}

void freeTeamHash()
{
  int i;
  for (i = 0; i < 256; i++)
  {
    free_list(t_heads[i]);
  }

}

void freeTeamList(TeamsList t)
{
  if (t != 0)
  {
    freeTeamList(t->next);
    free(t);
  }
  else
  {
    
  }

}

void TeamListInit()
{
  teams_list = 0;
  teams_list_tail = 0;
}

void insertTeamList(Team team)
{
  if (teams_list == 0)
  {
    teams_list = (teams_list_tail = newTeamIndex(team));
  }
  else
  {
    teams_list_tail->next = newTeamIndex(team);
    teams_list_tail = teams_list_tail->next;
  }

}

TeamsList newTeamIndex(Team team)
{
  TeamsList node = malloc(sizeof(struct team_name));
  node->team = team;
  node->next = 0;
  return node;
}

