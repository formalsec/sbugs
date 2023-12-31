#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int numSuppliers;
int numStations;
int numConnections;
typedef struct edge
{
  int source;
  int destination;
  int flowForward;
  int capacityForward;
  int flowBackward;
  int capacityBackward;
  struct edge *nextSrc;
  struct edge *nextDst;
} *edge_t;
typedef struct vertex
{
  int height;
  int excess;
  bool visited;
  edge_t srcEdgeList;
  edge_t dstEdgeList;
  struct vertex *next;
} *vertex_t;
vertex_t *graph = 0;
vertex_t verticesQueueFront = 0;
vertex_t verticesQueueRear = 0;
void *mallocAndVerify(size_t size)
{
  void *x = malloc(size);
  if (x == 0)
  {
    printf("Error in malloc, exiting...\n");
    exit(1);
  }
  else
  {
    
  }

  return x;
}

void scanfAndVerify(int *number)
{
  int error = 1;
  for (int number_index = 0; number_index < 10; number_index++)
  {
    number[number_index] = new_sym_var(sizeof(int) * 8);
  }

  if (error < 0)
  {
    printf("Error in scanf, exiting...\n");
    exit(1);
  }
  else
  {
    
  }

}

void pushQueue(vertex_t v)
{
  if (verticesQueueRear == 0)
  {
    verticesQueueFront = (verticesQueueRear = v);
  }
  else
  {
    verticesQueueRear->next = v;
    verticesQueueRear = v;
  }

}

void popQueue()
{
  if (verticesQueueFront != 0)
  {
    vertex_t x = verticesQueueFront;
    verticesQueueFront = verticesQueueFront->next;
    x->next = 0;
    if (verticesQueueFront == 0)
    {
      verticesQueueRear = 0;
    }
    else
    {
      
    }

  }
  else
  {
    
  }

}

vertex_t newVertex()
{
  vertex_t vertex = mallocAndVerify(sizeof(struct vertex));
  vertex->height = 0;
  vertex->excess = 0;
  vertex->srcEdgeList = 0;
  vertex->dstEdgeList = 0;
  vertex->next = 0;
  vertex->visited = false;
  return vertex;
}

edge_t newEdge(int src, int dest, int flowForward, int capForward, int flowBackward, int capBackward)
{
  edge_t x = mallocAndVerify(sizeof(struct edge));
  x->source = src;
  x->destination = dest;
  x->flowForward = flowForward;
  x->capacityForward = capForward;
  x->flowBackward = flowBackward;
  x->capacityBackward = capBackward;
  x->nextSrc = 0;
  x->nextDst = 0;
  return x;
}

void addToSrcList(edge_t *head, int src, int dest, int flowForward, int capForward, int flowBackward, int capBackward)
{
  edge_t x = newEdge(src, dest, flowForward, capForward, flowBackward, capBackward);
  int d = x->destination;
  if ((*head) == 0)
  {
    x->nextSrc = *head;
    *head = x;
    (*head)->nextDst = 0;
  }
  else
  {
    if (d < (*head)->destination)
    {
      x->nextSrc = *head;
      *head = x;
    }
    else
    {
      edge_t tmp = *head;
      while ((tmp->nextSrc != 0) && (tmp->nextSrc->destination < x->destination))
        tmp = tmp->nextSrc;

      x->nextSrc = tmp->nextSrc;
      tmp->nextSrc = x;
    }

  }

}

void addToDstList(edge_t *head, edge_t x, int destination)
{
  edge_t tmp;
  for (tmp = x; tmp != 0; tmp = tmp->nextSrc)
  {
    if (tmp->destination == destination)
    {
      tmp->nextDst = *head;
      *head = tmp;
      break;
    }
    else
    {
      
    }

  }

}

