#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct queue
{
  int visitedVertex;
  struct queue *next;
} *Queue;
typedef struct edge
{
  int indexVertexList;
  int flow;
  int capacity;
  struct edge *next;
} *Edge;
typedef struct vertex
{
  Edge edgesHead;
  int type;
} *Vertex;
typedef struct graph
{
  Vertex vertexList;
  int maxFlow;
  int marketsNumber;
  int clientsNumber;
  int vertexNumber;
  int streets;
  int avenues;
  int size;
  int sourceIndex;
  int sinkIndex;
} *Graph;
void edgeInitializer(Graph g, int from, int to, int capacity, int flow)
{
  Edge aux;
  aux = g->vertexList[from].edgesHead;
  g->vertexList[from].edgesHead = (struct edge *) malloc(sizeof(struct edge));
  g->vertexList[from].edgesHead->next = aux;
  g->vertexList[from].edgesHead->indexVertexList = to;
  g->vertexList[from].edgesHead->capacity = capacity;
  g->vertexList[from].edgesHead->flow = flow;
}

void edgesInitializer(Graph g, int from, int to)
{
  edgeInitializer(g, from, to, 1, 0);
  edgeInitializer(g, to, from, 0, 0);
}

void parseInput(Graph g)
{
  int i;
  int N;
  int M;
  int S;
  int C;
  int offset;
  int up;
  int down;
  int left;
  int right;
  M = new_sym_var(sizeof(int) * 8);
  N = new_sym_var(sizeof(int) * 8);
  g->size = ((2 * M) * N) + 2;
  g->vertexList = (struct vertex *) malloc(g->size * (sizeof(struct vertex)));
  g->streets = N;
  g->avenues = M;
  g->maxFlow = 0;
  g->vertexNumber = N * M;
  g->sourceIndex = 2 * g->vertexNumber;
  g->sinkIndex = (2 * g->vertexNumber) + 1;
  g->marketsNumber = 0;
  g->clientsNumber = 0;
  for (i = 0; i < g->size; i++)
  {
    g->vertexList[i].edgesHead = 0;
    g->vertexList[i].type = 0;
  }

  S = new_sym_var(sizeof(int) * 8);
  C = new_sym_var(sizeof(int) * 8);
  for (i = 0; i < S; i++)
  {
    M = new_sym_var(sizeof(int) * 8);
    N = new_sym_var(sizeof(int) * 8);
    offset = ((N - 1) * g->avenues) + (M - 1);
    if (g->vertexList[offset].type == 0)
    {
      g->marketsNumber += 1;
    }
    else
    {
      
    }

    g->vertexList[offset].type = 2;
    g->vertexList[offset + g->vertexNumber].type = 2;
  }

  for (i = 0; i < C; i++)
  {
    M = new_sym_var(sizeof(int) * 8);
    N = new_sym_var(sizeof(int) * 8);
    offset = ((N - 1) * g->avenues) + (M - 1);
    if ((g->vertexList[offset].type != 3) && (g->vertexList[offset].type != 1))
    {
      g->clientsNumber += 1;
    }
    else
    {
      
    }

    if ((g->vertexList[offset].type == 2) || (g->vertexList[offset].type == 3))
    {
      g->vertexList[offset].type = 3;
      g->vertexList[offset + g->vertexNumber].type = 3;
    }
    else
    {
      g->vertexList[offset].type = 1;
      g->vertexList[offset + g->vertexNumber].type = 1;
    }

  }

  for (i = 0; i < g->vertexNumber; i++)
  {
    edgesInitializer(g, i, i + g->vertexNumber);
    if ((g->vertexList[i].type == 1) || (g->vertexList[i].type == 3))
    {
      edgesInitializer(g, g->sourceIndex, i);
    }
    else
    {
      
    }

    if ((g->vertexList[i].type == 2) || (g->vertexList[i].type == 3))
    {
      edgesInitializer(g, i + g->vertexNumber, g->sinkIndex);
    }
    else
    {
      
    }

    if ((g->vertexList[i].type == 0) || (g->vertexList[i].type == 1))
    {
      up = i - g->avenues;
      down = i + g->avenues;
      left = i - 1;
      right = i + 1;
      if (up >= 0)
      {
        edgesInitializer(g, i + g->vertexNumber, up);
      }
      else
      {
        
      }

      if (down < g->vertexNumber)
      {
        edgesInitializer(g, i + g->vertexNumber, down);
      }
      else
      {
        
      }

      if (((left / g->avenues) == (i / g->avenues)) && (left >= 0))
      {
        edgesInitializer(g, i + g->vertexNumber, left);
      }
      else
      {
        
      }

      if (((right / g->avenues) == (i / g->avenues)) && (right < g->vertexNumber))
      {
        edgesInitializer(g, i + g->vertexNumber, right);
      }
      else
      {
        
      }

    }
    else
    {
      
    }

  }

}

