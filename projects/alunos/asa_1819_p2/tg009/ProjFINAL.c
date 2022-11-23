#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define oo 1000000000

int head,tail;

struct Graph{
  int vertices; 
  int f;  
  int e;  
  int t; 
  int countEst;
  int countLig;

  int* visited;
  int* arrayEst;
  int* color; 
  int* pred;  
  int* q;
  
  int** capacity; 
  int** transp;
  int** flow;
};

struct ArrayLig{
    int origin;
    int dest;
};

struct Graph* alloca_Graph(int v, int f, int e, int t){

  int i, j;

  struct Graph* Grafo = (struct Graph*) can_fail_malloc(sizeof(struct Graph));
  Grafo -> capacity = (int**) can_fail_malloc(sizeof(int*) * v);

  for(i=0; i<v; i++){
    Grafo->capacity[i] = (int*) can_fail_malloc(sizeof(int) * v);
  }

  Grafo -> flow = (int**) can_fail_malloc(sizeof(int*) * v);
  for(i=0; i<v; i++){
    Grafo->flow[i] = (int*) can_fail_malloc(sizeof(int) * v);
  }

  Grafo -> transp = (int**) can_fail_malloc(sizeof(int*) * v);
  for(i=0; i<v; i++){
    Grafo->transp[i] = (int*) can_fail_malloc(sizeof(int) * v);
  }

  Grafo -> visited = (int*) can_fail_malloc(sizeof(int) * v);
  Grafo -> arrayEst = (int*) can_fail_malloc(sizeof(int) * e);
  Grafo -> color = (int*) can_fail_malloc(sizeof(int) * v);
  Grafo -> pred = (int*) can_fail_malloc(sizeof(int) * v);
  Grafo -> q = (int*) can_fail_malloc(sizeof(int) * v);

  Grafo -> f = f;
  Grafo -> e = e;
  Grafo -> t = t;
  Grafo -> vertices = v;

  for (i=0; i<v; i++) {
      for (j=0; j<v; j++) {
          Grafo->capacity[i][j] = 0;
      }
  }

  for (i=0; i<v; i++) {
      for (j=0; j<v; j++) {
          Grafo->transp[i][j] = 0;
      }
  }

  for (i=0; i<v; i++) {
      for (j=0; j<v; j++) {
          Grafo->flow[i][j] = 0;
      }
  }

  for(i=0; i<v; i++){
    Grafo->visited[i] = 0;
  }
  return Grafo;
}

void free_Graph(struct Graph* Grafo, int v, int f, int e, int t){

  int i;  


  for(i=0; i<v; i++) {
    int* capacity = Grafo->capacity[i];
    free(capacity);
  }
  free(Grafo -> capacity);

  for(i=0; i<v; i++){
    int* flow = Grafo->flow[i];
    free(flow);
  }
  free(Grafo -> flow);

  
  for(i=0; i<v; i++){
    int* transp = Grafo->transp[i];
    free(transp);
  }
  free(Grafo -> transp);

  free(Grafo -> visited);
  free(Grafo -> arrayEst);
  free(Grafo -> color);
  free(Grafo -> pred);
  free(Grafo -> q);
}

int min (int x, int y) {
    return x<y ? x : y;
}

void enqueue (struct Graph* grafo, int x) {
    grafo->q[tail] = x;
    tail++;
    grafo->color[x] = GRAY;
}

int dequeue (struct Graph* grafo) {
    int x = grafo->q[head];
    head++;
    grafo->color[x] = BLACK;
    return x;
}


/* BFS para o algoritmo */

int bfs (struct Graph* grafo, int start, int target) {
    int u,v;
    int cont = 0;
    for (u=0; u<grafo->vertices; u++) {
	    grafo->color[u] = WHITE;
    }
    head = tail = 0;
    enqueue(grafo, start);
    grafo->pred[start] = -1;
    while (head!=tail) {
        u = dequeue(grafo);
        for (v=0; v<grafo->vertices; v++) {
            if (grafo->color[v]==WHITE && grafo->capacity[u][v]-grafo->flow[u][v]>0) {
                enqueue(grafo, v);
                grafo->pred[v] = u;
            }
        }
      cont++;
    }
    return grafo->color[target]==BLACK;
}


/* Algoritmo Edmonds-Karp para descobrir o fluxo maximo */

int max_flow (struct Graph* grafo, int source, int sink) {
    int u;
    int max_flow = 0;
    while (bfs(grafo,source,sink)) {
      int increment = oo;
      for (u=sink; grafo->pred[u]>=0; u=grafo->pred[u]) {
          increment = min(increment,grafo->capacity[grafo->pred[u]][u]-grafo->flow[grafo->pred[u]][u]);

      }
      for (u=sink; grafo->pred[u]>=0; u=grafo->pred[u]) {
          grafo->flow[grafo->pred[u]][u] += increment;
          grafo->flow[u][grafo->pred[u]] -= increment;
      }
      max_flow += increment;

      }

    return max_flow;
}


/* DFS para usar no grafo transposto */

void DFS(struct Graph* grafo, int i)
{
  int j;
    grafo->visited[i]=1;
	
	for(j=0;j<grafo->vertices;j++)
       if(grafo->visited[j]!=1&&grafo->transp[i][j]!=grafo->flow[j][i])
            DFS(grafo, j);
}

