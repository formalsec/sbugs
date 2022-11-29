#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define S 0 /*origem*/
#define T 1 /*destino*/
#define FALSE 0
#define TRUE 1
#define MIN(a,b) (((a)<(b))?(a):(b))
#define REV(i) ((i%2)?(i-1):(i+1))

/*
*******************************************************************************
*                             QUEUE
*******************************************************************************
*/

struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*) can_fail_malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*) can_fail_malloc(queue->capacity * sizeof(int));
    return queue;
}

int isEmpty(struct Queue* queue) {
  return (queue->size == 0);
}

int isFull(struct Queue* queue) {
  return (queue->size == queue->capacity);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)%queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

int valueInQueue(struct Queue* queue, int val) {
  int i;
  for (i = queue->front; i < (queue->front + queue->size); i++)
    if (queue->array[i] == val)
      return TRUE;
  return FALSE;
}

void freeQueue(struct Queue* queue) {
  free(queue->array);
  free(queue);
}

/*
*******************************************************************************
*                             GRAPH
*******************************************************************************
*/

typedef struct {
  /*destination vertex*/
  int to;
  /*capacity*/
  int cap;
  /*flow*/
  int flow;
  /*next edge*/
  int next;
}edge;

void addEdge(edge* edges, int* first, int from, int to, int cap, int* edgeNum) {
  edges[*edgeNum].to = to;
  edges[*edgeNum].cap = cap;
  edges[*edgeNum].flow = 0;
  edges[*edgeNum].next = first[from];
  first[from] = (*edgeNum)++;

  edges[*edgeNum].to = from;
  edges[*edgeNum].cap = 0;
  edges[*edgeNum].flow = 0;
  edges[*edgeNum].next = first[to];
  first[to] = (*edgeNum)++;
}

void freeGraph(edge* edges, int* first) {
  free(edges);
  free(first);
}

void readSupplierProduction(edge* edges, int* first, int* edgeNum, int suppliers) {
  int i;
  for (i = 2; i < suppliers+2; i++) {
    int production;
    if (scanf("%d", &production) != 1) exit(-1);
    addEdge(edges, first, 0, i, production, edgeNum);
  }
}

void readStationsCapacity(edge* edges, int* first, int* edgeNum, int suppliers, int stations) {
  int stationIndex = 2 + suppliers;
  int stationDestIndex = stationIndex + stations;
  int i;
  for (i = stationIndex; i < stationIndex + stations; i++, stationDestIndex++) {
    int capacity;
    if (scanf("%d", &capacity) != 1) exit(-1);
    addEdge(edges, first, i, stationDestIndex, capacity, edgeNum);
  }
}

void readConnections(edge* edges, int* first, int* edgeNum, int suppliers, int stations, int connections) {
  int i;
  for (i = 0; i < connections; i++) {
    int orig, dest, capacity;
    if (scanf("%d %d %d", &orig, &dest, &capacity) != 3) exit(-1);
    if (orig >= (2 + suppliers))
    orig += stations;
    addEdge(edges, first, orig, dest, capacity, edgeNum);
  }
}

/*
*******************************************************************************
*                                 PUSH-RELABEL
*******************************************************************************
*/

void push(edge* edges, int u, int index, int* excess) {
  int diff = MIN(excess[u], edges[index].cap - edges[index].flow);
  edges[index].flow += diff;
  edges[REV(index)].flow = -edges[index].flow;
  excess[u] -= diff;
  excess[edges[index].to] += diff;
}

void relabel(edge* edges, int* first, int u, int* height) {
  int i, min = INT_MAX;
  for (i = first[u]; i != -1; i = edges[i].next)
    if ((edges[i].cap - edges[i].flow > 0)) {
      min = MIN(min, height[edges[i].to]);
      height[u] = 1 + min;
    }
}

void dfs_reverse(edge* edges, int* first, int u, int* visited) {
  int i;
  visited[u] = TRUE;
  for (i = first[u]; i != -1; i = edges[i].next)
    if (!visited[edges[i].to] && (edges[REV(i)].cap - edges[REV(i)].flow > 0))
      dfs_reverse(edges, first, edges[i].to, visited);
}