void Preflow()
{
  int i = 0;
  int j = 0;
  int srcTmp = 0;
  int destTmp = 0;
  int pathCapTmp = 0;
  int capacityTmp = 0;
  int total = 0;
  scanfAndVerify(&numSuppliers);
  scanfAndVerify(&numStations);
  scanfAndVerify(&numConnections);
  total = (numSuppliers + (numStations * 2)) + 2;
  graph = mallocAndVerify((sizeof(vertex_t)) * total);
  graph[0] = newVertex();
  graph[0]->height = total;
  graph[1] = newVertex();
  for (i = 2; i < (numSuppliers + 2); i++)
  {
    graph[i] = newVertex();
    scanfAndVerify(&capacityTmp);
    graph[i]->excess = capacityTmp;
    graph[0]->excess -= capacityTmp;
    addToSrcList(&graph[0]->srcEdgeList, 0, i, capacityTmp, capacityTmp, -capacityTmp, 0);
    addToDstList(&graph[i]->dstEdgeList, graph[0]->srcEdgeList, i);
    pushQueue(graph[i]);
  }

  for (j = i; j < ((numSuppliers + numStations) + 2); j++)
  {
    graph[j] = newVertex();
    graph[j + numStations] = newVertex();
    scanfAndVerify(&capacityTmp);
    addToSrcList(&graph[j]->srcEdgeList, j, j + numStations, 0, capacityTmp, 0, 0);
    addToDstList(&graph[j + numStations]->dstEdgeList, graph[j]->srcEdgeList, j + numStations);
  }

  for (i = 1; i <= numConnections; i++)
  {
    scanfAndVerify(&srcTmp);
    scanfAndVerify(&destTmp);
    scanfAndVerify(&pathCapTmp);
    if (srcTmp > (numSuppliers + 1))
    {
      addToSrcList(&graph[srcTmp + numStations]->srcEdgeList, srcTmp + numStations, destTmp, 0, pathCapTmp, 0, 0);
      addToDstList(&graph[destTmp]->dstEdgeList, graph[srcTmp + numStations]->srcEdgeList, destTmp);
    }
    else
    {
      addToSrcList(&graph[srcTmp]->srcEdgeList, srcTmp, destTmp, 0, pathCapTmp, 0, 0);
      addToDstList(&graph[destTmp]->dstEdgeList, graph[srcTmp]->srcEdgeList, destTmp);
    }

  }

}

void Push(vertex_t u, vertex_t v, bool uIsSource)
{
  edge_t uv;
  int add = 0;
  int oldexcess = v->excess;
  if (uIsSource)
  {
    for (uv = u->srcEdgeList; uv != 0; uv = uv->nextSrc)
    {
      if (((v->srcEdgeList != 0) && (uv->destination == v->srcEdgeList->source)) || (uv->destination == v->dstEdgeList->destination))
      {
        add = (u->excess < (uv->capacityForward - uv->flowForward)) ? (u->excess) : (uv->capacityForward - uv->flowForward);
        uv->flowForward += add;
        uv->flowBackward = -uv->flowForward;
        break;
      }
      else
      {
        
      }

    }

  }
  else
  {
    for (uv = u->dstEdgeList; uv != 0; uv = uv->nextDst)
    {
      if (uv->source == v->srcEdgeList->source)
      {
        add = (u->excess < (uv->capacityBackward - uv->flowBackward)) ? (u->excess) : (uv->capacityBackward - uv->flowBackward);
        uv->flowBackward += add;
        uv->flowForward = -uv->flowBackward;
        break;
      }
      else
      {
        
      }

    }

  }

  u->excess -= add;
  v->excess += add;
  if (((((v->srcEdgeList != 0) && (oldexcess == 0)) && (v->srcEdgeList->source != 1)) && (v->srcEdgeList->source != 0)) || ((((v->dstEdgeList != 0) && (oldexcess == 0)) && (v->dstEdgeList->destination != 1)) && (v->dstEdgeList->destination != 0)))
  {
    pushQueue(v);
  }
  else
  {
    
  }

}

void Relabel(vertex_t u)
{
  int minHeight = -1;
  edge_t edge;
  for (edge = u->srcEdgeList; edge != 0; edge = edge->nextSrc)
  {
    if ((graph[edge->destination]->height >= u->height) && ((edge->capacityForward - edge->flowForward) > 0))
    {
      if (minHeight == (-1))
      {
        minHeight = graph[edge->destination]->height;
      }
      else
      {
        minHeight = (graph[edge->destination]->height < minHeight) ? (graph[edge->destination]->height) : (minHeight);
      }

    }
    else
    {
      
    }

  }

  for (edge = u->dstEdgeList; edge != 0; edge = edge->nextDst)
  {
    if ((graph[edge->source]->height >= u->height) && ((edge->capacityBackward - edge->flowBackward) > 0))
    {
      if (minHeight == (-1))
      {
        minHeight = graph[edge->source]->height;
      }
      else
      {
        minHeight = (graph[edge->source]->height < minHeight) ? (graph[edge->source]->height) : (minHeight);
      }

    }
    else
    {
      
    }

  }

  if (minHeight != (-1))
  {
    u->height = 1 + minHeight;
  }
  else
  {
    
  }

}

