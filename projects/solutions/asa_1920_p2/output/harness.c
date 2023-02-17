#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wasp.h>
typedef struct node *link;
struct node
{
  int crossroad;
  int flow;
  int capacity;
  link next;
};
struct graph
{
  int V;
  int s;
  int t;
  link *adj;
};
typedef struct graph *Graph;
link insertBegin(int v, link head)
{
  link l = malloc(sizeof(struct node));
  l->crossroad = v;
  l->flow = 0;
  l->capacity = 1;
  l->next = head;
  return l;
}

int insertEdge(Graph G, int u, int v)
{
  link l;
  for (l = G->adj[u]; l != ((void *) 0); l = l->next)
  {
    if (l->crossroad == v)
    {
      if (l->flow == l->capacity)
        l->flow -= l->capacity;
      return 0;
    }
  }

  G->adj[u] = insertBegin(v, G->adj[u]);
  return 1;
}

Graph graphInit(int M, int N)
{
  int i;
  Graph G = malloc(sizeof(struct graph));
  G->V = (2 * (M * N)) + 2;
  G->s = G->V - 2;
  G->t = G->V - 1;
  G->adj = malloc(G->V * (sizeof(link)));
  for (i = 0; i < G->V; i++)
    G->adj[i] = (void *) 0;

  return G;
}

int whichVertex(Graph G, int m, int n, int M)
{
  return (M * n) - ((M - m) + 1);
}

void buildRoads(Graph G, int M, int N)
{
  int i;
  int j;
  int u;
  int v;
  for (i = 1; i <= N; i++)
  {
    for (j = 1; j <= M; j++)
    {
      u = whichVertex(G, j, i, M);
      if ((j + 1) <= M)
      {
        v = whichVertex(G, j + 1, i, M);
        insertEdge(G, u + (M * N), v);
        insertEdge(G, v + (M * N), u);
      }
      if ((i + 1) <= N)
      {
        v = whichVertex(G, j, i + 1, M);
        insertEdge(G, u + (M * N), v);
        insertEdge(G, v + (M * N), u);
      }
      insertEdge(G, u, u + (M * N));
    }

  }

}

void addCitizen(Graph G, int m, int n, int M)
{
  int v = whichVertex(G, m, n, M);
  insertEdge(G, G->s, v);
}

void addSupermarkets(Graph G, int m, int n, int M, int N)
{
  int v = whichVertex(G, m, n, M);
  insertEdge(G, v + (M * N), G->t);
}

void addingCitizenAndSupermarkets(Graph G, int S, int C, int M, int N, char *line)
{
  int num1;
  int num2;
  int i = 0;
  while (i < S)
  {
    num1 = __WASP_symb_int("num1");
    num2 = __WASP_symb_int("num2");
    addSupermarkets(G, num1, num2, M, N);
    i++;
  }

  i = 0;
  while (i < C)
  {
    num1 = __WASP_symb_int("num1");
    num2 = __WASP_symb_int("num2");
    addCitizen(G, num1, num2, M);
    i++;
  }

}

int QUEUEempty(link *head)
{
  return (*head) == ((void *) 0);
}

void QUEUEput(link *head, link *tail, int n)
{
  if ((*head) == ((void *) 0))
  {
    *head = (*tail = insertBegin(n, *head));
    return;
  }
  (*tail)->next = insertBegin(n, (*tail)->next);
  *tail = (*tail)->next;
}

int QUEUEget(link *head)
{
  int n = (*head)->crossroad;
  link l = (*head)->next;
  free(*head);
  *head = l;
  return n;
}

void freeQUEUE(link *head)
{
  link l;
  while (*head)
  {
    l = (*head)->next;
    free(*head);
    *head = l;
  }

}

int *BFS(Graph G, int s, int *p)
{
  link head = (void *) 0;
  link tail = (void *) 0;
  int *color = malloc(G->V * (sizeof(int)));
  memset(p, -1, G->V * (sizeof(int)));
  memset(color, 0, G->V * (sizeof(int)));
  p[s] = -2;
  QUEUEput(&head, &tail, s);
  while (!QUEUEempty(&head))
  {
    link l;
    int u = QUEUEget(&head);
    for (l = G->adj[u]; l != ((void *) 0); l = l->next)
    {
      int v = l->crossroad;
      if ((color[v] == 0) && ((l->capacity - l->flow) > 0))
      {
        p[v] = u;
        if (v == G->t)
        {
          free(color);
          freeQUEUE(&head);
          return p;
        }
        color[v] = 1;
        QUEUEput(&head, &tail, v);
      }
    }

    color[u] = 2;
  }

  free(color);
  return p;
}

int edmondsKarp(Graph G)
{
  int max = 0;
  int *p = malloc(G->V * (sizeof(int)));
  while (1)
  {
    int i;
    link l;
    p = BFS(G, G->s, p);
    if (p[G->t] == (-1))
      break;
    i = G->t;
    while (p[i] != (-2))
    {
      for (l = G->adj[p[i]]; l != ((void *) 0); l = l->next)
      {
        if (l->crossroad == i)
          l->flow += l->capacity;
      }

      insertEdge(G, i, p[i]);
      i = p[i];
    }

    max += 1;
  }

  free(p);
  return max;
}

void freeCity(Graph G)
{
  int i;
  link l;
  for (i = 0; i < G->V; i++)
  {
    while (G->adj[i])
    {
      l = G->adj[i];
      G->adj[i] = G->adj[i]->next;
      free(l);
    }

  }

  free(G->adj);
  free(G);
}

int main()
{
  char line[100];
  int M;
  int N;
  int S;
  int C;
  Graph City;
  M = __WASP_symb_int("M");
  N = __WASP_symb_int("N");
  City = graphInit(M, N);
  buildRoads(City, M, N);
  S = __WASP_symb_int("C");
  C = __WASP_symb_int("S");
  addingCitizenAndSupermarkets(City, S, C, M, N, line);
  printf("%d\n", edmondsKarp(City));
  freeCity(City);
  return 0;
}