int cmpfunc(const void *a, const void *b){
  const struct ArrayLig *ca = a;
  const struct ArrayLig *cb = b;

  if(ca->origin == cb->origin){
    return (ca->dest - cb->dest);
  }
  return (ca->origin - cb->origin);
}


/* QuickSort */

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int* arr, int low, int high){
    int j;
    int pivot = arr[high];
    int i = (low - 1);
    
    for (j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


/* Ler os inputs */

int read_input_fornecedores() {
    int f;
    scanf("%d",&f);
    return f;
}

int read_input_estacoes() {
    int e;
    scanf("%d",&e);
    return e;
}

int read_input_ligacoes() {
    int t;
    scanf("%d",&t);
    return t;
}

void read_input_capFron(struct Graph* grafo, int f){
  int i;
  for(i=2; i<f+2; i++){
    scanf("%d", &grafo->capacity[0][i]);
  }
}

void read_input_capEst(struct Graph* grafo, int f, int e){
  int i;
  for(i=f+2; i<e+f+2; i++){
    scanf("%d", &grafo->capacity[i][i+e]);
  }
}

void read_input_fluxo(struct Graph* grafo, int f, int e, int t){
  int a, b, c, i;
  for(i=0; i<t; i++){
    scanf("%d%d%d", &a, &b, &c);
    if (a >= f+2) {
      grafo->capacity[a + e][b] = c;
    } else {
      grafo->capacity[a][b] = c;
    }
  }
}


/* Print da matriz */

void printMatrix(struct Graph* grafo){
  int i, j;
  for(i=0; i<grafo->vertices; i++){
    for(j=0; j<grafo->vertices; j++){
      printf("%3d ", grafo->capacity[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}


/* Transpor a matriz */

void transpMatrix(struct Graph* grafo){
  int i, j;
  for(i=0; i<grafo->vertices; i++){
    for(j=0; j<grafo->vertices; j++){
      grafo->transp[j][i] = grafo->capacity[i][j];
    }
  }
}

/* Print da Transposta */

void printTransp (struct Graph* grafo) {
  int i, j;
  for(i=0; i<grafo->vertices; i++){
    for(j=0; j<grafo->vertices; j++){
      printf("%3d ", grafo->transp[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}


/* Corte minimo */

void getMinCut(struct Graph* grafo, struct ArrayLig* arrayLig){
  int i, j, Est;
  grafo -> countEst = 0;
  grafo -> countLig = 0;
  for(i=0; i<grafo->vertices; i++){
    if(grafo->visited[i]==1){
      for(j=0; j<grafo->vertices; j++){
        if(grafo->transp[i][j]!=0 && grafo->visited[j]!=1){
          if (i>grafo->f+1 && j>grafo->f+1 && abs(j-i) == grafo->e) {
            Est = min(i, j);
            grafo->arrayEst[grafo -> countEst] = Est;
            grafo -> countEst++;
          } else if(j!=0){
              if(i>grafo->e+grafo->f+1){
                arrayLig[grafo -> countLig].dest = i-grafo->e;
                arrayLig[grafo -> countLig].origin = j;
                grafo -> countLig++;
              }
              else if(j>grafo->e+grafo->f+1){
                arrayLig[grafo -> countLig].dest = i;
                arrayLig[grafo -> countLig].origin = j-grafo->e;
                grafo -> countLig++;
              }
              else{
                arrayLig[grafo -> countLig].dest = i;
                arrayLig[grafo -> countLig].origin = j;
                grafo -> countLig++;
              }
          }
        }
      }
    }
  }
}


/* Main */

int main () {
    int i, j;

    /* Ler os inputs */
    int f = read_input_fornecedores();
    int e = read_input_estacoes();
    int t = read_input_ligacoes();

    /* Numero de vertices total (a source, o target, os fornecedores e 2 x as estacoes) */
    int vertices = 2 + f + (2 * e);

    struct Graph* newGrafo = alloca_Graph(vertices, f, e, t);
    struct ArrayLig* arrayLig = (struct ArrayLig*) can_fail_malloc(sizeof(struct ArrayLig));  

    read_input_capFron(newGrafo, f);
    read_input_capEst(newGrafo, f, e);
    read_input_fluxo(newGrafo, f, e, t);
    printf("%d\n",max_flow(newGrafo,0,1));
    transpMatrix(newGrafo);
    DFS(newGrafo, 1);
    getMinCut(newGrafo, arrayLig);
    quickSort(newGrafo->arrayEst, 0, newGrafo -> countEst-1);
    for(i=0; i < newGrafo -> countEst; i++){
      if(newGrafo->countEst-1 == i){
        printf("%d", newGrafo->arrayEst[i]);
      }
      else {
        printf("%d ", newGrafo->arrayEst[i]);
      }
    }
    printf("\n");
    qsort(arrayLig, newGrafo -> countLig, sizeof(struct ArrayLig), cmpfunc);
    for(j=0; j < newGrafo -> countLig; j++){
      printf("%d ", arrayLig[j].origin);
      printf("%d\n", arrayLig[j].dest);
    }

    free_Graph(newGrafo, vertices, f, e ,t);
    free(newGrafo);
    free(arrayLig);

    return 0;
}