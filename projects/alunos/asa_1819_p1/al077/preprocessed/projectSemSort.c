#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct Vector
{
  int *vector;
  int elems;
  int size;
} Vector;
typedef struct Graph
{
  int vertices;
  Vector *adj;
} Graph;
typedef struct subNetworksVector
{
  Vector *vector;
  int elems;
  int size;
  int biggestSubNetwork;
} subNetworksVector;
void adjDFS(Graph *g, bool goal);
void adjAux(Graph *g, int u, int *time, bool *visited, int *discovery, int *low, int *parent, bool goal);
void addConnectionToGraph(Graph *g, int v, int u);
void graphInit(Graph *g, int vertices);
void vectorInit(Vector *v, int defSize);
void vectorPushback(Vector *v, int element);
void vectorFree(Vector *v);
void subNetworksInit(subNetworksVector *v, int initSize);
void addSubNetwork(subNetworksVector *v, int initSize);
void freeSubNetwork(subNetworksVector *v);
void freeGraph(Graph *g);
int subNetworksCount = 0;
int max = 0;
subNetworksVector *subNetworks;
Vector subNetworkIds;
int crucialPointCounter = 0;
bool *crucialPoints;
int main()
{
  int routers;
  int connections;
  if (2 < 0)
  {
    perror("error on scanf\n");
  }
  else
  {
    routers = new_sym_var(sizeof(int) * 8);
    connections = new_sym_var(sizeof(int) * 8);
    
  }

  Graph *graph = (Graph *) malloc(sizeof(struct Graph));
  graphInit(graph, routers);
  subNetworks = (subNetworksVector *) malloc(sizeof(struct subNetworksVector));
  subNetworksInit(subNetworks, 16);
  vectorInit(&subNetworkIds, 16);
  int aux1;
  int aux2;
  int i;
  for (i = 0; i < connections; i++)
  {
    if (2 < 0)
    {
      perror("error on scanf\n");
    }
    else
    {
      aux1 = new_sym_var(sizeof(int) * 8);
      aux2 = new_sym_var(sizeof(int) * 8);
      
    }

    addConnectionToGraph(graph, aux1 - 1, aux2 - 1);
  }

  crucialPoints = (bool *) malloc((sizeof(bool)) * routers);
  adjDFS(graph, false);
  printf("%d\n", subNetworksCount);
  for (i = subNetworksCount - 1; i > 0; i--)
    printf("%d ", subNetworkIds.vector[i] + 1);

  printf("%d\n", subNetworkIds.vector[0] + 1);
  printf("%d\n", crucialPointCounter);
  freeSubNetwork(subNetworks);
  subNetworksCount = 0;
  subNetworks = (subNetworksVector *) malloc(sizeof(struct subNetworksVector));
  subNetworksInit(subNetworks, 16);
  adjDFS(graph, true);
  printf("%d\n", subNetworks->biggestSubNetwork);
  free(crucialPoints);
  freeSubNetwork(subNetworks);
  freeGraph(graph);
  vectorFree(&subNetworkIds);
  return 0;
}

void adjDFS(Graph *g, bool goal)
{
  int routers = g->vertices;
  bool *visited = (bool *) malloc((sizeof(bool)) * routers);
  int *discovery = (int *) malloc((sizeof(int)) * routers);
  int *low = (int *) malloc((sizeof(int)) * routers);
  int *parent = (int *) malloc((sizeof(int)) * routers);
  int *time = (int *) malloc(sizeof(int));
  *time = 0;
  int i;
  for (i = 0; i < routers; i++)
  {
    visited[i] = false;
    parent[i] = -1;
    if (!goal)
    {
      crucialPoints[i] = false;
    }
    else
    {
      
    }

  }

  for (i = routers - 1; i >= 0; i--)
  {
    if ((!visited[i]) && (!crucialPoints[i]))
    {
      addSubNetwork(subNetworks, 16);
      adjAux(g, i, time, visited, discovery, low, parent, goal);
      vectorPushback(&subNetworkIds, max);
      max = 0;
      if (goal && (subNetworks->vector[subNetworksCount].elems > subNetworks->biggestSubNetwork))
      {
        subNetworks->biggestSubNetwork = subNetworks->vector[subNetworksCount].elems;
      }
      else
      {
        
      }

      subNetworksCount++;
    }
    else
    {
      
    }

  }

  free(visited);
  free(discovery);
  free(low);
  free(parent);
  free(time);
}

