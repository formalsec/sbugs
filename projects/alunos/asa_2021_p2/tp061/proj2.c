#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define A 0
#define B 1
#define C 2
#define MAX_INT 2147483647
#define MIN(X,Y) (X<Y ? X : Y)
/*---------------------------------Structures---------------------------------*/
typedef struct graph{
  int* color;
  int* pred;
	int** Cij;                                                        /*capacity*/
  int** Fij;                                                            /*flow*/
} Graph;

/*------------------------------Global Variables------------------------------*/
Graph graph;                                                 /*saves the graph*/
int n;                                                   /*number of processes*/
int k;                              /*number of interactions between processes*/
int head, tail;
int* q;                                              /*variable used for queue*/

/*------------------------Enqueue and Dequeue functions-----------------------*/
void enqueue(int x) {
  q[tail] = x;
  tail++;
  graph.color[x] = B;
}

int dequeue() {
  int x = q[head];
  head++;
  graph.color[x] = C;
  return x;
}
/*---------------------Using BFS as a searching algorithm---------------------*/
int bfs(int start, int target) {
  int u, v;
  for (u = 0; u < (n+2); u++) {
    graph.color[u] = A;
  }
  head = tail = 0;
  enqueue(start);
  graph.pred[start] = -1;
  while (head != tail) {
    u = dequeue();
    for (v = 0; v < (n+2); v++) {
      if (graph.color[v] == A && graph.Cij[u][v] - graph.Fij[u][v] > 0) {
        enqueue(v);
        graph.pred[v] = u;
      }
    }
  }
  return graph.color[target] == C;
}

/*----------------------Applying fordfulkerson algorithm----------------------*/
int fordFulkerson(int source, int sink) {
  int u;
  int max_flow = 0;
  int increment = MAX_INT;

  while (bfs(source, sink)) {
    for (u = sink; graph.pred[u] >= 0; u = graph.pred[u]) {
      increment = MIN(increment, graph.Cij[graph.pred[u]][u] - graph.Fij[graph.pred[u]][u]);
    }
    for (u = sink; graph.pred[u] >= 0; u = graph.pred[u]) {
      graph.Fij[graph.pred[u]][u] += increment;
      graph.Fij[u][graph.pred[u]] -= increment;
    }
    /* Adding the path flows*/
    max_flow += increment;
  }
  return max_flow;
}

/*------------------------------------Main------------------------------------*/
int main() {
  int i, a, b, c;                               /*used for small operations*/
  /*allocate memory*/
  if (scanf("%d %d", &n, &k) == 2) {                             /*memory for:*/
    graph.Cij = can_fail_malloc(sizeof(int*)*(n+2));          /*capacity matrix lines*/
    graph.Fij = can_fail_malloc(sizeof(int*)*(n+2));              /*flow matrix lines*/
    graph.color = can_fail_malloc(sizeof(int)*(n+2));                    /*node color*/
    graph.pred = can_fail_malloc(sizeof(int)*(n+2));
    q = can_fail_malloc(sizeof(int)*(n+2));
    for (i = 0; i < (n+2); i++) {
      graph.Cij[i] = can_fail_calloc(sizeof(int), (n+2));    /*capacity matrix columns*/
      graph.Fij[i] = can_fail_calloc(sizeof(int), (n+2));        /*flow matrix columns*/
    }


    /*saves entries 0 and n+1 of matrix*/
    for (i = 0; i < n; i++) {
      if (scanf("%d %d", &a, &b) == 2) {
        graph.Cij[0][i+1] = a;
        graph.Cij[i+1][0] = a;
        graph.Cij[n+1][i+1] = b;
        graph.Cij[i+1][n+1] = b;
      }
    }
    /*saves entries of the matrix other then 0 and n+1*/
    for (i = 0; i < k; i++) {
      if (scanf("%d %d %d", &a, &b, &c) == 3) {
        graph.Cij[a][b] = c;
        graph.Cij[b][a] = c;
      }
    }

    /*OUTPUT*/
    printf("%d\n", fordFulkerson(0, n+1));

    /*release allocated memory*/
    for (i = 0; i < n+2; i++) {
      free(graph.Fij[i]);                              /*free matrix columns*/
      free(graph.Cij[i]);                              /*free matrix columns*/
    }
    free(q);
    free(graph.pred);
    free(graph.color);
    free(graph.Fij);                                     /*free matrix lines*/
    free(graph.Cij);                                     /*free matrix lines*/
    return 0;
  }
  /*if scanf==2 returned false*/
  return 1;
}