int pushRelabel(edge* edges, int* first, int* minCutEdges, int size, int realConnections) {
  int *excess, *height, i;
  struct Queue* q = createQueue(size-2);

  excess = (int*) can_fail_malloc(size*sizeof(int));
  height = (int*) can_fail_malloc(size*sizeof(int));
  memset(excess, 0, size*sizeof(int));
  memset(height, 0, size*sizeof(int));
  height[S] = size;

  for (i = first[S]; i != -1; i = edges[i].next) {
    edges[i].flow = edges[i].cap;
    edges[REV(i)].flow = -edges[i].cap;
    excess[edges[i].to] = edges[i].cap;
    excess[S] -= edges[i].cap;
    enqueue(q, edges[i].to);
  }

  while (!isEmpty(q)) {
    int u = dequeue(q);
    while (excess[u] > 0) {
      for (i = first[u]; i != -1 && excess[u] > 0 ; i = edges[i].next)
        if ((edges[i].cap - edges[i].flow > 0) && (height[u] == height[edges[i].to] + 1)) {
          push(edges, u, i, excess);
          if (edges[i].to != T && edges[i].to != S && !valueInQueue(q, edges[i].to)) {
            enqueue(q, edges[i].to);
          }
        }
      if (excess[u] > 0)
        relabel(edges, first, u, height);
    }
  }


  int* visited = (int*) can_fail_malloc(size*sizeof(int));
  int* exists = (int*) can_fail_malloc(size*sizeof(int));
  memset(visited, FALSE, size*sizeof(int));
  dfs_reverse(edges, first, T, visited);

  int orig;
  int edgesIndex = 0;
  for (orig = 0; orig < size; orig++)
    if (!visited[orig]) {
      int originCount = 0;
      memset(exists, FALSE, size*sizeof(int));
      for (i = first[orig]; i != -1; i = edges[i].next)
        if (visited[edges[i].to] && (edges[i].flow > 0) && (edges[i].cap > 0)) {
          originCount++;
          exists[edges[i].to] = TRUE;
        }
      for (i = 0; i < size && originCount > 0; i++)
        if (exists[i]) {
          originCount--;
          minCutEdges[edgesIndex++] = orig;
          minCutEdges[edgesIndex++] = i;
        }
    }

  int maxflow = excess[T];

  free(exists);
  free(visited);
  freeQueue(q);
  free(height);
  free(excess);
  return maxflow;
}

/*
*******************************************************************************
*                                 MAIN
*******************************************************************************
*/
int main() {
  int suppliers, stations, connections;
  if (scanf("%d %d %d", &suppliers, &stations, &connections) != 3)
    exit(-1);
  if (suppliers <= 0 || stations < 0 || connections < 0) {
    printf("Wrong input: Numbers must be positive\n");
    exit(-1);
  }

  int size = 2 + suppliers + 2*stations;
  int realConnections = 2*(connections + suppliers + stations);

  int edgeNum = 0;
  int* first = (int*) can_fail_malloc(size*sizeof(size));
  int i;
  for (i = 0; i < size; ++i) {
    first[i] = -1;
  }
  edge* edges = (edge*) can_fail_malloc(realConnections*sizeof(edge));
  readSupplierProduction(edges, first, &edgeNum, suppliers);

  readStationsCapacity(edges, first, &edgeNum, suppliers, stations);

  readConnections(edges, first, &edgeNum, suppliers, stations, connections);

  int* minCutEdges = (int*) can_fail_malloc(realConnections*sizeof(int));
  memset(minCutEdges, 0, realConnections*sizeof(int));
  printf("%d\n", pushRelabel(edges, first, minCutEdges, size, realConnections));

  int temp = 0;
  for (i = 1; i < realConnections; i += 2) {
    if ((minCutEdges[i-1] >= (2 + suppliers)) && (minCutEdges[i-1] + stations == minCutEdges[i])) {
      if (temp == 0) {
        printf("%d", minCutEdges[i-1]);
        temp = 1;
      }
      else printf(" %d", minCutEdges[i-1]);
      minCutEdges[i] = -1;
      minCutEdges[i-1] = -1;
    }
  }
  printf("\n");

  for (i = 1; i < realConnections; i += 2) {
    if (minCutEdges[i] != -1 && minCutEdges[i-1] != S) {
      int orig = minCutEdges[i-1];
      int dest = minCutEdges[i];
      if (orig >= (2 + suppliers + stations))
        orig -= stations;
      if (dest >= (2 + suppliers + stations))
        dest -= stations;
      printf("%d %d\n", orig, dest);
    }
  }

  free(minCutEdges);
  freeGraph(edges, first);
  return 0;
}
