#include <stdio.h>
#include <stdlib.h>
#include <wasp.h>
typedef struct queue_el
{
  int id;
  struct queue_el *next;
} QueueEl;
typedef struct queue
{
  QueueEl *first;
  QueueEl *last;
} Queue;
typedef struct destinationNode
{
  int id;
  int from;
  int flow;
  int weight;
  int residualCapacity;
  struct destinationNode *reverseDestinationNode;
  struct destinationNode *nextNode;
} DestinationNode;
typedef struct baseNode
{
  DestinationNode *firstNode;
  DestinationNode *lastNode;
} BaseNode;
typedef struct graph
{
  int dim;
  BaseNode *nodes;
} Graph;
Graph *newGraph(int dim)
{
  int i;
  Graph *g = malloc(sizeof(Graph));
  BaseNode *b;
  g->dim = dim;
  g->nodes = malloc(g->dim * (sizeof(BaseNode)));
  b = g->nodes;
  for (i = 0; i < g->dim; i++)
  {
    (b + i)->firstNode = (void *) 0;
    (b + i)->lastNode = (void *) 0;
  }

  return g;
}

void freeGraph(Graph *g)
{
  int i;
  BaseNode *b;
  DestinationNode *d1;
  DestinationNode *d2;
  for (i = 0; i < g->dim; i++)
  {
    b = g->nodes + i;
    d1 = b->firstNode;
    while (d1)
    {
      d2 = d1->nextNode;
      free(d1);
      d1 = d2;
    }

  }

  free(g->nodes);
  free(g);
}

DestinationNode *newNode(Graph *g, int from, int to, int weight)
{
  BaseNode *b = g->nodes + from;
  DestinationNode *d = malloc(sizeof(DestinationNode));
  d->id = to;
  d->from = from;
  d->weight = weight;
  d->flow = 0;
  d->residualCapacity = weight;
  d->reverseDestinationNode = (void *) 0;
  d->nextNode = (void *) 0;
  if (b->firstNode == ((void *) 0))
  {
    b->firstNode = d;
  }
  else
  {
    b->lastNode->nextNode = d;
  }
  b->lastNode = d;
  return d;
}

void createProcessToProcessor(Graph *g, int id, int cost1, int cost2)
{
  DestinationNode *tmp1;
  DestinationNode *tmp2;
  tmp1 = newNode(g, 0, id, cost1);
  tmp2 = newNode(g, id, 0, 0);
  tmp1->reverseDestinationNode = tmp2;
  tmp2->reverseDestinationNode = tmp1;
  tmp1 = newNode(g, id, g->dim - 1, cost2);
  tmp2 = newNode(g, g->dim - 1, id, cost2);
  tmp1->reverseDestinationNode = tmp2;
  tmp2->reverseDestinationNode = tmp1;
}

void createProcessToProcess(Graph *g, int from, int to, int cost)
{
  DestinationNode *tmp1;
  DestinationNode *tmp2;
  tmp1 = newNode(g, from, to, cost);
  tmp2 = newNode(g, to, from, cost);
  tmp1->reverseDestinationNode = tmp2;
  tmp2->reverseDestinationNode = tmp1;
}

QueueEl *newQueueEl(int id)
{
  QueueEl *el = (QueueEl *) malloc(sizeof(QueueEl));
  el->id = id;
  el->next = (void *) 0;
  return el;
}

void freeQueueEl(QueueEl *el)
{
  free(el);
}

Queue *newQueue()
{
  Queue *q = (Queue *) malloc(sizeof(Queue));
  q->first = (void *) 0;
  q->last = (void *) 0;
  return q;
}

void freeQueue(Queue *q)
{
  QueueEl *aux1;
  QueueEl *aux2;
  aux1 = q->first;
  while (aux1)
  {
    aux2 = aux1->next;
    freeQueueEl(aux1);
    aux1 = aux2;
  }

  free(q);
}

int isQueueEmpty(Queue *q)
{
  if (!q->first)
  {
    return -1;
  }
  return 0;
}

void enQueue(Queue *q, int id)
{
  QueueEl *el = newQueueEl(id);
  if (isQueueEmpty(q))
  {
    q->first = el;
  }
  else
  {
    q->last->next = el;
  }
  q->last = el;
}

