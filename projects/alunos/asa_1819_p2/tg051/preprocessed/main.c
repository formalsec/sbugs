#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


typedef struct Edge
{
  struct Edge *res;
  int dest;
  int ccap;
  int cap;
} edge;
typedef struct Node
{
  edge *edge;
  struct Node *next;
} node;
typedef struct List
{
  node *head;
} list;
typedef struct AdjList
{
  int n;
  list *lists;
} adjList;
typedef struct Graph
{
  int nProviders;
  int nStations;
  int nVertices;
  int nEdges;
  adjList *adjList;
} graph;
typedef struct Dfsdata
{
  adjList *adjList;
  int vertex;
  int flow;
  int *visited;
  int time;
} dfsData;
typedef struct Pair
{
  int o;
  int d;
} pair;
edge *createEdge(int dest, int cap)
{
  edge *newEdge = (edge *) malloc(sizeof(edge));
  newEdge->dest = dest;
  newEdge->cap = cap;
  newEdge->ccap = cap;
  return newEdge;
}

node *createNode(int dest, int cap)
{
  node *newNode = (node *) malloc(sizeof(node));
  edge *newEdge = createEdge(dest, cap);
  newNode->edge = newEdge;
  newNode->next = 0;
  return newNode;
}

adjList *createAdjList(int n)
{
  int i;
  adjList *newAdjList = (adjList *) malloc(sizeof(adjList));
  newAdjList->n = n;
  newAdjList->lists = (list *) malloc((sizeof(list)) * n);
  for (i = 0; i < n; i++)
  {
    newAdjList->lists[i].head = 0;
  }

  return newAdjList;
}

edge *addEdge(adjList *adjList, int origin, int dest, int cap)
{
  node *newNode = createNode(dest, cap);
  newNode->next = adjList->lists[origin].head;
  adjList->lists[origin].head = newNode;
  return newNode->edge;
}

void printAdjList(adjList *adjList)
{
  int v;
  for (v = 0; v < adjList->n; v++)
  {
    node *nodep = adjList->lists[v].head;
    while (nodep)
    {
      printf("  > [edge: (%d->%d) | capacity: %d/%d c: %d]\n", v, nodep->edge->dest, nodep->edge->res->ccap, nodep->edge->cap, nodep->edge->ccap);
      nodep = nodep->next;
    }

    printf("\n");
  }

}

graph *createGraph(int f, int e, int t)
{
  graph *newGraph = (graph *) malloc(sizeof(graph));
  newGraph->nProviders = f;
  newGraph->nStations = e;
  newGraph->nVertices = (f + (2 * e)) + 2;
  newGraph->nEdges = (t + f) + e;
  return newGraph;
}

graph *parseInput()
{
  int f;
  int e;
  int t;
  int i;
  int k;
  int o;
  int d;
  int el;
  graph *graph;
  adjList *adjList;
  edge *e1;
  edge *e2;
  f = new_sym_var(sizeof(int) * 8);
  e = new_sym_var(sizeof(int) * 8);
  t = new_sym_var(sizeof(int) * 8);
  graph = createGraph(f, e, t);
  f++;
  el = f + e;
  adjList = createAdjList(graph->nVertices);
  for (i = 2; i <= f; i++)
  {
    k = new_sym_var(sizeof(int) * 8);
    e1 = addEdge(adjList, 0, i, k);
    e2 = addEdge(adjList, i, 0, 0);
    e1->res = e2;
    e2->res = e1;
  }

  for (i = ++f; i <= el; i++)
  {
    k = new_sym_var(sizeof(int) * 8);
    e1 = addEdge(adjList, i, i + e, k);
    e2 = addEdge(adjList, i + e, i, 0);
    e1->res = e2;
    e2->res = e1;
  }

  for (i = 0; i < t; i++)
  {
    o = new_sym_var(sizeof(int) * 8);
    d = new_sym_var(sizeof(int) * 8);
    k = new_sym_var(sizeof(int) * 8);
    if (o >= f)
    {
      e1 = addEdge(adjList, o + e, d, k);
      e2 = addEdge(adjList, d, o + e, 0);
      e1->res = e2;
      e2->res = e1;
    }
    else
    {
      e1 = addEdge(adjList, o, d, k);
      e2 = addEdge(adjList, d, o, 0);
      e1->res = e2;
      e2->res = e1;
    }

  }

  graph->adjList = adjList;
  return graph;
}

