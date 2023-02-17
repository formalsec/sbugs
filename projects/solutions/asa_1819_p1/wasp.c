#include <stdio.h>
#include <stdlib.h>
#include <wasp.h>

int v; /* Number of vertexes */
int e; /* Number of edges */

typedef struct edge* edge;

struct edge{
  int v; /* destination vertex */
  edge nxt; /* Next on list */
};

edge *E; /* The array containing edges, indexed by numbers */

int *d; /* DFS discovery times */
int *low; /* DFS low values */
int *color; /* DFS color values */

int dc; /* Discovery time counter */
int arts; /* Total number of articulation points */
int *As;  /* Array with articulation points */
int *inAs; /* Boolean for this point is articulation */

int
dfs(int pu, /* Previous u */
    int u   /* Current u */
    )
{
  color[u] = 1; /* Gray color */
  d[u] = dc;
  low[u] = dc;
  dc++;

  /* printf("call %d from %d\n", u+1, pu+1); */
  /* printf("low[%d] = %d\n", u+1, low[u]); */

  int min; /* Actually it is a max. Problem update. */
  min = u;

  /* inS[u] = 1; /\* Push into S *\/ */
  /* S[Stop] = u; */
  /* Stop++; */

  int vcs = 0;	/* Number of visit calls */
  int artQ = 0; /* By default not articulation */
  edge e;
  e = E[u];
  while(NULL != e){
    if(0 == color[e->v]){
      vcs++;
      int t = dfs(u, e->v);
      if (t > min)
	min = t;
      if( low[e->v] < low[u] ){
	low[u] = low[e->v];
	/* printf("low[%d] = %d\n", u+1, low[u]); */
      }
      if(-1 != pu && low[e->v] >= d[u]){ /* No backward edge to above u, for child */
	artQ = 1;
      }
    } else /* Backward edge, because there are no crossing edges */
      if( e->v != pu && d[e->v] < low[u] ){ /* Not (Back + Tree) pair */
	low[u] = d[e->v];
	/* printf("low[%d] = %d\n", u+1, low[u]); */
      }
    e = e->nxt;
  }

  if(-1 == pu && 1 < vcs){ /* No backward edge above u */
    artQ = 1;
  }

  if(1 == artQ){ /* Means articulation point */
    As[arts] = u;
    inAs[u] = 1;
    /* printf("Considering %d as art.\n", u+1); */
    arts++; /* Increase the number of articulation points */
  }

  return min;
}

int	    /* Restricted DFS */
RtDfs(int u   /* Current u */
      )
{
  color[u] = 1; /* Gray color */

  int size;
  size = 1;

  edge e;
  e = E[u];
  while(NULL != e){
    if(0 == inAs[e->v] && 0 == color[e->v]){ /* Skip articulation points */
      size += RtDfs(e->v);
    }
    e = e->nxt;
  }

  return size;
}

static int
intcmp(const void *p1, const void *p2)
{
  return *(int*)p1-*(int*)p2;
}

int main()
{
  int* nets;

  v = __WASP_symb_int("v");
  d = (int*)malloc(v*sizeof(int));
  low = (int*)malloc(v*sizeof(int));
  As = (int*)malloc(v*sizeof(int));
  inAs = (int*)calloc(v, sizeof(int));
  nets = (int*)malloc(v*sizeof(int));
  color = (int*)calloc(v, sizeof(int));
  E = (edge*)calloc(v, sizeof(edge));

  e = __WASP_symb_int("e");
  int i;

  i = 0;
  while(i<e){
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
  } /* Finish reading the graph */

  /* Run DFS algorithm */
  dc = 0;
  arts = 0; /* Number of articulation points */
  int n = 0; /* Number of networks */

  i = 0;
  while(i < v){
    if(0 == color[i]){ /* Means node not visited */
      nets[n] = dfs(-1, i);
      n++;
    }
    i++;
  }

  printf("%d\n",n);
  qsort(nets, n, sizeof(int), intcmp);
  i = 0;
  while(i < n-1){
    printf("%d ", nets[i]+1);
    i++;
  }
  printf("%d\n", nets[i]+1);

  printf("%d\n",arts); /* Number of articulation points */

  /* Find largest sub-net */
  i = 0;
  while(i< v)
    color[i++] = 0;

  int max = 0;
  i = 0;
  while(i < v){
    if(0 == inAs[i] && 0 == color[i]){ /* Means node not visited */
      int t = RtDfs(i);
      if (t > max)
	max = t;
    }
    i++;
  }

  printf("%d\n", max);


  i = 0;
  while(i < v){
    edge e = E[i];
    while(NULL != e){
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
