#include <stdio.h>
#include <stdlib.h>
#include <wasp.h>
typedef struct edge *edge;
struct edge
{
  int v;
  edge nxt;
};
edge *G;
int *d;
static int DFS_visit(int v, int B)
{
  int Gb = 1;
  if (0 == (B & d[v]))
  {
    d[v] |= B;
    edge p = G[v];
    while (Gb && (((void *) 0) != p))
    {
      Gb = DFS_visit(p->v, B);
      Gb = Gb && (1 == (1 & d[p->v]));
      p = p->nxt;
    }

    d[v] |= 1;
  }
  return Gb;
}

int main()
{
  int i;
  int n;
  int m;
  int qa;
  int qb;
  edge *Gt;
  qa = __WASP_symb_int("qa");
  qa--;
  qb = __WASP_symb_int("qb");
  qb--;
  n = __WASP_symb_int("n");
  m = __WASP_symb_int("m");
  edge E;
  G = calloc(n, sizeof(edge));
  E = calloc(m, sizeof(struct edge));
  d = calloc(n, sizeof(int));
  for (i = 0; i < m; i++)
  {
    E[i].v = __WASP_symb_int("v");
    E[i].v--;
    int in;
    in = __WASP_symb_int("in");
    in--;
    E[i].nxt = G[in];
    G[in] = &E[i];
  }

  int Gb;
  Gb = 1;
  for (i = 0; Gb && (i < n); i++)
  {
    Gb = ((void *) 0) == G[i];
    Gb = Gb || (((void *) 0) == ((G[i]) ? (G[i]->nxt) : ((void *) 0)));
    Gb = Gb || (((void *) 0) == ((G[i]->nxt) ? (G[i]->nxt->nxt) : ((void *) 0)));
  }

  for (i = 0; Gb && (i < n); i++)
    Gb = DFS_visit(i, 2);

  if (Gb)
  {
    DFS_visit(qa, 4);
    DFS_visit(qb, 8);
    edge p;
    edge k;
    Gt = calloc(n, sizeof(edge));
    for (i = 0; i < n; i++)
    {
      p = G[i];
      while (((void *) 0) != p)
      {
        k = p->nxt;
        p->nxt = Gt[p->v];
        Gt[p->v] = p;
        p->v = i;
        p = k;
      }

    }

    int c;
    c = 0;
    for (i = 0; i < n; i++)
    {
      if ((4 == (d[i] & 4)) && (8 == (d[i] & 8)))
      {
        int l = 1;
        p = Gt[i];
        while (l && (((void *) 0) != p))
        {
          l = (4 != (4 & d[p->v])) || (8 != (8 & d[p->v]));
          p = p->nxt;
        }

        if (l)
        {
          printf("%d ", 1 + i);
          c++;
        }
      }
    }

    if (0 == c)
      printf("-");
    printf("\n");
    free(Gt);
  }
  else
  {
    printf("0\n");
  }
  free(d);
  free(E);
  free(G);
  return 0;
}
