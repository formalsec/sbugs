#include <stdio.h>
#include <stdlib.h>
#include <wasp.h>
int v;
int e;
typedef struct edge *edge;
struct edge
{
  int v;
  edge nxt;
};
edge *E;
int *d;
int *low;
int *color;
int dc;
int arts;
int *As;
int *inAs;
int dfs(int pu, int u)
{
  color[u] = 1;
  d[u] = dc;
  low[u] = dc;
  dc++;
  int min;
  min = u;
  int vcs = 0;
  int artQ = 0;
  edge e;
  e = E[u];
  while (((void *) 0) != e)
  {
    if (0 == color[e->v])
    {
      vcs++;
      int t = dfs(u, e->v);
      if (t > min)
        min = t;
      if (low[e->v] < low[u])
      {
        low[u] = low[e->v];
      }
      if (((-1) != pu) && (low[e->v] >= d[u]))
      {
        artQ = 1;
      }
    }
    else
      if ((e->v != pu) && (d[e->v] < low[u]))
    {
      low[u] = d[e->v];
    }
    e = e->nxt;
  }

  if (((-1) == pu) && (1 < vcs))
  {
    artQ = 1;
  }
  if (1 == artQ)
  {
    As[arts] = u;
    inAs[u] = 1;
    arts++;
  }
  return min;
}

int RtDfs(int u)
{
  color[u] = 1;
  int size;
  size = 1;
  edge e;
  e = E[u];
  while (((void *) 0) != e)
  {
    if ((0 == inAs[e->v]) && (0 == color[e->v]))
    {
      size += RtDfs(e->v);
    }
    e = e->nxt;
  }

  return size;
}

static int intcmp(const void *p1, const void *p2)
{
  return (*((int *) p1)) - (*((int *) p2));
}

int main()
{
  int *nets;
  v = __WASP_symb_int("v");
  d = (int *) malloc(v * (sizeof(int)));
  low = (int *) malloc(v * (sizeof(int)));
  As = (int *) malloc(v * (sizeof(int)));
  inAs = (int *) calloc(v, sizeof(int));
  nets = (int *) malloc(v * (sizeof(int)));
  color = (int *) calloc(v, sizeof(int));
  E = (edge *) calloc(v, sizeof(edge));
  e = __WASP_symb_int("e");
  int i;
  i = 0;
  while (i < e)
  {
    int u;
    int v;
    u = __WASP_symb_int("u");
    u--;
    v = __WASP_symb_int("v");
    v--;
    edge a = (edge) malloc(sizeof(struct edge));
    a->v = v;
    a->nxt = E[u];
    E[u] = a;
    a = (edge) malloc(sizeof(struct edge));
    a->v = u;
    a->nxt = E[v];
    E[v] = a;
    i++;
  }

  dc = 0;
  arts = 0;
  int n = 0;
  i = 0;
  while (i < v)
  {
    if (0 == color[i])
    {
      nets[n] = dfs(-1, i);
      n++;
    }
    i++;
  }

  printf("%d\n", n);
  qsort(nets, n, sizeof(int), intcmp);
  i = 0;
  while (i < (n - 1))
  {
    printf("%d ", nets[i] + 1);
    i++;
  }

  printf("%d\n", nets[i] + 1);
  printf("%d\n", arts);
  i = 0;
  while (i < v)
    color[i++] = 0;

  int max = 0;
  i = 0;
  while (i < v)
  {
    if ((0 == inAs[i]) && (0 == color[i]))
    {
      int t = RtDfs(i);
      if (t > max)
        max = t;
    }
    i++;
  }

  printf("%d\n", max);
  i = 0;
  while (i < v)
  {
    edge e = E[i];
    while (((void *) 0) != e)
    {
      edge t = e->nxt;
      free(e);
      e = t;
    }

    i++;
  }

  free(d);
  free(low);
  free(As);
  free(inAs);
  free(nets);
  free(color);
  free(E);
  return 0;
}