void Discharge(vertex_t u)
{
  edge_t edgeToNeighborSrc = u->srcEdgeList;
  edge_t edgeToNeighborDst = u->dstEdgeList;
  vertex_t v1 = 0;
  vertex_t v2 = 0;
  while (u->excess > 0)
  {
    if ((edgeToNeighborSrc == 0) && (edgeToNeighborDst == 0))
    {
      Relabel(u);
      edgeToNeighborSrc = u->srcEdgeList;
      edgeToNeighborDst = u->dstEdgeList;
    }
    else
    {
      if (edgeToNeighborSrc != 0)
      {
        v1 = graph[edgeToNeighborSrc->destination];
      }
      else
      {
        
      }

      if (edgeToNeighborDst != 0)
      {
        v2 = graph[edgeToNeighborDst->source];
      }
      else
      {
        
      }

      if (((edgeToNeighborSrc != 0) && ((edgeToNeighborSrc->capacityForward - edgeToNeighborSrc->flowForward) > 0)) && (u->height == (v1->height + 1)))
      {
        Push(u, v1, true);
      }
      else
      {
        if (((edgeToNeighborDst != 0) && ((edgeToNeighborDst->capacityBackward - edgeToNeighborDst->flowBackward) > 0)) && (u->height == (v2->height + 1)))
        {
          Push(u, v2, false);
        }
        else
        {
          if (edgeToNeighborDst != 0)
          {
            edgeToNeighborDst = edgeToNeighborDst->nextDst;
          }
          else
          {
            
          }

          if (edgeToNeighborSrc != 0)
          {
            edgeToNeighborSrc = edgeToNeighborSrc->nextSrc;
          }
          else
          {
            
          }

        }

      }

    }

  }

}

void DFSVisit(vertex_t u)
{
  edge_t edge;
  u->visited = true;
  for (edge = u->srcEdgeList; edge != 0; edge = edge->nextSrc)
  {
    if ((!graph[edge->destination]->visited) && ((edge->capacityBackward - edge->flowBackward) != 0))
    {
      DFSVisit(graph[edge->destination]);
    }
    else
    {
      
    }

  }

  for (edge = u->dstEdgeList; edge != 0; edge = edge->nextDst)
  {
    if ((!graph[edge->source]->visited) && ((edge->capacityForward - edge->flowForward) != 0))
    {
      DFSVisit(graph[edge->source]);
    }
    else
    {
      
    }

  }

}

void minimumCut()
{
  int i;
  edge_t edge;
  bool firstChar = true;
  printf("%d\n", graph[1]->excess);
  for (i = numSuppliers + 2; i < ((numSuppliers + 2) + numStations); i++)
  {
    for (edge = graph[i]->srcEdgeList; edge != 0; edge = edge->nextSrc)
    {
      if ((((graph[edge->source]->visited && (!graph[edge->destination]->visited)) || ((!graph[edge->source]->visited) && graph[edge->destination]->visited)) && (edge->source < edge->destination)) && ((edge->source + numStations) == edge->destination))
      {
        if (firstChar)
        {
          printf("%d", edge->source);
          firstChar = false;
        }
        else
        {
          printf(" %d", edge->source);
        }

      }
      else
      {
        
      }

    }

  }

  printf("\n");
  for (i = 0; i < (numSuppliers + 2); i++)
  {
    for (edge = graph[i]->srcEdgeList; edge != 0; edge = edge->nextSrc)
    {
      if ((((graph[edge->source]->visited && (!graph[edge->destination]->visited)) || ((!graph[edge->source]->visited) && graph[edge->destination]->visited)) && (edge->source != 0)) && (edge->destination != 0))
      {
        printf("%d %d\n", edge->source, edge->destination);
      }
      else
      {
        
      }

    }

  }

  for (i = (numSuppliers + 2) + numStations; i < ((numSuppliers + (numStations * 2)) + 2); i++)
  {
    for (edge = graph[i]->srcEdgeList; edge != 0; edge = edge->nextSrc)
    {
      if (((((graph[edge->source]->visited && (!graph[edge->destination]->visited)) || ((!graph[edge->source]->visited) && graph[edge->destination]->visited)) && (edge->source != 0)) && (edge->destination != 0)) && ((edge->capacityForward - edge->flowForward) == 0))
      {
        printf("%d %d\n", edge->source - numStations, edge->destination);
      }
      else
      {
        
      }

    }

  }

}

void PushRelabel()
{
  Preflow();
  while (verticesQueueFront != 0)
  {
    Discharge(verticesQueueFront);
    popQueue();
  }

}

int main()
{
  PushRelabel();
  DFSVisit(graph[1]);
  minimumCut();
  return 0;
}

