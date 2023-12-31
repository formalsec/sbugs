#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>


typedef struct node
{
  void *element;
  struct node *next;
} Node;
typedef struct list
{
  Node *head;
  Node *tail;
} *List;
Node *nodeCreate(void *element);
void *nodeDestroy(Node *node);
List listCreate();
void listDestroy(List list, void (*freeElement)(void *));
void listPushBack(List list, void *element);
void listPushFront(List list, void *element);
void *listPopBack(List list);
void *listPopFront(List list);
Node *listIterator(List list);
typedef List Vertex;
typedef struct edge
{
  Vertex *orig;
  Vertex *dest;
  struct edge *residual;
  int capacity;
} Edge;
typedef struct network
{
  Vertex *vertices;
  int nVertices;
  int nAvenues;
  int nStreets;
  int nSupermarkets;
  int nHouses;
} Network;
Edge *createEdge(Vertex *orig, Vertex *dest, int capacity);
void destroyEdge(void *edge);
Node *nodeCreate(void *element)
{
  Node *node = (Node *) malloc(sizeof(Node));
  node->element = element;
  node->next = 0;
  return node;
}

void *nodeDestroy(Node *node)
{
  void *element = node->element;
  free(node);
  return element;
}

List listCreate()
{
  List list = (List) malloc(sizeof(struct list));
  list->head = 0;
  list->tail = 0;
  return list;
}

void listDestroy(List list, void (*freeElement)(void *))
{
  Node *iterator = listIterator(list);
  while ((iterator = list->head) != 0)
  {
    list->head = iterator->next;
    if (freeElement != 0)
    {
      freeElement(nodeDestroy(iterator));
    }
    else
    {
      nodeDestroy(iterator);
    }

  }

  free(list);
}

void listPushBack(List list, void *element)
{
  Node *node = nodeCreate(element);
  if (list->head == 0)
  {
    list->head = node;
  }
  else
  {
    list->tail->next = node;
  }

  list->tail = node;
}

void listPushFront(List list, void *element)
{
  Node *node = nodeCreate(element);
  if (list->head == 0)
  {
    list->tail = node;
  }
  else
  {
    node->next = list->head;
  }

  list->head = node;
}

