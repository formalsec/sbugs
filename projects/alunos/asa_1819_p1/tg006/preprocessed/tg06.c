#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct general *grid;
typedef struct dfs_ex *dfs;
typedef struct node *link;
struct dfs_ex
{
  _Bool bigId;
  _Bool erased;
  char nSons;
  char state;
  int visitTime;
  int lowTime;
  int pi;
};
struct general
{
  int nRouters;
  int nConections;
  int nsubgrid;
  int time;
  int nArtic;
  dfs *extras;
  link *adj;
};
struct node
{
  int id;
  link next;
};
void dfs_torjan(grid);
int visit_dfs_torjan(grid, int, int);
int dfs_max(grid);
int visit_dfs_max(grid, dfs, int, int);
link create_list();
link insertBegin(link, int);
void free_link(link);
int main()
{
  int i = 0;
  int adj1;
  int adj2;
  grid general = (grid) malloc(sizeof(struct general));
  if (((2 != 2) || (general->nRouters < 2)) || (general->nConections < 1))
  {
    perror("Erro na leitura de inputs");
    exit(1);
  }
  else
  {
    general->nRouters = new_sym_var(sizeof(int) * 8);
    general->nConections = new_sym_var(sizeof(int) * 8);
    
  }

  general->nsubgrid = 0;
  general->time = 0;
  general->nArtic = 0;
  general->extras = (dfs *) malloc((sizeof(dfs)) * general->nRouters);
  general->adj = (link *) malloc((sizeof(link)) * general->nRouters);
  for (; i < general->nRouters; i++)
  {
    general->extras[i] = (dfs) malloc(sizeof(struct dfs_ex));
    general->extras[i]->visitTime = 0;
    general->extras[i]->lowTime = 0;
    general->extras[i]->nSons = 0;
    general->extras[i]->state = 0;
    general->extras[i]->erased = 0;
    general->extras[i]->pi = 0;
    general->extras[i]->bigId = 0;
    general->adj[i] = 0;
  }

  for (i = 0; i < general->nConections; i++)
  {
    if (((((2 != 2) || (adj1 < 1)) || (adj1 > general->nRouters)) || (adj2 < 1)) || (adj2 > general->nRouters))
    {
      perror("Erro na leitura de inputs");
      exit(1);
    }
    else
    {
      adj1 = new_sym_var(sizeof(int) * 8);
      adj2 = new_sym_var(sizeof(int) * 8);
      
    }

    if ((adj1 > general->nRouters) || (adj2 > general->nRouters))
    {
      perror("Erro na leitura de inputs");
      exit(1);
    }
    else
    {
      
    }

    general->adj[adj1 - 1] = insertBegin(general->adj[adj1 - 1], adj2);
    general->adj[adj2 - 1] = insertBegin(general->adj[adj2 - 1], adj1);
  }

  dfs_torjan(general);
  printf("%d\n", general->nsubgrid);
  for (i = 0; i < general->nRouters; i++)
  {
    if (general->extras[i]->bigId == 1)
    {
      if ((--general->nsubgrid) == 0)
      {
        printf("%d\n", i + 1);
        break;
      }
      else
      {
        
      }

      printf("%d ", i + 1);
    }
    else
    {
      
    }

  }

  printf("%d\n", general->nArtic);
  printf("%d\n", dfs_max(general));
  for (i = 0; i < general->nRouters; i++)
  {
    free_link(general->adj[i]);
    free(general->extras[i]);
  }

  free(general->adj);
  free(general->extras);
  free(general);
  exit(0);
}

void dfs_torjan(grid general)
{
  int i = 0;
  int bigId = 0;
  dfs *extras = general->extras;
  for (; i < general->nRouters; i++)
  {
    if (extras[i]->state == 0)
    {
      general->nsubgrid++;
      bigId = visit_dfs_torjan(general, i, i);
      general->extras[bigId]->bigId = 1;
      if (extras[i]->nSons > 1)
      {
        general->nArtic++;
        extras[i]->erased = 1;
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

int visit_dfs_torjan(grid general, int vId, int bigId)
{
  link edge = 0;
  int eId = 0;
  dfs Vextras = general->extras[vId];
  dfs Eextras = 0;
  Vextras->visitTime = ++general->time;
  Vextras->lowTime = general->time;
  Vextras->state = 1;
  Vextras->nSons = 0;
  for (edge = general->adj[vId]; edge != 0; edge = edge->next)
  {
    eId = edge->id - 1;
    Eextras = general->extras[eId];
    if (Eextras->state == 0)
    {
      if (bigId < eId)
      {
        bigId = eId;
      }
      else
      {
        
      }

      if (Vextras->nSons < 2)
      {
        Vextras->nSons++;
      }
      else
      {
        
      }

      Eextras->pi = vId + 1;
      bigId = visit_dfs_torjan(general, eId, bigId);
      Vextras->lowTime = (Eextras->lowTime < Vextras->lowTime) ? (Eextras->lowTime) : (Vextras->lowTime);
      if (((Vextras->erased == 0) && (Vextras->pi != 0)) && (Vextras->visitTime <= Eextras->lowTime))
      {
        general->nArtic++;
        Vextras->erased = 1;
      }
      else
      {
        
      }

    }
    else
    {
      if ((Eextras->state == 1) && (Vextras->pi != (eId + 1)))
      {
        Vextras->lowTime = (Vextras->lowTime < Eextras->visitTime) ? (Vextras->lowTime) : (Eextras->visitTime);
      }
      else
      {
        
      }

    }

  }

  Vextras->state = 2;
  return bigId;
}

int dfs_max(grid general)
{
  dfs *Vextras = general->extras;
  int max[2] = {0, 0};
  int i = 0;
  for (; i < general->nRouters; i++)
  {
    if (Vextras[i]->erased == 1)
    {
      continue;
    }
    else
    {
      
    }

    if (Vextras[i]->state == 2)
    {
      max[1] = visit_dfs_max(general, Vextras[i], 0, i);
      if (max[0] < max[1])
      {
        max[0] = max[1];
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  return max[0];
}

int visit_dfs_max(grid general, dfs Vextras, int max, int vId)
{
  link edge = 0;
  int eId = 0;
  dfs Eextras = 0;
  if (Vextras->state == 2)
  {
    max++;
  }
  else
  {
    
  }

  Vextras->state = 3;
  for (edge = general->adj[vId]; edge != 0; edge = edge->next)
  {
    eId = edge->id - 1;
    Eextras = general->extras[eId];
    if (Eextras->erased == 1)
    {
      continue;
    }
    else
    {
      
    }

    if (Eextras->state == 2)
    {
      max = visit_dfs_max(general, Eextras, max, eId);
    }
    else
    {
      
    }

  }

  Vextras->state = 4;
  return max;
}

link insertBegin(link head, int i)
{
  link newEl = malloc(sizeof(struct node));
  newEl->id = i;
  newEl->next = head;
  return newEl;
}

void free_link(link ls)
{
  link p = 0;
  while (ls != 0)
  {
    p = ls->next;
    free(ls);
    ls = p;
  }

}
