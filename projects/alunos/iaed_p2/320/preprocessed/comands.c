#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "games.h"
#include "teams.h"
#include "mysort.h"


void comand_a(int nl, dlist_games **hasht_g, dlist_teams **hasht_t, dlist_games *dl_g)
{
  int score1;
  int score2;
  char g_name[1024];
  char name_t1[1024];
  char name_t2[1024];
  game *p_g;
  team *p_t;
  node_dlist_games *other;
  for (int g_name_index = 0; g_name_index < 10; g_name_index++)
  {
    g_name[g_name_index] = new_sym_var(sizeof(char) * 8);
  }

  g_name[10 - 1] = '\0';
  for (int name_t1_index = 0; name_t1_index < 10; name_t1_index++)
  {
    name_t1[name_t1_index] = new_sym_var(sizeof(char) * 8);
  }

  name_t1[10 - 1] = '\0';
  for (int name_t2_index = 0; name_t2_index < 10; name_t2_index++)
  {
    name_t2[name_t2_index] = new_sym_var(sizeof(char) * 8);
  }

  name_t2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (search_hasht_g(hasht_g, g_name) != 0)
  {
    printf("%d Jogo existente.\n", nl);
  }
  else
  {
    if ((search_hasht_t(hasht_t, name_t1) == 0) || (search_hasht_t(hasht_t, name_t2) == 0))
    {
      printf("%d Equipa inexistente.\n", nl);
    }
    else
    {
      p_g = new_game(g_name, name_t1, name_t2, score1, score2);
      if (score1 > score2)
      {
        p_t = search_hasht_t(hasht_t, name_t1)->p_t;
        p_t->n_wins++;
      }
      else
      {
        
      }

      if (score1 < score2)
      {
        p_t = search_hasht_t(hasht_t, name_t2)->p_t;
        p_t->n_wins++;
      }
      else
      {
        
      }

      other = addlast_dlist_games(dl_g, p_g);
      insert_hasht_g(hasht_g, p_g, other);
    }

  }

}

void comand_A(int nl, dlist_teams **hasht_t)
{
  char t_name[1024];
  team *p_t;
  for (int t_name_index = 0; t_name_index < 10; t_name_index++)
  {
    t_name[t_name_index] = new_sym_var(sizeof(char) * 8);
  }

  t_name[10 - 1] = '\0';
  if (search_hasht_t(hasht_t, t_name))
  {
    printf("%d Equipa existente.\n", nl);
  }
  else
  {
    p_t = new_team(t_name);
    insert_hasht_t(hasht_t, p_t);
  }

}

void comand_l(int nl, dlist_games *dl_g)
{
  node_dlist_games *n_dl = dl_g->head;
  while (n_dl != 0)
  {
    printf("%d %s %s %s %d %d\n", nl, n_dl->p_g->g_name, n_dl->p_g->name_t1, n_dl->p_g->name_t2, n_dl->p_g->score1, n_dl->p_g->score2);
    n_dl = n_dl->next;
  }

}

void comand_p(int nl, dlist_games **hasht_g)
{
  char g_name[1024];
  node_dlist_games *n_dl;
  for (int g_name_index = 0; g_name_index < 10; g_name_index++)
  {
    g_name[g_name_index] = new_sym_var(sizeof(char) * 8);
  }

  g_name[10 - 1] = '\0';
  if ((n_dl = search_hasht_g(hasht_g, g_name)) == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    printf("%d %s %s %s %d %d\n", nl, g_name, n_dl->p_g->name_t1, n_dl->p_g->name_t2, n_dl->p_g->score1, n_dl->p_g->score2);
  }

}

void comand_P(int nl, dlist_teams **hasht_t)
{
  char t_name[1024];
  node_dlist_teams *n_dl;
  for (int t_name_index = 0; t_name_index < 10; t_name_index++)
  {
    t_name[t_name_index] = new_sym_var(sizeof(char) * 8);
  }

  t_name[10 - 1] = '\0';
  if ((n_dl = search_hasht_t(hasht_t, t_name)) == 0)
  {
    printf("%d Equipa inexistente.\n", nl);
  }
  else
  {
    printf("%d %s %d\n", nl, t_name, n_dl->p_t->n_wins);
  }

}