int deQueue(Queue *q)
{
  QueueEl *el;
  int id;
  if (isQueueEmpty(q))
    return 0;
  el = q->first;
  if (!q->first->next)
  {
    q->first = (void *) 0;
    q->last = (void *) 0;
  }
  else
  {
    q->first = el->next;
  }
  id = el->id;
  freeQueueEl(el);
  return id;
}

void clearQueue(Queue *q)
{
  QueueEl *aux1;
  QueueEl *aux2;
  aux1 = q->first;
  while (aux1)
  {
    aux2 = aux1->next;
    freeQueueEl(aux1);
    aux1 = aux2;
  }

  q->first = (void *) 0;
  q->last = (void *) 0;
}

Queue *q;
int *visited;
int bfs(Graph *g, int from, DestinationNode *path[], int to)
{
  int actual_node;
  int i;
  BaseNode *b;
  DestinationNode *d = (void *) 0;
  for (i = 0; i < g->dim; i++)
    visited[i] = 0;

  enQueue(q, from);
  visited[from] = 1;
  while (isQueueEmpty(q) == 0)
  {
    actual_node = deQueue(q);
    visited[actual_node] = 2;
    b = g->nodes + actual_node;
    d = b->firstNode;
    while (d)
    {
      if ((visited[d->id] == 0) && (d->residualCapacity > 0))
      {
        enQueue(q, d->id);
        visited[d->id] = 1;
        path[d->id] = d;
        if (d->id == (g->dim - 1))
        {
          clearQueue(q);
          return 1;
        }
      }
      d = d->nextNode;
    }

  }

  return 0;
}

int incrementFlow(Graph *g, DestinationNode *d, int increment)
{
  d->flow += increment;
  d->residualCapacity = d->weight - d->flow;
  return d->from;
}

int maxFlowPath(Graph *g, DestinationNode *path[])
{
  int pathFlow = 0;
  int pos = g->dim - 1;
  DestinationNode *d = path[pos];
  do
  {
    if (pathFlow == 0)
    {
      pathFlow = d->residualCapacity;
    }
    else
      if (pathFlow > d->residualCapacity)
    {
      pathFlow = d->residualCapacity;
    }
    pos = d->from;
    d = path[pos];
  }
  while (pos != 0);
  return pathFlow;
}

int maxFlow(Graph *g, DestinationNode *path[])
{
  int pos;
  int flow = 0;
  int pathFlow = 0;
  DestinationNode *d1;
  DestinationNode *d2;
  while (bfs(g, 0, path, g->dim - 1))
  {
    pos = g->dim - 1;
    pathFlow = maxFlowPath(g, path);
    flow += pathFlow;
    do
    {
      d1 = path[pos];
      pos = incrementFlow(g, d1, pathFlow);
      d2 = d1->reverseDestinationNode;
      incrementFlow(g, d2, -pathFlow);
    }
    while (pos != 0);
  }

  return flow;
}

int main()
{
  int num_tasks;
  int num_cost_com;
  int tmp1;
  int tmp2;
  int tmp3;
  int i;
  num_tasks = __WASP_symb_int("tasks");
  num_cost_com = __WASP_symb_int("cost_com");
  Graph *g = newGraph(num_tasks + 2);
  visited = (int *) malloc(g->dim * (sizeof(int)));
  DestinationNode *path[g->dim];
  q = newQueue();
  for (i = 0; i < num_tasks; i++)
  {
    tmp1 = __WASP_symb_int("tmp1");
    tmp2 = __WASP_symb_int("tmp2");
    createProcessToProcessor(g, i + 1, tmp1, tmp2);
  }

  for (i = 0; i < num_cost_com; i++)
  {
    tmp1 = __WASP_symb_int("tmp1");
    tmp2 = __WASP_symb_int("tmp2");
    tmp3 = __WASP_symb_int("tmp3");
    createProcessToProcess(g, tmp1, tmp2, tmp3);
  }

  printf("%d\n", maxFlow(g, path));
  free(visited);
  freeQueue(q);
  freeGraph(g);
  return 0;
}
