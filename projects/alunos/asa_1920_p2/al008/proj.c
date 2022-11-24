#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*==============================================================================
                                ASA - PROJECT 2
                                    GROUP 8
                              Maria Duarte nº90415
                              Laura Baeta nº92507
==============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define CITZEN 2
#define EMPTY 0
#define SUPMARK 1
#define INT_MAX 1
#define NOTHING -1
#define SOMETHING 1

/*Struct that represents a node in a adjacency list*/
struct Node{
  int dest;
  struct Node* next;
  int key;
};

/*Struct that represents a Graph in a form of an array of adjacency lists*/
struct Graph{
  /*Number of vertices*/
  int V;
  /*Array that holds the grades of each student*/
  struct Node** array;
  int* visited;
  int* parent;
};

/*Struct that represents a Queue that contains the frontier along which the
algorithm BFS is currently searching*/
struct Queue {
    int* items;
    int front;
    int size;
};

struct Node* newNode(int dest);
struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest);
void deleteEdge(struct Graph* graph, int src, int neighbor);
void addSuperMarket(int numSMark, int t, int numAvn, struct Graph* graph);
void addCitzen(int numCitzen, int numAvn, int numSt, struct Graph* graph);
void connectNeighbors(struct Graph* graph, int numAvn, int numSt);
void freeList(struct Node* head);
struct Queue *createQueue();
void freeQueue(struct Queue* queue);
int isEmpty(struct Queue *q);
void enqueue(struct Queue *q, int value);
int dequeue(struct Queue *q);
int bfs(struct Graph* graph, int startVertex, int sink, int n);
int edmondsKarp(struct Graph* graph, int s, int t, int n);

/*==============================================================================
                                    GRAPH
==============================================================================*/
/*Function to create a new adjacency list node*/
struct Node* newNode(int dest) {
  struct Node* node = (struct Node*)can_fail_malloc(sizeof(struct Node));
  node->dest = (dest);
  node->next = NULL;
  return node;
}

/*Function that creates a graph of V vertices*/
struct Graph* createGraph(int V) {
  int i;
  struct Graph* graph = (struct Graph*)can_fail_malloc(sizeof(struct Graph));
  graph->V = V;
  /*Create an array of adjacency lists.*/
  graph->array = (struct Node**)can_fail_calloc(V, sizeof(struct Node*));
  graph->visited = (int*)can_fail_calloc(V, sizeof(int));
  graph->parent = (int*)can_fail_calloc(V, sizeof(int));

  for (i = 0; i < V; i++) {
      graph->array[i] = (struct Node*)can_fail_calloc(1, sizeof(struct Node));
      graph->parent[i] = -1;
  }

  return graph;
}

/*Function that adds an edge to the graph */
void addEdge(struct Graph* graph, int src, int dest) {
  /*Add an edge from src to dest.
  A new node is added to the adjacency list of (src-1).
  The node is added at the end*/
  struct Node* node = newNode(dest);

  if (graph->array[src] == NULL) {
      graph->array[src] = node;
  }
  else {
      struct Node* temp = graph->array[src];
      while (temp->next) {
          temp = temp->next;
      }
      temp->next = node;
  }
}

/*Function that deletes  an edge of the graph */
void deleteEdge(struct Graph* graph, int src, int neighbor){
  struct Node* current = graph->array[src];
  struct Node* temp;

  while (current){
    /*Verifies if neighbor we want to delete is in the head of the linked list*/
    if(current->dest == neighbor){
      /*If so it will change first to point to next link*/
      graph->array[src] = current->next;
      free(current);
      break;
    }

    else if(current->next == NULL){
      /*Else it will return if the neighbor does not belong to the linked list*/
      return;
    }

    else if(current->next->dest == neighbor){
      /*Else it will bypass the current link*/
      temp = current->next;
      current->next = temp->next;
      free(temp);
      break;
    }
    current = current->next;
  }
}

/*==============================================================================
                              AUXILIARY FUNCTIONS
==============================================================================*/
/*Function that will add the values read from stdin, that correspond to the
positions of super-makets, to array of adjacency lists'array' in the struct
Graph graph. It will also connect the super-market vertexes to an artificial
sink*/
void addSuperMarket(int numSMark, int t, int numAvn, struct Graph* graph) {
  int i, index;
  int av, st;
  char buffer[100];

  for (i = 0; i<numSMark; i++) {
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%d %d", &av, &st);
    index=2*((st-1)*numAvn+av);
    addEdge(graph, index, t);
    graph->array[index]->key=SUPMARK;
    graph->array[index-1]->key=SUPMARK;
  }
}

/*Function that will add the values read from stdin, that correspond to the
positions of citizens, to array of adjacency lists'array' in the struct
Graph graph. It will also connect the citizens vertexes to an artificial
source*/
void addCitzen(int numCitzen, int s, int numAvn, struct Graph* graph) {
  int i, index;
  int av, st;
  char buffer[100];

  for (i = 0; i<numCitzen; i++) {
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%d %d", &av, &st);
    index = 2*((st-1)*numAvn+av)-1;
    addEdge(graph, s, index);
    graph->array[index]->key=CITZEN;
    graph->array[index+1]->key=CITZEN;
  }
}

