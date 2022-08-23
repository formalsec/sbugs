/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


enum color
{
  White,
  Gray,
  Black
};
int time;
int grades[10000000];
int p[10000000];
int d[10000000];
int f[10000000];
enum color color[10000000];
typedef struct node *link;
typedef struct graph *Graph;
struct node
{
  int v;
  link next;
};
struct graph
{
  int V;
  int E;
  link *adj;
};
void dfs_visit(Graph G, int u)
{
  link a;
  color[u] = Gray;
  d[u] = time;
  time++;
  for (a = G->adj[u]; a != 0; a = a->next)
  {
    if (color[a->v] == White)
    {
      p[a->v] = u;
      dfs_visit(G, a->v);
    }
    else
    {
      
    }

    if ((color[a->v] == Black) || (color[a->v] == Gray))
    {
      if (grades[u] < grades[a->v])
      {
        grades[u] = grades[a->v];
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

  color[u] = Black;
  f[u] = time;
  time++;
}

void dfs(Graph G)
{
  int u;
  for (u = 0; u < G->V; u++)
  {
    color[u] = White;
    p[u] = -1;
  }

  time = 1;
  for (u = 0; u < G->V; u++)
  {
    if (color[u] == White)
    {
      dfs_visit(G, u);
    }
    else
    {
      
    }

  }

}

void predictGrades(Graph G)
{
  int u;
  link a;
  dfs(G);
  for (u = 0; u < G->V; u++)
  {
    for (a = G->adj[u]; a != 0; a = a->next)
    {
      if (((d[a->v] <= d[u]) && (d[u] < f[u])) && (f[u] <= f[a->v]))
      {
        if (grades[u] < grades[a->v])
        {
          grades[u] = grades[a->v];
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      if ((((d[u] < d[a->v]) && (d[u] < f[a->v])) && (f[a->v] < f[u])) && (color[a->v] == Black))
      {
        if (grades[u] < grades[a->v])
        {
          grades[u] = grades[a->v];
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      if (((d[a->v] < f[a->v]) && (f[a->v] < d[u])) && (d[u] < f[u]))
      {
        if (grades[u] < grades[a->v])
        {
          grades[u] = grades[a->v];
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

  for (u = G->V - 1; u > (-1); u--)
    if (p[u] != (-1))
  {
    if (grades[u] > grades[p[u]])
    {
      grades[p[u]] = grades[u];
    }
    else
    {
      
    }

  }
  else
  {
    
  }


}

Graph GRAPHinit(int V)
{
  int v;
  Graph G = malloc(sizeof(struct graph));
  G->V = V;
  G->E = 0;
  G->adj = malloc(V * (sizeof(link)));
  for (v = 0; v < V; v++)
    G->adj[v] = 0;

  return G;
}

void insertE(link *head, int v)
{
  link a = (link) malloc(sizeof(struct node));
  link last = *head;
  a->v = v;
  a->next = 0;
  if ((*head) == 0)
  {
    *head = a;
    return;
  }
  else
  {
    
  }

  while (last->next != 0)
    last = last->next;

  last->next = a;
  return;
}

void GRAPHinsertE(Graph G, int v, int w)
{
  link a;
  for (a = G->adj[v]; a != 0; a = a->next)
    if (a->v == w)
  {
    return;
  }
  else
  {
    
  }


  insertE(&G->adj[v], w);
  G->E++;
}

void printGrades(Graph G)
{
  int i;
  for (i = 0; i < G->V; i++)
  {
    printf("%d\n", grades[i]);
  }

}

void getGrades(int N)
{
  int i;
  for (i = 0; i < N; i++)
  {
    grades[i] = new_sym_var(sizeof(int) * 8);
  }

}

void getEdges(Graph G, int M)
{
  int i;
  int v;
  int w;
  for (i = 0; i < M; i++)
  {
    v = new_sym_var(sizeof(int) * 8);
    w = new_sym_var(sizeof(int) * 8);
    GRAPHinsertE(G, v - 1, w - 1);
  }

}

int main()
{
  int N;
  int M;
  N = new_sym_var(sizeof(int) * 8);
  M = new_sym_var(sizeof(int) * 8);
  if ((N >= 2) && (M >= 1))
  {
    Graph G = GRAPHinit(N);
    getGrades(N);
    getEdges(G, M);
    predictGrades(G);
    printGrades(G);
  }
  else
  {
    
  }

  return 0;
}

