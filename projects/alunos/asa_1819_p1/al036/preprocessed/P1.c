#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


struct dfspass
{
  int topsub;
  int time;
} dfspass;
struct ll
{
  int val;
  struct ll *next;
} ll;
int ponto(int size, int i, int j)
{
  return i + (j * size);
}

struct ll *llinsert(struct ll *entry, struct ll *list)
{
  struct ll *i;
  struct ll *j;
  if (list == 0)
  {
    return entry;
  }
  else
  {
    
  }

  for (i = list, j = 0; i != 0; j = i, i = i->next)
  {
    if (entry->val < i->val)
    {
      entry->next = i;
      if (j == 0)
      {
        return entry;
      }
      else
      {
        
      }

      j->next = entry;
      return list;
    }
    else
    {
      
    }

  }

  j->next = entry;
  return list;
}

int adj(struct ll *la, int a)
{
  if ((la == 0) || (la->val > a))
  {
    return 0;
  }
  else
  {
    
  }

  return (la->val == a) || adj(la->next, a);
}

struct dfspass *visita(int v, struct ll **la, int *Visitado, int Max, int *d, int *p, int *low, struct dfspass *pass)
{
  int i;
  Visitado[v] = 1;
  d[v] = ++pass->time;
  low[v] = pass->time;
  for (i = 0; i < Max; ++i)
  {
    if (adj(la[v], i) && (Visitado[i] == 0))
    {
      p[i] = v;
      if (i > pass->topsub)
      {
        pass->topsub = i;
      }
      else
      {
        
      }

      pass = visita(i, la, Visitado, Max, d, p, low, pass);
    }
    else
    {
      
    }

    if (((i != p[v]) && adj(la[v], i)) && ((low[v] == (-1)) || (low[i] < low[v])))
    {
      low[v] = low[i];
    }
    else
    {
      
    }

  }

  return pass;
}

int dimrede(int v, struct ll **la, int *Visitado, int Max, int num)
{
  int i;
  Visitado[v] = 1;
  num++;
  for (i = 0; i < Max; ++i)
  {
    if (adj(la[v], i) && (Visitado[i] == 0))
    {
      num = dimrede(i, la, Visitado, Max, num);
    }
    else
    {
      
    }

  }

  return num;
}

int main()
{
  int In;
  int In2;
  int e1;
  int e2;
  int i;
  struct ll **la;
  struct ll *topl;
  struct ll *entry;
  In = new_sym_var(sizeof(int) * 8);
  la = malloc(In * (sizeof(struct ll *)));
  for (i = 0; i < In; ++i)
  {
    la[i] = 0;
  }

  In2 = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < In2; ++i)
  {
    e1 = new_sym_var(sizeof(int) * 8);
    e2 = new_sym_var(sizeof(int) * 8);
    e1--;
    e2--;
    entry = malloc(sizeof(ll));
    entry->val = e2;
    entry->next = 0;
    la[e1] = llinsert(entry, la[e1]);
    entry = malloc(sizeof(ll));
    entry->val = e1;
    entry->next = 0;
    la[e2] = llinsert(entry, la[e2]);
  }

  int *Visitado;
  int *d;
  int *p;
  int *low;
  int Nsub = 0;
  Visitado = malloc(In * (sizeof(int)));
  d = malloc(In * (sizeof(int)));
  p = malloc(In * (sizeof(int)));
  low = malloc(In * (sizeof(int)));
  for (i = 0; i < In; ++i)
  {
    Visitado[i] = 0;
    d[i] = -1;
    p[i] = -1;
    low[i] = -1;
  }

  struct dfspass *pass;
  pass = malloc(sizeof(struct dfspass));
  pass->time = 0;
  topl = 0;
  for (i = 0; i < In; ++i)
  {
    if (Visitado[i] == 0)
    {
      Nsub++;
      pass->topsub = i;
      pass = visita(i, la, Visitado, In, d, p, low, pass);
      entry = malloc(sizeof(ll));
      entry->val = pass->topsub + 1;
      entry->next = 0;
      topl = llinsert(entry, topl);
    }
    else
    {
      
    }

  }

  entry = topl;
  printf("%d\n%d", Nsub, entry->val);
  for (i = 1; i < Nsub; ++i)
  {
    topl = entry;
    entry = entry->next;
    free(topl);
    printf(" %d", entry->val);
  }

  free(entry);
  printf("\n");
  free(pass);
  int np = 0;
  int j;
  int nl;
  for (i = 0; i < In; ++i)
  {
    if (p[i] == (-1))
    {
      nl = 0;
      for (j = 0; j < In; ++j)
      {
        if (p[j] == i)
        {
          nl++;
        }
        else
        {
          
        }

      }

      if (nl > 1)
      {
        np++;
        for (entry = la[i], topl = 0; entry != 0; topl = entry, entry = entry->next)
        {
          free(topl);
        }

        la[i] = 0;
      }
      else
      {
        
      }

    }
    else
    {
      for (j = 0; j < In; ++j)
      {
        if ((p[j] == i) && (low[j] >= d[i]))
        {
          np++;
          for (entry = la[i], topl = 0; entry != 0; topl = entry, entry = entry->next)
          {
            free(topl);
          }

          la[i] = 0;
          break;
        }
        else
        {
          
        }

      }

    }

  }

  printf("%d\n", np);
  int max = 1;
  for (i = 0; i < In; ++i)
  {
    Visitado[i] = 0;
  }

  for (i = 0; i < In; ++i)
  {
    if ((la[i] != 0) && (Visitado[i] == 0))
    {
      j = dimrede(i, la, Visitado, In, 0);
      if (j > max)
      {
        max = j;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  printf("%d\n", max);
  for (i = 0; i < In; ++i)
  {
    for (entry = la[i], topl = 0; entry != 0; topl = entry, entry = entry->next)
    {
      free(topl);
    }

  }

  free(la);
  free(d);
  free(p);
  free(Visitado);
  free(low);
  return 0;
}

