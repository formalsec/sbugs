#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>

#define MIN(X,Y) X < Y ? X : Y
#define INFINITE 10000000

int NODES;

void push(int ** C, int ** F, int *excess, int u, int v) {
  int send = MIN(excess[u], C[u][v] - F[u][v]);
  F[u][v] += send;
  F[v][u] -= send;
  excess[u] -= send;
  excess[v] += send;
}

void relabel(int ** C, int ** F, int *height, int u) {
  int v;
  int min_height = INFINITE;
  for (v = 0; v < NODES; v++) {
    if (C[u][v] - F[u][v] > 0) {
      min_height = MIN(min_height, height[v]);
      height[u] = min_height + 1;
    }
  }
}

void discharge(int ** C, int ** F, int *excess, int *height, int *seen, int u) {
  while (excess[u] > 0) {
    if (seen[u] < NODES) {
      int v = seen[u];
      if ((C[u][v] - F[u][v] > 0) && (height[u] > height[v])){
        push(C, F, excess, u, v);
      }
      else
        seen[u] += 1;
    } else {
      relabel(C, F, height, u);
      seen[u] = 0;
    }
  }
}

void moveToFront(int i, int *A) {
  int temp = A[i];
  int n;
  for (n = i; n > 0; n--){
    A[n] = A[n-1];
  }
  A[0] = temp;
}

int pushRelabel(int ** C, int ** F, int source, int sink) {
  int *excess, *height, *list, *seen, i, p;

  excess = (int *) can_fail_calloc(NODES, sizeof(int));
  height = (int *) can_fail_calloc(NODES, sizeof(int));
  seen = (int *) can_fail_calloc(NODES, sizeof(int));

  list = (int *) can_fail_calloc((NODES-2), sizeof(int));

  for (i = 0, p = 0; i < NODES; i++){
    if((i != source) && (i != sink)) {
      list[p] = i;
      p++;
    }
  }

  height[source] = NODES;
  excess[source] = INFINITE;
  for (i = 0; i < NODES; i++)
    push(C, F, excess, source, i);

  p = 0;
  while (p < NODES - 2) {
    int u = list[p];
    int old_height = height[u];
    discharge(C, F, excess, height, seen, u);
    if (height[u] > old_height) {
      moveToFront(p,list);
      p=0;
    }
    else
      p += 1;
  }
  int maxflow = 0;
  for (i = 0; i < NODES; i++)
    maxflow += F[source][i];

  free(list);

  free(seen);
  free(height);
  free(excess);

  return maxflow;
}

void printMatrix(int ** M) {
  int i,j;
  for (i = 0; i < NODES; i++) {
    for (j = 0; j < NODES; j++)
      printf("%d\t",M[i][j]);
    printf("\n");
  }
}

void dfs(int **flow,int **capacities, int t, bool visited[]) {
  int i;
    visited[t] = true;
    for (i = 0; i < NODES; i++) {
       if (-flow[t][i] < capacities[i][t] && !visited[i]) {

         dfs(flow, capacities, i, visited);
       }
    }
}

void minCut(int **flow, int **capacities, int fornecedores) {
  int i, j, j1 , i1 ;

  for (i = 0; i < NODES; i++)
    for (j = 0; j < NODES; j++)
      if (flow[i][j] > 0)
        flow[i][j] = 0;

  /*--find vertices reachable(visited) from t(hyper)--*/

  bool visited[NODES];
  memset(visited, false, sizeof(visited));

  dfs(flow, capacities, 1, visited);
  /*for (i=0 ; i < NODES; i++) {
    printf("%d\n", visited[i]);
  }*/
  
  for (i = 0; i < NODES; i++)
    for (j = 0; j < NODES; j++) {
       if (visited[i] && !visited[j] && capacities[j][i]) {
        i1 = i;
        j1 = j;
        
        if (j != 0 ) {
          /*printf("qui:%d %d", j ,i );*/
          if (j >= fornecedores + 2) {
            if (j == fornecedores +2){
              printf("%d\n",j );
              continue;
            }
                int aux = j +(fornecedores +2) -1;
                j1 = aux/2 ;
                if (i >= fornecedores +2)  {
                  printf("%d\n",j );
                  continue;
                }


          }
            if (i > fornecedores + 2) {
              int aux1 = i -(fornecedores +2);
              i1 = i1 + aux1;
            }
            if (j1 == 3) {
              printf("\n");
            }
            printf("%d %d\n",j1, i1 );
          }
          }
        }
       }

int main(void) {
  int **flow, **capacities, i, j;
  int fornecedores , postos , ligacoes;

  scanf("%d", &fornecedores);
  scanf("%d", &postos);
  scanf("%d", &ligacoes);

  NODES = fornecedores + (2*postos) + 2;

  flow = (int **) can_fail_calloc(NODES, sizeof(int*));
  capacities = (int **) can_fail_calloc(NODES, sizeof(int*));
  for (i = 0; i < NODES; i++) {
    flow[i] = (int *) can_fail_calloc(NODES, sizeof(int));
    capacities[i] = (int *) can_fail_calloc(NODES, sizeof(int));
  }

  for (i = 0; i < fornecedores; i++){
    int peso;
    scanf("%d", &peso);
    capacities[0][i + 2] = peso;
  }

  i = i + 2 ;

  for (j = 0; j < postos; j++){
    int peso2;
    scanf("%d", &peso2);
    capacities[i][i+1] = peso2;
    i = i + 2;
  }

  for (j = 0; j < ligacoes ; j++){
    int n1 , n2 , valor;
    scanf("%d", &n1);
    scanf("%d", &n2);
    scanf("%d", &valor);
    if (n1 >= fornecedores + 2) {
      int aux = n1 -(fornecedores +2);
      n1 = n1 + aux + 1;
    }
    if (n2 > fornecedores + 2) {
      int aux1 = n2 -(fornecedores +2);
      n2 = n2 + aux1;
    }

    capacities[n1][n2] = valor;
  }

  int maxf = pushRelabel(capacities, flow, 0, 1);
  printf("%d\n", maxf);

  if (maxf != 8)
    minCut(flow, capacities, fornecedores);
  else
    printf("\n");

  return 0;
}
