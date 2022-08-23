/*
 * File:  proj2.c
 * Author: 92443 Daniela Carvalho
 *         93718 Guilherme Barata
 * Description: Um programa que permite saber quantas pessoas podem ir a um supermercado
 *              sem se encontrarem umas com as outras.
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 4000

/* QUEUE */ 
struct queue {
  int items[SIZE];
  int front;
  int rear;
};

struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

void enqueue(struct queue* q, int value) {
  if (q->rear != SIZE - 1){
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      q->front = q->rear = -1;
    }
  }
  return item;
}


/* GRAFO */
struct node {
  int vertex;
  int capacity;
  int visited;
  struct node* next;
};
struct node* createNode(int);

struct Graph {
  int numVertices;
  struct node** adjLists;
};

struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->capacity = 1;
  newNode->next = NULL;
  newNode->visited = 0;
  return newNode;
}

struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;
  graph->adjLists = malloc(vertices * sizeof(struct node*));
  

  int i;
  for (i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;

  return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
  
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

}

void delEdge(struct Graph* graph, int src, int dst){
  struct node* temp = graph->adjLists[src];
    
  struct node* aux;
  while (temp){
    if(temp->vertex == dst){
      graph->adjLists[src] = temp -> next;
      free(temp);
      break;
    }
  
    if(temp->next != NULL && temp->next->vertex == dst){
      aux = temp->next;
      temp->next = temp->next->next;
      free(aux);
      break;
    }
    temp = temp->next;
  }
}


/* FUNCOES */
void preencher_supermercados(int S, int M, int N, struct Graph* graph);
void preencher_cidadaos(int C, int M, int N, struct Graph* graph, int sources[]);
void preencher_arestas(struct Graph* graph, int M, int N);
int bfs(struct Graph* graph, int startVertex, int M, int N, int pred[]);
int EdmundsKarp (struct Graph* graph, int sources[], int sink, int M, int N, int C, int n_ver);
void doFrees(struct Graph* graph, int numVert);

int main() {
  int M, N, S, C;
    
  scanf("%d %d", &M, &N);
  scanf("%d %d", &S, &C);

  int sources[C];

  struct Graph* graph = createGraph(2*M*N+1);
  preencher_arestas(graph, M, N);

  struct node* t = createNode(2*N*M);
  graph->adjLists[2*N*M] = t;

  preencher_supermercados(S, M, N, graph);
  preencher_cidadaos(C, M, N, graph, sources);
  printf("%d\n", EdmundsKarp(graph, sources, t->vertex, M, N, C, 2*M*N+1));
  doFrees(graph, 2*M*N+2);
   
  return 0;
}

void preencher_arestas(struct Graph* graph, int M, int N){
  int i;
  int num_vert = M*N*2;
  for (i=0; i<num_vert; i++){
    if(i%2 == 0){
      int cima = i-2*M+1;
      int baixo = i+2*M+1;
      int dta = i+3;
      int esq = i-1;
      if (cima >= 0) addEdge(graph, i, cima);
      if (baixo<num_vert) addEdge(graph, i, baixo);
      if (dta<num_vert && i%(2*M)!= 2*(M-1)) addEdge(graph, i, dta);
      if (esq >= 0 && i%(2*M)!=0) addEdge(graph, i, esq);
    }
    else{
      int cima = i-1;
      addEdge(graph, i, cima);
    }   
  }
}

/* SUPERMERCADOS */
void preencher_supermercados(int S, int M, int N, struct Graph* graph){
  int i;
  int av, rua;
  int flag=0;
    
  for (i=0; i<S; i++){
    scanf("%d %d", &av, &rua);
    int vertice = 2*((rua - 1) * M + av - 1);
    struct node * temp = graph->adjLists[vertice];
    while (temp){
      if (temp->vertex == 2*N*M){
        flag = 1;
      } 
      temp = temp->next;  
    }
    if (flag == 0) addEdge(graph, vertice, 2*N*M); 
    if (flag == 1) graph->adjLists[vertice]->capacity++;
    flag = 0;
  }
}

/* CIDADAOS */
void preencher_cidadaos(int C, int M, int N, struct Graph* graph, int sources[]){
  int i;
  int av, rua;
    
  for (i=0; i<C; i++){
    scanf("%d %d", &av,  &rua);
    int vertice = 2*((rua - 1) * M + av - 1)+1;
    sources[i] = vertice;
  }
}

/* BFS E EDMOND-KARP */
int bfs(struct Graph* graph, int startVertex, int M, int N, int pred[]) {

  int i;
  struct queue* q = createQueue();
  pred[startVertex] = -1;

  if (graph->adjLists[startVertex] == NULL ) return 0;

  graph->adjLists[startVertex]->visited = 1;
  enqueue(q, startVertex);

  while (!isEmpty(q)) {
    int currentVertex = dequeue(q);
    struct node* temp = graph->adjLists[currentVertex];

    while (temp) {
      int adjVertex = temp->vertex;

      if (graph->adjLists[adjVertex] != NULL && graph->adjLists[adjVertex]->capacity > 1){
        graph->adjLists[adjVertex]->visited = 0;
        graph->adjLists[adjVertex]->capacity--;
      }
    
      if (graph->adjLists[adjVertex] != NULL && graph->adjLists[adjVertex]->visited == 0 ) {
        pred[adjVertex] = currentVertex;
        if(adjVertex == 2*N*M){
          for(i=0; i<2*N*M+1; i++){
            if (graph->adjLists[i]!=NULL)
              graph->adjLists[i]->visited = 0;
            }
            free(q);
            return 1;
          }
          graph->adjLists[adjVertex]->visited = 1;
          enqueue(q, adjVertex);
        }
        temp = temp->next;
      }
    }
    
  for(i=0; i<2*N*M+1; i++){
    if (graph->adjLists[i]!=NULL) graph->adjLists[i]->visited = 0;
  }

  free(q);
  return 0;
}

int EdmundsKarp (struct Graph* graph, int sources[], int sink, int M, int N, int C, int n_ver){
  int i,e;
  int flow = 0;
  int pred[n_ver];
  for(e=0; e<C; e++){
    if(bfs(graph, sources[e], M, N, pred)){
      for(i=sink; pred[i]!=-1; i=pred[i]){
        delEdge(graph, pred[i], i);
        addEdge(graph, i, pred[i]);
      }
      flow++;
    }     
  }
  return flow;
}

/* FREES */
void doFrees(struct Graph* graph, int numVert){
  int i;

  for (i=0; i<numVert-1; i++){

    struct node * node_princ;
    struct node * node_aux;
    node_princ = graph->adjLists[i];

    while (node_princ != NULL){
      node_aux=node_princ;
      node_princ=node_princ->next;
      free(node_aux);
    }
  }

  free(graph->adjLists);
  free(graph);
}