#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
 * Project 1 - ASA
 * Made by: Nuno Alves && Jaime Costa
 */
#include <stdio.h>
#include <stdlib.h>

#define WHITE (0)
#define GRAY (1)
#define BLACK (2)

#define BLUE (1)  /* First node ancestor */
#define RED (-1) /* Second node ancestor */
#define GREEN (3) /* Both ancestor */

struct node {
  int ancestors[2];
  int num_ancestors;
  int color;
};

typedef struct node NODE;

static NODE *graph;
static int exist_ancestors = 0;

void read_graph(int n, int m) {
  int x, y;
  graph = (NODE*) can_fail_calloc(n, sizeof(NODE));
  NODE *node_ptr;

  while (--m >= 0) {
    scanf("%d %d", &x, &y);
    node_ptr = &graph[y-1];
    node_ptr->ancestors[node_ptr->num_ancestors++] = --x;
    if (node_ptr->num_ancestors > 2) {
      printf("0\n");
      exit(0);
    }
  }
}

void find_cycles_visit(int v) {
  int i;
  /* If have ancestors */
  graph[v].color = GRAY;
  for(i=0; i<graph[v].num_ancestors; ++i) {
    if (graph[graph[v].ancestors[i]].color == WHITE) {
      find_cycles_visit(graph[v].ancestors[i]);
    } else if (graph[graph[v].ancestors[i]].color == GRAY) { /* Have a cycle */
      printf("0\n");
      exit(0);
    }
  }
  graph[v].color = BLACK;
}

void find_cycles(int n) {
  int v;
  for(v=0; v<n; ++v) {
    if(graph[v].color == WHITE)
      find_cycles_visit(v);
  }
}

void find_ancestors_v1(int v) {
  int i;
  if (graph[v].color == BLUE) return; /* If ancestor already found */
  graph[v].color = BLUE; /* Mark as found */

  for(i=0; i<graph[v].num_ancestors; i++)
    find_ancestors_v1(graph[v].ancestors[i]); /* Mark other ancestors */
}

void fill_ancestors_red(int v) {
  int i;
  if (graph[v].color == RED) return; /* If ancestor already found */
  graph[v].color = RED; /* Mark as invalid LCA */

  for(i=0; i<graph[v].num_ancestors; i++) {
    fill_ancestors_red(graph[v].ancestors[i]); /* Mark ancestors as invalid LCA */
  }
}

void find_ancestors_v2(int v) {
  int i;
  if (graph[v].color == RED) return; /* If bad ancestor */
  if (graph[v].color == BLUE) { /* If common */
      graph[v].color= GREEN;
      exist_ancestors = 1;
      for(i=0; i<graph[v].num_ancestors; i++)
        fill_ancestors_red(graph[v].ancestors[i]);
  } else {
    for(i=0; i<graph[v].num_ancestors; i++)
      find_ancestors_v2(graph[v].ancestors[i]);
  }
}

void print_lca(int n) {
  int i;
  if(!exist_ancestors){
    printf("-\n");
  } else {
    for (i=0; i<n; i++)
      if (graph[i].color == GREEN) printf("%d ", i+1);
    printf("\n");
  }
}

int main() {
  int v1, v2, n, m;
  scanf("%d %d %d %d", &v1, &v2, &n, &m);

  read_graph(n, m);
  find_cycles(n);
  find_ancestors_v1(--v1);
  find_ancestors_v2(--v2);
  print_lca(n);

  return 0;
}