void minCutDFS(adjList *list, int source, int *visited)
{
  if (source == 0)
  {
    return;
  }
  else
  {
    
  }

  visited[source] = 1;
  node *nodep = list->lists[source].head;
  while (nodep)
  {
    if (nodep->edge->res->ccap && (!visited[nodep->edge->dest]))
    {
      minCutDFS(list, nodep->edge->dest, visited);
    }
    else
    {
      
    }

    nodep = nodep->next;
  }

}

int dfsFF(dfsData *data)
{
  adjList *adjList = data->adjList;
  int vertex = data->vertex;
  int flow = data->flow;
  int *visited = data->visited;
  int time = data->time;
  int dfsFlow = 0;
  node *nodep = adjList->lists[vertex].head;
  if (vertex == 1)
  {
    return flow;
  }
  else
  {
    
  }

  visited[vertex] = time;
  while (nodep)
  {
    edge *edgep = nodep->edge;
    edge *resEdgep = edgep->res;
    if ((visited[edgep->dest] != time) && (edgep->ccap > 0))
    {
      if (edgep->ccap < flow)
      {
        data->flow = edgep->ccap;
      }
      else
      {
        
      }

      data->vertex = edgep->dest;
      dfsFlow = dfsFF(data);
      if (dfsFlow > 0)
      {
        edgep->ccap -= dfsFlow;
        resEdgep->ccap += dfsFlow;
        return dfsFlow;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    nodep = nodep->next;
  }

  return 0;
}

int *fordFulkerson(graph *graph)
{
  dfsData *data = (dfsData *) malloc(sizeof(dfsData));
  int flow = 0;
  int maxFlow = 0;
  int time = 1;
  int visited[graph->nVertices];
  int *minCut = (int *) calloc(graph->nVertices, sizeof(int));
  data->adjList = graph->adjList;
  data->visited = visited;
  do
  {
    data->vertex = 0;
    data->flow = 32767;
    data->time = time;
    flow = dfsFF(data);
    maxFlow += flow;
    time++;
  }
  while (flow != 0);
  minCutDFS(graph->adjList, 1, minCut);
  printf("%d\n", maxFlow);
  return minCut;
}

int cmpint(const void *a, const void *b)
{
  return (*((int *) a)) - (*((int *) b));
}

void pairInsertSort(pair *edges, int n)
{
  int i;
  int j;
  pair key;
  for (i = 1; i < n; i++)
  {
    key = edges[i];
    j = i - 1;
    while ((j >= 0) && (edges[j].d > key.d))
    {
      edges[j + 1] = edges[j];
      j = j - 1;
    }

    edges[j + 1] = key;
  }

  for (i = 1; i < n; i++)
  {
    key = edges[i];
    j = i - 1;
    while ((j >= 0) && (edges[j].o > key.o))
    {
      edges[j + 1] = edges[j];
      j = j - 1;
    }

    edges[j + 1] = key;
  }

}

int main()
{
  int i;
  int stationStart;
  int si = 0;
  int se = 0;
  int *stationBN;
  pair *edgeBN;
  adjList *adjList;
  graph *graph;
  int *minCut;
  graph = parseInput();
  minCut = fordFulkerson(graph);
  adjList = graph->adjList;
  stationStart = (graph->nProviders + graph->nStations) + 1;
  stationBN = (int *) calloc(graph->nStations, sizeof(int));
  edgeBN = (pair *) calloc(graph->nEdges, sizeof(pair));
  for (i = 1; i < adjList->n; i++)
  {
    node *nodep = adjList->lists[i].head;
    while (nodep)
    {
      edge *edge = nodep->edge;
      if ((minCut[i] != minCut[edge->dest]) && edge->cap)
      {
        if (edge->dest > stationStart)
        {
          stationBN[si++] = edge->dest - graph->nStations;
        }
        else
        {
          edgeBN[se].o = i;
          edgeBN[se++].d = edge->dest;
        }

      }
      else
      {
        
      }

      nodep = nodep->next;
    }

  }

  qsort(stationBN, si, sizeof(int), cmpint);
  pairInsertSort(edgeBN, se);
  for (i = 0; i < si; i++)
  {
    if (i)
    {
      printf(" ");
    }
    else
    {
      
    }

    printf("%d", stationBN[i]);
  }

  printf("\n");
  for (i = 0; i < se; i++)
  {
    if (edgeBN[i].o > stationStart)
    {
      printf("%d ", edgeBN[i].o - graph->nStations);
    }
    else
    {
      printf("%d ", edgeBN[i].o);
    }

    printf("%d\n", edgeBN[i].d);
  }

  return 0;
}

