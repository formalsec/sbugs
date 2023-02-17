#include <stdio.h>
#include <stdlib.h>
#include <wasp.h>

typedef struct edge *edge;

struct edge{
  int v; /* Pointed vertex */
  edge nxt;
};

edge *G; /* Graph */
int *d; /* discovery and distance array */

static int
DFS_visit(int v,
    int B /* Indicator bit */
    ) /* Visit vertex */
{
  int Gb = 1; /* Valid graph */

  if(0 == (B & d[v])){
    d[v] |= B;

    edge p = G[v];
    while(Gb && NULL != p){
      Gb = DFS_visit(p->v, B);

      /* Gray vertex means back edge */
      Gb = Gb && 1 == (1 & d[p->v]);
      p = p->nxt;
    }

    d[v] |= 1;
  }

  return Gb;
}

int
main()
{
  int i;
  int n; /* Nodes */
  int m; /* Edges */
  int qa, qb; /* Query nodes */
  edge *Gt; /* Transposed Graph */

  qa = __WASP_symb_int("qa");
  qa--;
  qb = __WASP_symb_int("qb");
  qb--;

  n = __WASP_symb_int("n");
  m = __WASP_symb_int("m");

  edge E; /* Array of edges */

  G = calloc(n, sizeof(edge));
  E = calloc(m, sizeof(struct edge));
  d = calloc(n, sizeof(int));

  for(i = 0; i < m; i++){
    E[i].v = __WASP_symb_int("v");
    E[i].v--;

    int in;
    in = __WASP_symb_int("in");
    in--;
    E[i].nxt = G[in];
    G[in] = &E[i];
  }

  int Gb; /* Geo boolean */
  Gb = 1;

  /* Check degree */
  for(i = 0; Gb && i < n; i++){
    Gb = NULL == G[i];
    Gb = Gb || (NULL == ((G[i]) ? G[i]->nxt : NULL));
    Gb = Gb || (NULL == ((G[i]->nxt) ? G[i]->nxt->nxt : NULL));
  }

  /* Check cycles */
  for(i = 0; Gb && i < n; i++)
    Gb = DFS_visit(i, 2);

  if(Gb){ /* Do LCA computation */
    DFS_visit(qa, 4);
    DFS_visit(qb, 8);

    /* Transpose graph */
    edge p;
    edge k; /* keep */
    Gt = calloc(n, sizeof(edge));

    for(i = 0; i < n; i++){
      p = G[i];
      while(NULL != p){
        k = p->nxt;
        p->nxt = Gt[p->v];
        Gt[p->v] = p;
        p->v = i;
        p = k;
      }
    }

    int c;
    c = 0;
    for(i = 0; i < n; i++){
      if(4 == (d[i] & 4) && 8 == (d[i] & 8)){
        /* Check other common desc */
        int l = 1; /* True for lowest */
        p = Gt[i];
        while(l && NULL != p){
          l = 4 != (4 & d[p->v]) || 8 != (8 & d[p->v]);
          p = p->nxt;
        }
        if(l){
          printf("%d ", 1+i);
          c++;
        }
      }
    }
    if(0 == c)
      printf("-");
    printf("\n");

    free(Gt);
  } else {
    printf("0\n");
  }

  free(d);
  free(E);
  free(G);

  return 0;
}