void *listPopBack(List list)
{
  Node *temp;
  Node *iterator;
  if (list->head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  temp = list->tail;
  iterator = listIterator(list);
  if (iterator->next == 0)
  {
    list->head = 0;
    list->tail = 0;
  }
  else
  {
    while (iterator->next != list->tail)
      iterator = iterator->next;

    iterator->next = 0;
    list->tail = iterator;
  }

  return nodeDestroy(temp);
}

void *listPopFront(List list)
{
  Node *temp;
  if (list->head == 0)
  {
    return 0;
  }
  else
  {
    
  }

  temp = list->head;
  list->head = temp->next;
  list->tail = (list->head == 0) ? (0) : (list->tail);
  return nodeDestroy(temp);
}

Node *listIterator(List list)
{
  return list->head;
}

int listEmpty(List list)
{
  return list->head == 0;
}

Edge *createEdge(Vertex *orig, Vertex *dest, int capacity)
{
  Edge *edge = (Edge *) malloc(sizeof(Edge));
  edge->orig = orig;
  edge->dest = dest;
  edge->capacity = capacity;
  return edge;
}

void destroyEdge(void *edge)
{
  free(edge);
}

int buildingIndex(int avenue, int street, int nStreets)
{
  return (2 * (((avenue - 1) * nStreets) + street)) - 1;
}

int getBuildingIndex(int nStreets)
{
  int avenue;
  int street;
  avenue = new_sym_var(sizeof(int) * 8);
  street = new_sym_var(sizeof(int) * 8);
  return buildingIndex(avenue, street, nStreets);
}

void createResidualEdge(Vertex *orig, Vertex *dest, int capacity)
{
  Edge *mainEdge = createEdge(orig, dest, capacity);
  Edge *resEdge = createEdge(dest, orig, 0);
  mainEdge->residual = resEdge;
  resEdge->residual = mainEdge;
  listPushFront(*orig, mainEdge);
  listPushFront(*dest, resEdge);
}

void initialiseCityNetwork(Network *network)
{
  int i;
  int avenue;
  int street;
  int origI;
  int destI;
  int nVertices;
  int nAvenues;
  int nStreets;
  Vertex *v = network->vertices;
  nVertices = network->nVertices;
  nAvenues = network->nAvenues;
  nStreets = network->nStreets;
  for (i = 0; i < nVertices; i++)
    v[i] = listCreate();

  for (avenue = 1; avenue <= nAvenues; avenue++)
    for (street = 1; street <= nStreets; street++)
  {
    origI = buildingIndex(avenue, street, nStreets);
    destI = origI + 1;
    createResidualEdge(&v[origI], &v[destI], 1);
    if (avenue > 1)
    {
      createResidualEdge(&v[destI], &v[origI - (2 * nStreets)], 1);
    }
    else
    {
      
    }

    if (avenue < nAvenues)
    {
      createResidualEdge(&v[destI], &v[origI + (2 * nStreets)], 1);
    }
    else
    {
      
    }

    if (street > 1)
    {
      createResidualEdge(&v[destI], &v[origI - 2], 1);
    }
    else
    {
      
    }

    if (street < nStreets)
    {
      createResidualEdge(&v[destI], &v[origI + 2], 1);
    }
    else
    {
      
    }

  }


}

void destroyCityNetwork(Network *network)
{
  int i;
  int nVertices;
  Vertex *vertices;
  nVertices = network->nVertices;
  vertices = network->vertices;
  for (i = 0; i < nVertices; i++)
  {
    listDestroy(vertices[i], destroyEdge);
  }

  free(vertices);
}

int connected(Vertex *reference, Vertex *v)
{
  Node *iterator = listIterator(*v);
  Edge *edge;
  if (iterator != 0)
  {
    edge = (Edge *) iterator->element;
    return reference == edge->dest;
  }
  else
  {
    return 0;
  }

}

void processInput(Network *network)
{
  int i;
  int nSupermarkets;
  int nHouses;
  int nStreets;
  int nAvenues;
  int nVertices;
  Vertex *v;
  Vertex *source;
  Vertex *target;
  Vertex *current;
  network->nAvenues = new_sym_var(sizeof(int) * 8);
  network->nStreets = new_sym_var(sizeof(int) * 8);
  network->nSupermarkets = new_sym_var(sizeof(int) * 8);
  network->nHouses = new_sym_var(sizeof(int) * 8);
  nAvenues = network->nAvenues;
  nStreets = network->nStreets;
  network->nVertices = (2 * (nAvenues * nStreets)) + 2;
  network->vertices = (Vertex *) malloc(network->nVertices * (sizeof(Vertex)));
  nVertices = network->nVertices;
  initialiseCityNetwork(network);
  source = (v = network->vertices);
  target = &v[nVertices - 1];
  nSupermarkets = network->nSupermarkets;
  nHouses = network->nHouses;
  for (i = 0; i < nSupermarkets; i++)
  {
    current = &v[getBuildingIndex(nStreets) + 1];
    if (!connected(target, current))
    {
      createResidualEdge(current, target, 1);
    }
    else
    {
      
    }

  }

  for (i = 0; i < nHouses; i++)
  {
    current = &v[getBuildingIndex(nStreets)];
    if (!connected(source, current))
    {
      createResidualEdge(source, current, 1);
    }
    else
    {
      
    }

  }

}

int getVertexIndex(const Network *network, const Vertex *vertex)
{
  return vertex - network->vertices;
}

int bfsPath(Network *network, Vertex *orig, Vertex *dest, Edge **path)
{
  int i;
  int nVertices;
  List queue = listCreate();
  Vertex *currentVertex;
  Node *iterator;
  Edge *edge;
  nVertices = network->nVertices;
  for (i = 0; i < nVertices; i++)
    path[i] = 0;

  listPushBack(queue, orig);
  while (!listEmpty(queue))
  {
    currentVertex = (Vertex *) listPopFront(queue);
    if (currentVertex == dest)
    {
      break;
    }
    else
    {
      
    }

    iterator = listIterator(*currentVertex);
    while (iterator != 0)
    {
      edge = (Edge *) iterator->element;
      i = getVertexIndex(network, edge->dest);
      if (((edge->capacity != 0) && (path[i] == 0)) && (i != 0))
      {
        path[i] = edge;
        listPushBack(queue, edge->dest);
      }
      else
      {
        
      }

      iterator = iterator->next;
    }

  }

  listDestroy(queue, 0);
  return (path[nVertices - 1] != 0) ? (1) : (0);
}

void increaseFlow(Network *network, Edge **pi)
{
  Edge *edge = pi[network->nVertices - 1];
  while (edge != 0)
  {
    edge->capacity = 0;
    edge->residual->capacity = 1;
    edge = pi[getVertexIndex(network, edge->orig)];
  }

}

int findAugmentingPath(Network *network, Edge **pi)
{
  return bfsPath(network, network->vertices, &network->vertices[network->nVertices - 1], pi);
}

int edmondsKarp(Network *network)
{
  int maxFlow = 0;
  int nSupermarkets;
  int nHouses;
  Edge **path = (Edge **) malloc(network->nVertices * (sizeof(Edge *)));
  nSupermarkets = network->nSupermarkets, nHouses = network->nHouses;
  while (((maxFlow < nSupermarkets) && (maxFlow < nHouses)) && findAugmentingPath(network, path))
  {
    increaseFlow(network, path);
    maxFlow++;
  }

  free(path);
  return maxFlow;
}

int main()
{
  Network network;
  processInput(&network);
  printf("%d\n", edmondsKarp(&network));
  destroyCityNetwork(&network);
  return 0;
}

