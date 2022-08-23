/*File generated by PreProcessor.py*/


#include "data_structures.h"
#include "aux_functions.h"


void reads_input_game_full(Game *ng)
{
  getchar();
  ng->n = read_string(':');
  ng->t1 = read_string(':');
  ng->t2 = read_string(':');
  ng->s1 = read_number(':');
  ng->s2 = read_number('\n');
}

int error_check_a(Game *g, Game **G, int *G_sz, Team **T, int *T_sz, int *NL)
{
  if (HT_G_search(g->n, G, G_sz) != 0)
  {
    {
      printf("%d Jogo existente.\n", *NL);
      return 1;
    }
  }
  else
  {
    if ((HT_T_search(g->t1, T, T_sz) == 0) || (HT_T_search(g->t2, T, T_sz) == 0))
    {
      {
        printf("%d Equipa inexistente.\n", *NL);
        return 1;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

void update_games_won(char *slct, Game *g, Team **T, int *T_sz)
{
  Team *t1_HT = HT_T_search(g->t1, T, T_sz);
  Team *t2_HT = HT_T_search(g->t2, T, T_sz);
  int l;
  if ((l = strcmp(slct, "tie 1") == 0) || (strcmp(slct, "tie 2") == 0))
  {
    {
      if (l && (t1_HT->w > 0))
      {
        t1_HT->w -= 1;
      }
      else
      {
        if (t2_HT->w > 0)
        {
          t2_HT->w -= 1;
        }
        else
        {
          
        }

      }

    }
  }
  else
  {
    {
      if (g->s1 > g->s2)
      {
        {
          t1_HT->w += 1;
          if ((strcmp(slct, "g not new") == 0) && (t2_HT->w > 0))
          {
            t2_HT->w -= 1;
          }
          else
          {
            
          }

        }
      }
      else
      {
        if (g->s1 < g->s2)
        {
          {
            t2_HT->w += 1;
            if ((strcmp(slct, "g not new") == 0) && (t1_HT->w > 0))
            {
              t1_HT->w -= 1;
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

    }
  }

}

Team **A(Team **T, int *T_sz, int *T_n, int *NL)
{
  Team *nt = (Team *) malloc(sizeof(Team));
  getchar();
  nt->n = read_string('\n');
  nt->w = 0;
  if (HT_T_search(nt->n, T, T_sz) != 0)
  {
    {
      printf("%d Equipa existente.\n", *NL);
      free(nt->n);
      free(nt);
      return T;
    }
  }
  else
  {
    
  }

  *T_n += 1;
  T = HT_T_insert(nt, T, T_sz, T_n);
  return T;
}

void p(Game **G, int *G_sz, int *NL)
{
  char *name;
  Game *srch;
  getchar();
  name = read_string('\n');
  srch = HT_G_search(name, G, G_sz);
  if (srch == 0)
  {
    {
      printf("%d Jogo inexistente.\n", *NL);
    }
  }
  else
  {
    {
      printf("%d %s %s %s %d %d\n", *NL, srch->n, srch->t1, srch->t2, srch->s1, srch->s2);
    }
  }

  free(name);
}

void P(Team **T, int *T_n, int *NL)
{
  char *name;
  Team *srch;
  getchar();
  name = read_string('\n');
  srch = HT_T_search(name, T, T_n);
  if (srch == 0)
  {
    {
      printf("%d Equipa inexistente.\n", *NL);
    }
  }
  else
  {
    {
      printf("%d %s %d\n", *NL, srch->n, srch->w);
    }
  }

  free(name);
}

void l(node **ends, Game **G, int *G_sz, int *G_n, int *NL)
{
  Game *g;
  node *head = ends[0];
  node *t;
  getchar();
  if ((*G_n) == 0)
  {
    {
      return;
    }
  }
  else
  {
    
  }

  for (t = head; t != 0; t = t->next)
  {
    g = HT_G_search(t->text, G, G_sz);
    printf("%d %s %s %s %d %d\n", *NL, g->n, g->t1, g->t2, g->s1, g->s2);
  }

}

node **r(Game **G, int *G_sz, int *G_n, node **ends, Team **T, int *T_sz, int *NL)
{
  char *name;
  Game *srch;
  char *selector;
  int needs_update = 1;
  getchar();
  name = read_string('\n');
  srch = HT_G_search(name, G, G_sz);
  if (error_check_r_s(srch, name, NL))
  {
    return ends;
  }
  else
  {
    
  }

  if (srch->s1 == srch->s2)
  {
    needs_update = 0;
  }
  else
  {
    if (srch->s1 > srch->s2)
    {
      selector = "tie 1";
    }
    else
    {
      selector = "tie 2";
    }

  }

  if (needs_update)
  {
    update_games_won(selector, srch, T, T_sz);
  }
  else
  {
    
  }

  ends = lst_delete(ends, name);
  HT_G_delete(name, G, G_sz);
  *G_n -= 1;
  free(name);
  return ends;
}

void s(Game **G, int *G_sz, Team **T, int *T_sz, int *NL)
{
  Game *srch;
  char *name;
  char *prev_greater;
  int new_s1;
  int new_s2;
  int its_a_tie = 0;
  int needs_update = 1;
  int g_prev_tied = 0;
  getchar();
  name = read_string(':');
  new_s1 = read_number(':');
  new_s2 = read_number('\n');
  srch = HT_G_search(name, G, G_sz);
  if (error_check_r_s(srch, name, NL))
  {
    return;
  }
  else
  {
    
  }

  if (srch->s1 == srch->s2)
  {
    g_prev_tied = 1;
  }
  else
  {
    
  }

  if ((((srch->s1 > srch->s2) && (new_s1 > new_s2)) || ((srch->s1 < srch->s2) && (new_s1 < new_s2))) || ((srch->s1 == srch->s2) && (new_s1 == new_s2)))
  {
    {
      needs_update = 0;
    }
  }
  else
  {
    if (new_s1 == new_s2)
    {
      {
        its_a_tie = 1;
        if (srch->s1 > srch->s2)
        {
          prev_greater = "tie 1";
        }
        else
        {
          prev_greater = "tie 2";
        }

      }
    }
    else
    {
      
    }

  }

  srch->s1 = new_s1;
  srch->s2 = new_s2;
  if (needs_update)
  {
    {
      if (its_a_tie)
      {
        update_games_won(prev_greater, srch, T, T_sz);
      }
      else
      {
        if (g_prev_tied)
        {
          update_games_won("g not new prev tied", srch, T, T_sz);
        }
        else
        {
          update_games_won("g not new", srch, T, T_sz);
        }

      }

    }
  }
  else
  {
    
  }

  free(name);
}

void g(Team **T, int *T_sz, int *T_n, int *NL)
{
  int sz = *T_sz;
  int i;
  int max = 0;
  char **t_names = (char **) malloc((*T_n) * (sizeof(char *)));
  int len_t_names = 0;
  getchar();
  if ((*T_n) == 0)
  {
    {
      free(t_names);
      return;
    }
  }
  else
  {
    
  }

  for (i = 0; i < sz; i++)
  {
    if (T[i] != 0)
    {
      {
        if (T[i]->w > max)
        {
          {
            max = T[i]->w;
            len_t_names = 1;
            t_names[0] = T[i]->n;
          }
        }
        else
        {
          if (T[i]->w == max)
          {
            {
              len_t_names += 1;
              t_names[len_t_names - 1] = T[i]->n;
            }
          }
          else
          {
            
          }

        }

      }
    }
    else
    {
      
    }

  }

  qsort(t_names, len_t_names, sizeof(char *), comparator);
  printf("%d Melhores %d\n", *NL, max);
  for (i = 0; i < len_t_names; i++)
  {
    printf("%d * %s\n", *NL, t_names[i]);
  }

  free(t_names);
}

int main()
{
  int *NL = (int *) malloc(sizeof(int));
  Game **G = 0;
  int *G_sz = (int *) malloc(sizeof(int));
  int *G_n = (int *) malloc(sizeof(int));
  Team **T = 0;
  int *T_sz = (int *) malloc(sizeof(int));
  int *T_n = (int *) malloc(sizeof(int));
  node **ends = malloc((sizeof(node *)) * 2);
  int idc;
  Game *ng;
  *NL = 0;
  *G_sz = 10657;
  *G_n = 0;
  G = HT_G_init(G, G_sz);
  *T_sz = 10657;
  *T_n = 0;
  T = HT_T_init(T, T_sz);
  ends[0] = 0;
  ends[1] = 0;
  while ((idc = getchar()) != 'x')
  {
    *NL += 1;
    switch (idc)
    {
      case 'a':
        ng = malloc(sizeof(Game));
        reads_input_game_full(ng);
        if (error_check_a(ng, G, G_sz, T, T_sz, NL))
      {
        {
          free(ng->n);
          free(ng->t1);
          free(ng->t2);
          free(ng);
          break;
        }
      }
      else
      {
        
      }

        update_games_won("new", ng, T, T_sz);
        *G_n += 1;
        HT_G_insert(ng, G, G_sz);
        if ((*G_n) > ((*G_sz) / 2))
      {
        {
          G = HT_G_expand(G, G_sz);
        }
      }
      else
      {
        
      }

        ends = insert_END(ends, ng->n);
        break;

      case 'r':
        ends = r(G, G_sz, G_n, ends, T, T_sz, NL);
        break;

      case 'A':
        T = A(T, T_sz, T_n, NL);
        break;

      case 'p':
        p(G, G_sz, NL);
        break;

      case 'P':
        P(T, T_sz, NL);
        break;

      case 'l':
        l(ends, G, G_sz, G_n, NL);
        break;

      case 's':
        s(G, G_sz, T, T_sz, NL);
        break;

      case 'g':
        g(T, T_sz, T_n, NL);
        break;

    }

  }

  HT_G_free(G, G_sz);
  HT_T_free(T, T_sz);
  free_list(ends);
  free(NL);
  free(G_n);
  free(G_sz);
  free(T_n);
  free(T_sz);
  return 0;
}

