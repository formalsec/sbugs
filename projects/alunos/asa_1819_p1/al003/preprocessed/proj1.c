#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct node
{
  int v;
  struct node *next;
} *link;
typedef struct graph
{
  int V;
  int E;
  link *adj;
} *Graph;
link ids;
int C = 0;
int m = 0;
link list_newNode(int v)
{
  link x = (link) malloc(sizeof(struct node));
  x->v = v;
  x->next = 0;
  return x;
}

link list_insertBegin(int v, link head)
{
  link x = list_newNode(v);
  x->next = head;
  return x;
}

void list_free(link head)
{
  link x;
  while (head != 0)
  {
    x = head;
    head = head->next;
    free(x);
  }

}

Graph graph_init(int V)
{
  int v;
  Graph G = (Graph) malloc(sizeof(struct graph));
  G->V = V;
  G->E = 0;
  G->adj = (link *) malloc((V + 1) * (sizeof(link)));
  for (v = 0; v <= V; v++)
    G->adj[v] = 0;

  return G;
}

void graph_insertEdge(Graph G, int u, int v)
{
  G->adj[u] = list_insertBegin(v, G->adj[u]);
  G->adj[v] = list_insertBegin(u, G->adj[v]);
  G->E++;
}

void graph_DFSVisit(Graph G, int i, int *visited, int *d, int *pi, int *low, int *closed, int *unsafe, int *nvertices)
{
  link x;
  int suc = 0;
  int maxVertices = 1;
  low[i] = *visited;
  d[i] = *visited;
  (*visited)++;
  for (x = G->adj[i]; x != 0; x = x->next)
  {
    if (d[x->v] == 32767)
    {
      suc++;
      pi[x->v] = i;
      graph_DFSVisit(G, x->v, visited, d, pi, low, closed, unsafe, nvertices);
      low[i] = (low[i] < low[x->v]) ? (low[i]) : (low[x->v]);
      if (((pi[i] != (-1)) && (low[x->v] >= d[i])) && (unsafe[i] == 0))
      {
        C++;
        unsafe[i] = 1;
      }
      else
      {
        
      }

    }
    else
    {
      if (x->v != pi[i])
      {
        low[i] = (low[i] < d[x->v]) ? (low[i]) : (d[x->v]);
      }
      else
      {
        
      }

    }

  }

  if (((pi[i] == (-1)) && (suc > 1)) && (unsafe[i] == 0))
  {
    C++;
    unsafe[i] = 1;
  }
  else
  {
    
  }

  closed[i] = 1;
  if (unsafe[i] == 1)
  {
    nvertices[i] = 0;
  }
  else
  {
    for (x = G->adj[i]; x != 0; x = x->next)
    {
      if (closed[x->v] == 1)
      {
        maxVertices += nvertices[x->v];
        closed[x->v] = 2;
      }
      else
      {
        
      }

    }

    nvertices[i] = maxVertices;
  }

}

int graph_DFS(Graph G)
{
  int i;
  int R = 0;
  int visited = 0;
  int *d = (int *) malloc((G->V + 1) * (sizeof(int)));
  int *pi = (int *) malloc((G->V + 1) * (sizeof(int)));
  int *low = (int *) malloc((G->V + 1) * (sizeof(int)));
  int *closed = (int *) malloc((G->V + 1) * (sizeof(int)));
  int *unsafe = (int *) malloc((G->V + 1) * (sizeof(int)));
  int *nvertices = (int *) malloc((G->V + 1) * (sizeof(int)));
  for (i = 1; i <= G->V; i++)
  {
    d[i] = 32767;
    pi[i] = -1;
    low[i] = 32767;
    closed[i] = 0;
    unsafe[i] = 0;
    nvertices[i] = 0;
  }

  for (i = G->V; i >= 1; i--)
  {
    if (d[i] == 32767)
    {
      R++;
      ids = list_insertBegin(i, ids);
      graph_DFSVisit(G, i, &visited, d, pi, low, closed, unsafe, nvertices);
    }
    else
    {
      
    }

  }

  for (i = 1; i <= G->V; i++)
    m = (m > nvertices[i]) ? (m) : (nvertices[i]);

  free(d);
  free(pi);
  free(low);
  free(closed);
  free(unsafe);
  free(nvertices);
  return R;
}

void graph_destroy(Graph G)
{
  int i;
  for (i = 0; i <= G->V; i++)
    list_free(G->adj[i]);

  free(G->adj);
  free(G);
}

int main()
{
  Graph G;
  int V;
  int E;
  int R;
  int i;
  int u;
  int v;
  link x;
  V = new_sym_var(sizeof(int) * 8);
  E = new_sym_var(sizeof(int) * 8);
  G = graph_init(V);
  for (i = 0; i < E; i++)
  {
    u = new_sym_var(sizeof(int) * 8);
    v = new_sym_var(sizeof(int) * 8);
    graph_insertEdge(G, u, v);
  }

  R = graph_DFS(G);
  printf("%d\n", R);
  if (ids != 0)
  {
    for (x = ids; x != 0; x = x->next)
      if (x->next == 0)
    {
      printf("%d", x->v);
    }
    else
    {
      printf("%d ", x->v);
    }


  }
  else
  {
    
  }

  putchar('\n');
  printf("%d\n", C);
  printf("%d\n", m);
  list_free(ids);
  graph_destroy(G);
  return 0;
}