void adjAux(Graph *g, int u, int *time, bool *visited, int *discovery, int *low, int *parent, bool goal)
{
  int children = 0;
  visited[u] = true;
  discovery[u] = (low[u] = ++(*time));
  vectorPushback(&subNetworks->vector[subNetworksCount], u);
  if (u > max)
  {
    max = u;
  }
  else
  {
    
  }

  int i;
  for (i = 0; i < g->adj[u].elems; i++)
  {
    int v = g->adj[u].vector[i];
    if ((goal && (!crucialPoints[v])) || (!goal))
    {
      if (!visited[v])
      {
        children++;
        parent[v] = u;
        adjAux(g, v, time, visited, discovery, low, parent, goal);
        low[u] = (low[u] < low[v]) ? (low[u]) : (low[v]);
        if ((!goal) && ((((children > 1) && (parent[u] == (-1))) || ((low[v] >= discovery[u]) && (parent[u] != (-1)))) && (!crucialPoints[u])))
        {
          crucialPoints[u] = true;
          crucialPointCounter++;
        }
        else
        {
          
        }

      }
      else
      {
        if (v != parent[u])
        {
          low[u] = (low[u] < discovery[v]) ? (low[u]) : (discovery[v]);
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

  }

}

void addConnectionToGraph(Graph *g, int v, int u)
{
  vectorPushback(&g->adj[v], u);
  vectorPushback(&g->adj[u], v);
}

void graphInit(Graph *g, int vertices)
{
  g->vertices = vertices;
  g->adj = (Vector *) malloc((sizeof(struct Vector)) * vertices);
  int i;
  for (i = 0; i < vertices; i++)
    vectorInit(&g->adj[i], 16);

}

void vectorInit(Vector *v, int initSize)
{
  v->vector = (int *) calloc(initSize, sizeof(int));
  v->elems = 0;
  v->size = initSize;
}

void vectorPushback(Vector *v, int element)
{
  if (v->elems == v->size)
  {
    v->size *= 2;
    v->vector = realloc(v->vector, (sizeof(int)) * v->size);
  }
  else
  {
    
  }

  v->vector[v->elems++] = element;
}

void vectorFree(Vector *v)
{
  free(v->vector);
  v->vector = 0;
  v->size = (v->elems = 0);
}

void subNetworksInit(subNetworksVector *v, int initSize)
{
  v->vector = (Vector *) malloc((sizeof(struct subNetworksVector)) * initSize);
  int i;
  for (i = 0; i < initSize; i++)
  {
    vectorInit(&v->vector[i], initSize);
  }

  v->elems = 0;
  v->size = initSize;
  v->biggestSubNetwork = 0;
}

void addSubNetwork(subNetworksVector *v, int initSize)
{
  if (v->elems == v->size)
  {
    v->size *= 2;
    v->vector = realloc(v->vector, (sizeof(struct Vector)) * v->size);
    int i;
    for (i = v->elems; i < v->size; i++)
    {
      vectorInit(&v->vector[i], 16);
    }

  }
  else
  {
    
  }

  v->elems++;
}

void freeSubNetwork(subNetworksVector *v)
{
  int i = 0;
  for (; i < v->size; i++)
  {
    vectorFree(&v->vector[i]);
  }

  free(v->vector);
  free(v);
}

void freeGraph(Graph *g)
{
  int i = 0;
  for (; i < g->vertices; i++)
  {
    vectorFree(&g->adj[i]);
  }

  free(g->adj);
  free(g);
}