/*Connects each vertex with all it's possible neighbors*/
void connectNeighbors(struct Graph* graph, int numAvn, int numSt){
  int i;
  int total=2*numAvn*numSt;
  for(i=1; i<(graph->V-1); i++){

    /*Will connect Vin and Vout of super-markets*/
    if(graph->array[i]->key == SUPMARK && i%2!=0){
        addEdge(graph, i, i+1);
    }

    if(graph->array[i]->key!=SUPMARK){
      if(i%2!=0){
        /*Will connect Vin and Vout of non super-markets*/
        addEdge(graph, i, i+1);
      }
      else{
        if(i>2*numAvn)
          addEdge(graph, i, i-2*numAvn-1); /*connect with above vertex*/
        if(i>3 && (i-2)%numAvn!=0)
          addEdge(graph, i, i-3); /*connect with left vertex*/
        if(i==2 || (i)%(numAvn*2)!=0)
          addEdge(graph, i, i+1); /*connect with right vertex*/
        if(i<=total-2*numAvn)
          addEdge(graph, i, i+2*numAvn-1); /*connect with below vertex*/
      }
    }
  }
}

/*Function that will free an adjacency list*/
void freeList(struct Node* head) {
  struct Node* tmp;
  while (head != NULL) {
      tmp = head;
      head = head->next;
      free(tmp);
  }
}

/*==============================================================================
                                    QUEUE
==============================================================================*/
/*Function that creates a queue whose size will change depending of it's
content*/
struct Queue *createQueue() {
  struct Queue *q = can_fail_malloc(sizeof(struct Queue));
  q->front = 0;
  q->size = 0;
  q->items = NULL;
  return q;
}

/*Function that will free a queue*/
void freeQueue(struct Queue* queue) {
  free(queue->items);
  free(queue);
}

/*Function that verifies the queue is empty*/
int isEmpty(struct Queue *q) {
  return q->size == q->front;
}

/*Function that will add a value to the queue*/
void enqueue(struct Queue *q, int value) {
  /*Will increment size and relocate the memory occupied by the array 'items'
  according to it*/
  q->size += 1;
  q->items = can_fail_realloc(q->items, q->size * sizeof(int));
  q->items[q->size-1] = value;
}

/*Function that will return the first value in the array 'items'*/
int dequeue(struct Queue *q) {
  if (isEmpty(q)) {
      return NOTHING;
  }
  int value = q->items[q->front];
  q->front += 1;/*The first value in the array will be next one*/
  return value;
}


/*==============================================================================
                                      BFS
==============================================================================*/
/*BFS algorithm*/
int bfs(struct Graph* graph, int startVertex, int sink, int n) {

  struct Queue* q = createQueue();

  memset(graph->parent, -1, graph->V * sizeof(int));
  memset(graph->visited, 0, graph->V * sizeof(int));

  graph->visited[startVertex] = 1;

  enqueue(q, startVertex);
  while (!isEmpty(q)) {
    int currentVertex = dequeue(q);

    struct Node* temp = graph->array[currentVertex];

    while (temp!=NULL) {
      int adjVertex = temp->dest;

      if (graph->visited[adjVertex] == 0){
          enqueue(q, adjVertex);
          graph->visited[adjVertex] = 1;
          graph->parent[adjVertex]=currentVertex;
      }
      temp = temp->next;
    }
  }

  freeQueue(q);

  if(graph->visited[sink]==TRUE){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

/*==============================================================================
                                  Edmonds-Karp
==============================================================================*/
/*Edmonds-Karp algorithm*/
int edmondsKarp(struct Graph* graph, int s, int t, int n) {
  int flow=0;
  int j;

  while(bfs(graph, s, t, n)){
    for(j=t; graph->parent[j]!=-1;j=graph->parent[j]){
      deleteEdge(graph, graph->parent[j], j);
      addEdge(graph, j, graph->parent[j]);
    }
    flow++;
  }

  return flow;
}

/*==============================================================================
                                      MAIN
==============================================================================*/
int main() {
  int numSt, numAvn;
  int numSMark, numCitzen;
  char buffer[100];
  int i;
  int s,t;

  fgets(buffer, 100, stdin);
  sscanf(buffer, "%d %d", &numAvn, &numSt);

  fgets(buffer, 100, stdin);
  sscanf(buffer, "%d %d", &numSMark, &numCitzen);

  /*artificial source and sink*/
  s=0;
  t=2*(numAvn*numSt)+1;

  struct Graph* graph=createGraph((numAvn*numSt)*2+2);

  /*Create all edges of the graph*/
  addSuperMarket(numSMark, t, numAvn, graph);
  addCitzen(numCitzen, s, numAvn, graph);
  connectNeighbors(graph, numAvn, numSt);

  for(i=0;i<graph->V;i++){
    deleteEdge(graph, i, 0);
  }

  /*Print the max flow aka the number of citizens that are able to go to a
  super-market*/
  printf("%d\n",edmondsKarp(graph, s, t, numCitzen));

  /*Free array of adjacency lists*/
  for(i=0;i<graph->V;i++){
    freeList(graph->array[i]);
  }

  /*Free th graph*/
  free(graph->parent);
  free(graph->visited);
  free(graph->array);
  free(graph);

  return 0;
}
