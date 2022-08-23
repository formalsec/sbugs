/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "teams.h"


hash_table_teams *create_ht_team(int size)
{
  int i;
  hash_table_teams *new;
  if (size < 1)
  {
    return 0;
  }
  else
  {
    
  }

  if ((new = malloc(sizeof(hash_table_teams))) == 0)
  {
    return 0;
  }
  else
  {
    
  }

  if ((new->table = malloc((sizeof(list_teams *)) * size)) == 0)
  {
    return 0;
  }
  else
  {
    
  }

  for (i = 0; i < size; i++)
    new->table[i] = 0;

  new->size = size;
  return new;
}

int hash_teams(hash_table_teams *team_ht, char *v)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (team_ht->size - 1))
  {
    h = ((a * h) + (*v)) % team_ht->size;
  }

  return h;
}

void insertBegin_teams(hash_table_teams *team_ht, char *v)
{
  list_teams *new;
  int h = hash_teams(team_ht, v);
  new = malloc(sizeof(list_teams));
  new->name = malloc((sizeof(char)) * (strlen(v) + 1));
  new->victories = 0;
  strcpy(new->name, v);
  new->next = team_ht->table[h];
  team_ht->table[h] = new;
}

list_teams *search_team_aux(hash_table_teams *team_ht, char *v)
{
  list_teams *list;
  int h = hash_teams(team_ht, v);
  for (list = team_ht->table[h]; list != 0; list = list->next)
  {
    if (strcmp(v, list->name) == 0)
    {
      return list;
    }
    else
    {
      
    }

  }

  return 0;
}

int compare_names(list_names *y, list_names *z)
{
  return strcmp(y->team_name, z->team_name);
}

list_names *insert_name_list(list_names *head_lst_names, char *name)
{
  list_names *y = malloc(sizeof(list_names));
  y->team_name = name;
  y->next = 0;
  if ((head_lst_names == 0) || (compare_names(y, head_lst_names) < 0))
  {
    {
      y->next = head_lst_names;
      return y;
    }
  }
  else
  {
    {
      list_names *z = head_lst_names;
      while ((z->next != 0) && (compare_names(y, z->next) >= 0))
      {
        z = z->next;
      }

      y->next = z->next;
      z->next = y;
      return head_lst_names;
    }
  }

}

void print_list_names(list_names *head_lst_names, int NL)
{
  list_names *t;
  list_names *lst_names_aux = head_lst_names;
  for (t = head_lst_names; t != 0; t = t->next)
    printf("%d * %s\n", NL, t->team_name);

  while (lst_names_aux != 0)
  {
    lst_names_aux = head_lst_names->next;
    free(head_lst_names);
    head_lst_names = lst_names_aux;
  }

}