int bfs(Graph g, int *parentList, int *patchCapacity)
{
  int u;
  int v;
  Edge auxEdge;
  Queue queueRoot = (struct queue *) malloc(sizeof(struct queue));
  Queue queueTail;
  Queue queueAux;
  memset(parentList, -1, g->size * (sizeof(int)));
  memset(patchCapacity, 0, g->size * (sizeof(int)));
  parentList[g->sourceIndex] = g->sourceIndex;
  patchCapacity[g->sourceIndex] = 999;
  queueRoot->visitedVertex = g->sourceIndex;
  queueRoot->next = 0;
  queueTail = queueRoot;
  while (queueRoot != 0)
  {
    u = queueRoot->visitedVertex;
    queueAux = queueRoot;
    queueRoot = queueRoot->next;
    free(queueAux);
    if (queueRoot == 0)
    {
      queueTail = queueRoot;
    }
    else
    {
      
    }

    auxEdge = g->vertexList[u].edgesHead;
    while (auxEdge != 0)
    {
      v = auxEdge->indexVertexList;
      if ((parentList[v] == (-1)) && ((auxEdge->capacity - auxEdge->flow) > 0))
      {
        parentList[v] = u;
        patchCapacity[v] = (patchCapacity[u] < (auxEdge->capacity - auxEdge->flow)) ? (patchCapacity[u]) : (auxEdge->capacity - auxEdge->flow);
        if (queueRoot == 0)
        {
          queueRoot = (struct queue *) malloc(sizeof(struct queue));
          queueRoot->visitedVertex = v;
          queueRoot->next = 0;
          queueTail = queueRoot;
        }
        else
        {
          queueTail->next = (struct queue *) malloc(sizeof(struct queue));
          queueTail = queueTail->next;
          queueTail->visitedVertex = v;
          queueTail->next = 0;
        }

        if (v == g->sinkIndex)
        {
          while (queueRoot != 0)
          {
            queueAux = queueRoot;
            queueRoot = queueRoot->next;
            free(queueAux);
          }

          return patchCapacity[v];
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      auxEdge = auxEdge->next;
    }

  }

  return 0;
}

void edmondsKarp(Graph g)
{
  int currentVertex;
  int previousVertex;
  int path;
  int parentList[g->size];
  int patchCapacity[g->size];
  Edge auxEdge;
  path = bfs(g, parentList, patchCapacity);
  while (path != 0)
  {
    g->maxFlow = g->maxFlow + path;
    if (g->maxFlow == ((g->marketsNumber < g->clientsNumber) ? (g->marketsNumber) : (g->clientsNumber)))
    {
      break;
    }
    else
    {
      
    }

    currentVertex = g->sinkIndex;
    while (currentVertex != g->sourceIndex)
    {
      previousVertex = parentList[currentVertex];
      auxEdge = g->vertexList[previousVertex].edgesHead;
      while (auxEdge != 0)
      {
        if (auxEdge->indexVertexList == currentVertex)
        {
          auxEdge->flow = auxEdge->flow + 1;
          auxEdge = g->vertexList[currentVertex].edgesHead;
          while (auxEdge != 0)
          {
            if (auxEdge->indexVertexList == previousVertex)
            {
              auxEdge->flow = auxEdge->flow - 1;
              break;
            }
            else
            {
              
            }

            auxEdge = auxEdge->next;
          }

          break;
        }
        else
        {
          
        }

        auxEdge = auxEdge->next;
      }

      currentVertex = previousVertex;
    }

    path = bfs(g, parentList, patchCapacity);
  }

}

void freeGraph(Graph g)
{
  int i;
  Edge auxEdge;
  Edge terminateEdge;
  for (i = 0; i < g->size; i++)
  {
    auxEdge = g->vertexList[i].edgesHead;
    while (auxEdge != 0)
    {
      terminateEdge = auxEdge;
      auxEdge = auxEdge->next;
      free(terminateEdge);
    }

    free(&g->vertexList[i]);
  }

  free(g->vertexList);
  free(g);
}

int main(void)
{
  Graph g = malloc(sizeof(struct graph));
  parseInput(g);
  edmondsKarp(g);
  printf("%d\n", g->maxFlow);
  free(g);
  return 0;
}

