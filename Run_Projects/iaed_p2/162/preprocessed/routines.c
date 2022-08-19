/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"


void AddWin(game *game_v, int score1, int score2)
{
  if (score1 > score2)
  {
    {
      ++game_v->team1->wins;
    }
  }
  else
  {
    
  }

  if (score2 > score1)
  {
    {
      ++game_v->team2->wins;
    }
  }
  else
  {
    
  }

}

void __a__(teamstable *table_t, gametable *table_g, int NL)
{
  char name[1024];
  char team1_c[1024];
  char team2_c[1024];
  int score1;
  int score2;
  game *game_v;
  team *team1;
  team *team2;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  for (int team1_c_index = 0; team1_c_index < 10; team1_c_index++)
  {
    team1_c[team1_c_index] = new_sym_var(sizeof(char) * 8);
  }

  team1_c[10 - 1] = '\0';
  for (int team2_c_index = 0; team2_c_index < 10; team2_c_index++)
  {
    team2_c[team2_c_index] = new_sym_var(sizeof(char) * 8);
  }

  team2_c[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (SearchGame(name, table_g) != 0)
  {
    {
      printf("%d Jogo existente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  team1 = SearchTeam(team1_c, table_t);
  team2 = SearchTeam(team2_c, table_t);
  if ((team1 == 0) || (team2 == 0))
  {
    {
      printf("%d Equipa inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  game_v = (game *) malloc(sizeof(game));
  game_v->name = (char *) malloc((sizeof(char)) * (strlen(name) + 1));
  strcpy(game_v->name, name);
  game_v->team1 = team1;
  game_v->team2 = team2;
  game_v->score1 = score1;
  game_v->score2 = score2;
  game_v->id = table_g->last_idg;
  InsertGame(game_v, table_g);
  AddWin(game_v, score1, score2);
  if (table_g->n_el >= (table_g->size / 2))
  {
    {
      *table_g = *ExpandGameTable(table_g);
    }
  }
  else
  {
    
  }

}

void __A__(teamstable *table_t, int NL)
{
  team *team_v;
  char name[1024];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  if (SearchTeam(name, table_t) != 0)
  {
    {
      printf("%d Equipa existente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  team_v = (team *) malloc(sizeof(team));
  team_v->name = (char *) malloc((sizeof(char)) * (strlen(name) + 1));
  strcpy(team_v->name, name);
  team_v->wins = 0;
  InsertTeam(team_v, table_t);
  if (table_t->n_el >= (table_t->size / 2))
  {
    {
      *table_t = *ExpandTeamsTable(table_t);
    }
  }
  else
  {
    
  }

}

int partition(game **game_array, int left, int right)
{
  int i = left - 1;
  int j = right;
  game *aux;
  game *pivot = game_array[right];
  while (i < j)
  {
    while (game_array[++i]->id < pivot->id)
      ;

    while (game_array[--j]->id > pivot->id)
    {
      if (j == left)
      {
        {
          break;
        }
      }
      else
      {
        
      }

    }

    if (i < j)
    {
      {
        aux = game_array[i];
        game_array[i] = game_array[j];
        game_array[j] = aux;
      }
    }
    else
    {
      
    }

  }

  aux = game_array[i];
  game_array[i] = game_array[right];
  game_array[right] = aux;
  return i;
}

void quicksort(game **game_array, int left, int right)
{
  int i;
  if (right <= left)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  i = partition(game_array, left, right);
  quicksort(game_array, left, i - 1);
  quicksort(game_array, i + 1, right);
}

void __l__(gametable *table_g, int NL)
{
  game **game_array;
  int i;
  int j = 0;
  game_array = (game **) malloc(((sizeof(game *)) * table_g->size) / 2);
  for (i = 0; i < table_g->size; i++)
  {
    if (table_g->table[i] != 0)
    {
      {
        game_array[j] = table_g->table[i];
        ++j;
      }
    }
    else
    {
      
    }

  }

  quicksort(game_array, 0, j - 1);
  for (i = 0; i < j; i++)
  {
    printf("%d %s %s %s %d %d\n", NL, game_array[i]->name, game_array[i]->team1->name, game_array[i]->team2->name, game_array[i]->score1, game_array[i]->score2);
  }

  free(game_array);
}

void __p__(gametable *table_g, int NL)
{
  game *game_v;
  char name[1024];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  game_v = SearchGame(name, table_g);
  if (game_v == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }
  else
  {
    {
      printf("%d %s %s %s %d %d\n", NL, game_v->name, game_v->team1->name, game_v->team2->name, game_v->score1, game_v->score2);
    }
  }

}

void __P__(teamstable *table_t, int NL)
{
  team *team_v;
  char name[1024];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  team_v = SearchTeam(name, table_t);
  if (team_v == 0)
  {
    {
      printf("%d Equipa inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  printf("%d %s %d\n", NL, team_v->name, team_v->wins);
}

void __r__(gametable *table_g, int NL)
{
  game *game_v;
  char name[1024];
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  game_v = SearchGame(name, table_g);
  if (game_v == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  if (game_v->score1 > game_v->score2)
  {
    {
      --game_v->team1->wins;
    }
  }
  else
  {
    
  }

  if (game_v->score2 > game_v->score1)
  {
    {
      --game_v->team2->wins;
    }
  }
  else
  {
    
  }

  DeleteGame(game_v, table_g);
  --table_g->n_el;
}

void __s__(gametable *table_g, int NL)
{
  game *game_v;
  char name[1024];
  int score1;
  int score2;
  for (int name_index = 0; name_index < 10; name_index++)
  {
    name[name_index] = new_sym_var(sizeof(char) * 8);
  }

  name[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  game_v = SearchGame(name, table_g);
  if (game_v == 0)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
      return;
    }
  }
  else
  {
    
  }

  if (game_v->score1 > game_v->score2)
  {
    {
      --game_v->team1->wins;
    }
  }
  else
  {
    
  }

  if (game_v->score2 > game_v->score1)
  {
    {
      --game_v->team2->wins;
    }
  }
  else
  {
    
  }

  game_v->score1 = score1;
  game_v->score2 = score2;
  AddWin(game_v, score1, score2);
}

int cmpstr(const void *a, const void *b)
{
  const char **aa = (const char **) a;
  const char **bb = (const char **) b;
  return strcmp(*aa, *bb);
}

void __g__(teamstable *table_t, int NL)
{
  int i;
  int n_winners = 0;
  int n_wins = 0;
  char **teamptr_array;
  teamptr_array = (char **) malloc((sizeof(char *)) * ((table_t->size / 2) + 1));
  for (i = 0; i < table_t->size; i++)
  {
    if (table_t->table[i] != 0)
    {
      {
        if (table_t->table[i]->wins > n_wins)
        {
          {
            n_wins = table_t->table[i]->wins;
            n_winners = 0;
          }
        }
        else
        {
          
        }

        if (table_t->table[i]->wins == n_wins)
        {
          {
            teamptr_array[n_winners] = table_t->table[i]->name;
            ++n_winners;
          }
        }
        else
        {
          
        }

      }
    }
    else
    {
      
    }

  }

  qsort(teamptr_array, n_winners, sizeof(char *), cmpstr);
  if (n_winners > 0)
  {
    {
      printf("%d Melhores %d\n", NL, n_wins);
    }
  }
  else
  {
    
  }

  for (i = 0; i < n_winners; i++)
  {
    printf("%d * %s\n", NL, teamptr_array[i]);
  }

  free(teamptr_array);
}

void __x__(teamstable *table_t, gametable *table_g)
{
  int i;
  for (i = 0; i < table_t->size; i++)
  {
    if (table_t->table[i] != 0)
    {
      {
        free(table_t->table[i]->name);
        free(table_t->table[i]);
      }
    }
    else
    {
      
    }

  }

  free(table_t->table);
  for (i = 0; i < table_g->size; i++)
  {
    if (table_g->table[i] != 0)
    {
      {
        free(table_g->table[i]->name);
        free(table_g->table[i]);
      }
    }
    else
    {
      
    }

  }

  free(table_g->table);
}
