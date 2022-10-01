/*File generated by PreProcessor.py*/


#include "data_structures.h"


node *NEW(char *text)
{
  node *x = malloc(sizeof(node));
  x->text = text;
  x->next = 0;
  x->prev = 0;
  return x;
}

node **insert_END(node **ends, char *text)
{
  node *head = ends[0];
  node *tail = ends[1];
  if (head == 0)
  {
    head = NEW(text);
    tail = head;
    ends[0] = head;
    ends[1] = tail;
    return ends;
  }
  else
  {
    
  }

  tail->next = NEW(text);
  tail->next->prev = tail;
  tail = tail->next;
  ends[0] = head;
  ends[1] = tail;
  return ends;
}

node **lst_delete(node **ends, char *text)
{
  node *t;
  node *head = ends[0];
  node *tail = ends[1];
  for (t = head; t != 0; t = t->next)
  {
    if (strcmp(t->text, text) == 0)
    {
      if ((t == head) && (t == tail))
      {
        head = t->next;
        tail = t->next;
      }
      else
      {
        if (t == head)
        {
          head = t->next;
          if (head != 0)
          {
            head->prev = 0;
          }
          else
          {
            
          }

        }
        else
        {
          if (t == tail)
          {
            tail = t->prev;
            tail->next = 0;
          }
          else
          {
            t->prev->next = t->next;
            t->next->prev = t->prev;
          }

        }

      }

      free(t);
      break;
    }
    else
    {
      
    }

  }

  ends[0] = head;
  ends[1] = tail;
  return ends;
}

void free_list(node **ends)
{
  node *head = ends[0];
  node *t;
  node *next;
  if (head == 0)
  {
    free(ends);
    return;
  }
  else
  {
    
  }

  for (t = head, next = t->next; next != 0; t = next, next = next->next)
  {
    free(t);
  }

  free(t);
  free(ends);
}

int hash(char *v, int M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (M - 1))
    h = ((a * h) + (*v)) % M;

  return abs(h);
}

Game **HT_G_init(Game **G, int *G_sz)
{
  int i;
  int sz = *G_sz;
  G = malloc(sz * (sizeof(Game)));
  for (i = 0; i < sz; i++)
    G[i] = 0;

  return G;
}

Team **HT_T_init(Team **T, int *T_sz)
{
  int i;
  int sz = *T_sz;
  T = malloc(sz * (sizeof(Team)));
  for (i = 0; i < sz; i++)
    T[i] = 0;

  return T;
}

void HT_G_free(Game **G, int *G_sz)
{
  int i;
  int sz = *G_sz;
  for (i = 0; i < sz; i++)
  {
    if (G[i] != 0)
    {
      free(G[i]->n);
      free(G[i]->t1);
      free(G[i]->t2);
      free(G[i]);
    }
    else
    {
      
    }

  }

  free(G);
}

void HT_T_free(Team **T, int *T_sz)
{
  int i;
  int sz = *T_sz;
  for (i = 0; i < sz; i++)
  {
    if (T[i] != 0)
    {
      free(T[i]->n);
      free(T[i]);
    }
    else
    {
      
    }

  }

  free(T);
}

Game **HT_G_expand(Game **G, int *G_sz)
{
  int i;
  Game **temp_G = G;
  *G_sz *= 2;
  G = HT_G_init(G, G_sz);
  for (i = 0; i < ((*G_sz) / 2); i++)
  {
    if (temp_G[i] != 0)
    {
      HT_G_insert(temp_G[i], G, G_sz);
    }
    else
    {
      
    }

  }

  free(temp_G);
  return G;
}

Team **HT_T_expand(Team **T, int *T_sz, int *T_n)
{
  int i;
  Team **temp_T = T;
  *T_sz *= 2;
  T = HT_T_init(T, T_sz);
  for (i = 0; i < ((*T_sz) / 2); i++)
    if (temp_T[i] != 0)
  {
    HT_T_insert(temp_T[i], T, T_sz, T_n);
  }
  else
  {
    
  }


  free(temp_T);
  return T;
}

void HT_G_insert(Game *g, Game **G, int *G_sz)
{
  int sz = *G_sz;
  int i = hash(g->n, sz);
  while (G[i] != 0)
    i = (i + 1) % sz;

  G[i] = g;
}

Team **HT_T_insert(Team *t, Team **T, int *T_sz, int *T_n)
{
  int sz = *T_sz;
  int i = hash(t->n, sz);
  while (T[i] != 0)
  {
    i = (i + 1) % sz;
  }

  T[i] = t;
  if ((*T_n) > ((*T_sz) / 2))
  {
    T = HT_T_expand(T, T_sz, T_n);
  }
  else
  {
    
  }

  return T;
}

Game *HT_G_search(char *name, Game **G, int *G_sz)
{
  int sz = *G_sz;
  int i = hash(name, sz);
  while (G[i] != 0)
  {
    if (strcmp(G[i]->n, name) == 0)
    {
      return G[i];
    }
    else
    {
      i = (i + 1) % sz;
    }

  }

  return 0;
}

Team *HT_T_search(char *name, Team **T, int *T_sz)
{
  int sz = *T_sz;
  int i = hash(name, sz);
  while (T[i] != 0)
  {
    if (strcmp(T[i]->n, name) == 0)
    {
      return T[i];
    }
    else
    {
      i = (i + 1) % sz;
    }

  }

  return 0;
}

void HT_G_delete(char *name, Game **G, int *G_sz)
{
  Game *g;
  int sz = *G_sz;
  int j;
  int i = hash(name, sz);
  while (G[i] != 0)
  {
    if (strcmp(G[i]->n, name) == 0)
    {
      break;
    }
    else
    {
      i = (i + 1) % sz;
    }

  }

  if (G[i] == 0)
  {
    return;
  }
  else
  {
    
  }

  free(G[i]->n);
  free(G[i]->t1);
  free(G[i]->t2);
  free(G[i]);
  G[i] = 0;
  for (j = (i + 1) % sz; G[j] != 0; j = (j + 1) % sz)
  {
    g = G[j];
    G[j] = 0;
    HT_G_insert(g, G, G_sz);
  }

}