void comand_r(int nl, dlist_games **hasht_g, dlist_teams **hasht_t, dlist_games *dl_g)
{
  int score1;
  int score2;
  int h;
  char g_name[1024];
  team *p_t;
  node_dlist_games *n_dl;
  node_dlist_games *other;
  for (int g_name_index = 0; g_name_index < 10; g_name_index++)
  {
    g_name[g_name_index] = new_sym_var(sizeof(char) * 8);
  }

  g_name[10 - 1] = '\0';
  if ((n_dl = search_hasht_g(hasht_g, g_name)) == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    score1 = n_dl->p_g->score1;
    score2 = n_dl->p_g->score2;
    if (score1 > score2)
    {
      p_t = search_hasht_t(hasht_t, n_dl->p_g->name_t1)->p_t;
      p_t->n_wins--;
    }
    else
    {
      
    }

    if (score1 < score2)
    {
      p_t = search_hasht_t(hasht_t, n_dl->p_g->name_t2)->p_t;
      p_t->n_wins--;
    }
    else
    {
      
    }

    other = n_dl->other;
    h = hashf(g_name);
    rm_node_dlist_games(hasht_g[h], n_dl);
    rm_node_dlist_games(dl_g, other);
  }

}

void comand_s(int nl, dlist_games **hasht_g, dlist_teams **hasht_t)
{
  int score1;
  int score2;
  int pscore1;
  int pscore2;
  char g_name[1024];
  node_dlist_games *n_dl;
  node_dlist_teams *n_dl_t;
  for (int g_name_index = 0; g_name_index < 10; g_name_index++)
  {
    g_name[g_name_index] = new_sym_var(sizeof(char) * 8);
  }

  g_name[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if ((n_dl = search_hasht_g(hasht_g, g_name)) == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    pscore1 = n_dl->p_g->score1;
    pscore2 = n_dl->p_g->score2;
    n_dl->p_g->score1 = score1;
    n_dl->p_g->score2 = score2;
    if ((pscore1 > pscore2) && (score1 <= score2))
    {
      n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t1);
      n_dl_t->p_t->n_wins--;
      if (score1 < score2)
      {
        n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t2);
        n_dl_t->p_t->n_wins++;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    if ((pscore1 < pscore2) && (score1 >= score2))
    {
      n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t2);
      n_dl_t->p_t->n_wins--;
      if (score1 > score2)
      {
        n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t1);
        n_dl_t->p_t->n_wins++;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    if (pscore1 == pscore2)
    {
      if (score1 > score2)
      {
        n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t1);
        n_dl_t->p_t->n_wins++;
      }
      else
      {
        
      }

      if (score1 < score2)
      {
        n_dl_t = search_hasht_t(hasht_t, n_dl->p_g->name_t2);
        n_dl_t->p_t->n_wins++;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

}

void comand_g(int nl, dlist_teams **hasht_t)
{
  int ha_equipa = 0;
  int i;
  int j = 0;
  int max_wins = 0;
  int len;
  node_dlist_teams *n_dl;
  char **list_t = malloc((sizeof(char *)) * 1500);
  for (i = 0; i < 1500; i++)
  {
    n_dl = hasht_t[i]->head;
    while (n_dl != 0)
    {
      ha_equipa = 1;
      if (n_dl->p_t->n_wins > max_wins)
      {
        max_wins = n_dl->p_t->n_wins;
      }
      else
      {
        
      }

      n_dl = n_dl->next;
    }

  }

  if (ha_equipa)
  {
    printf("%d Melhores %d\n", nl, max_wins);
    for (i = 0; i < 1500; i++)
    {
      n_dl = hasht_t[i]->head;
      while (n_dl != 0)
      {
        if (n_dl->p_t->n_wins == max_wins)
        {
          len = strlen(n_dl->p_t->t_name) + 1;
          list_t[j] = malloc((sizeof(char)) * len);
          strcpy(list_t[j++], n_dl->p_t->t_name);
        }
        else
        {
          
        }

        n_dl = n_dl->next;
      }

    }

    sort_alpha(list_t, 0, j - 1);
    for (i = 0; i < j; i++)
    {
      printf("%d * %s\n", nl, list_t[i]);
      free(list_t[i]);
    }

  }
  else
  {
    
  }

  free(list_t);
}

