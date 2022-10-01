/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>


typedef struct node
{
  int current;
  struct node *next;
} *Node;
typedef struct vertex
{
  int height;
  int excessFlow;
  char visited : 1;
  int *adj;
  int size;
  int current;
} *Vertex;
typedef struct edge
{
  int sourceVertex;
  int destVertex;
  int currentFlow;
  int maxFlow;
} *Edge;
typedef Edge *EdgeList;
typedef Vertex *VertexList;
typedef int listSize;
typedef struct queue
{
  int size;
  Node first;
  Node last;
} *Queue;
typedef struct graph
{
  int numSources;
  int numStations;
  int numEdges;
  listSize edgeL;
  listSize vertexL;
  EdgeList edgeList;
  VertexList vertexList;
  Queue queue;
} *Graph;
typedef struct vpair
{
  int source;
  int destination;
} *Vpair;
Vpair newVpair(int s, int d)
{
  Vpair new = (Vpair) malloc(sizeof(struct vpair));
  new->source = s;
  new->destination = d;
  return new;
}

Vertex newVertex()
{
  Vertex new = (Vertex) malloc(sizeof(struct vertex));
  new->height = 0;
  new->excessFlow = 0;
  new->visited = 0;
  new->adj = 0;
  new->size = 0;
  return new;
}

Edge newEdge(int source, int destination, int maxFlow)
{
  Edge new = (Edge) malloc(sizeof(struct edge));
  new->sourceVertex = source;
  new->destVertex = destination;
  new->currentFlow = 0;
  new->maxFlow = maxFlow;
  return new;
}

Node newNode(int vertex)
{
  Node new = (Node) malloc(sizeof(struct node));
  new->current = vertex;
  new->next = 0;
  return new;
}

Queue newQueue()
{
  Queue new = (Queue) malloc(sizeof(struct queue));
  new->first = 0;
  new->last = 0;
  new->size = 0;
  return new;
}

void enQueue(Queue queue, int vertex)
{
  Node node = newNode(vertex);
  if (queue->size == 0)
  {
    queue->first = node;
    queue->last = node;
    queue->size++;
  }
  else
  {
    queue->last->next = node;
    queue->last = node;
    queue->size++;
  }

}

Node deQueue(Queue queue)
{
  Node temp = queue->first;
  if (queue->first == 0)
  {
    return 0;
  }
  else
  {
    
  }

  queue->first = queue->first->next;
  queue->size--;
  if (queue->size == 1)
  {
    queue->last = queue->first;
  }
  else
  {
    
  }

  if (queue->size == 0)
  {
    queue->last = 0;
  }
  else
  {
    
  }

  temp->next = 0;
  return temp;
}

Graph newGraph()
{
  char line[30];
  int sources;
  int stations;
  int edges;
  int value;
  int src;
  int src_v = 0;
  int dst;
  int dst_v = 0;
  int cap;
  int i;
  int aux = 0;
  int aux_2 = 0;
  Graph graph = (Graph) malloc(sizeof(struct graph));
  assert(fgets(line, 30, stdin));
  sources = new_sym_var(sizeof(int) * 8);
  stations = new_sym_var(sizeof(int) * 8);
  edges = new_sym_var(sizeof(int) * 8);
  graph->numSources = sources;
  graph->numStations = stations;
  graph->numEdges = edges;
  graph->queue = newQueue();
  graph->edgeL = (edges + stations) + sources;
  graph->vertexL = ((2 * stations) + sources) + 2;
  graph->edgeList = (EdgeList) malloc((sizeof(Edge)) * graph->edgeL);
  graph->vertexList = (VertexList) malloc((sizeof(Vertex)) * graph->vertexL);
  graph->vertexList[0] = newVertex();
  graph->vertexList[1] = newVertex();
  for (i = 2; i < (sources + 2); i++)
  {
    value = new_sym_var(sizeof(int) * 8);
    graph->vertexList[i] = newVertex();
    graph->edgeList[aux] = newEdge(0, i, value);
    graph->vertexList[i]->size++;
    graph->vertexList[0]->size++;
    aux += 1;
  }

  for (i = 0; i < stations; i++)
  {
    value = new_sym_var(sizeof(int) * 8);
    graph->vertexList[((2 + sources) + i) + aux_2] = newVertex();
    graph->vertexList[((3 + sources) + i) + aux_2] = newVertex();
    graph->edgeList[aux] = newEdge(((2 + sources) + i) + aux_2, ((3 + sources) + i) + aux_2, value);
    graph->vertexList[((2 + sources) + i) + aux_2]->size++;
    graph->vertexList[((3 + sources) + i) + aux_2]->size++;
    aux += 1;
    aux_2++;
  }

  i = 0;
  while (fgets(line, 30, stdin) && (i < (edges + 1)))
  {
    src = new_sym_var(sizeof(int) * 8);
    dst = new_sym_var(sizeof(int) * 8);
    cap = new_sym_var(sizeof(int) * 8);
    if (i != 0)
    {
      src_v = src;
      dst_v = dst;
      if (src > (sources + 1))
      {
        src_v = ((2 * src) - sources) - 1;
      }
      else
      {
        
      }

      if (dst > (sources + 1))
      {
        dst_v = ((2 * dst) - sources) - 2;
      }
      else
      {
        
      }

      graph->edgeList[aux] = newEdge(src_v, dst_v, cap);
      graph->vertexList[src_v]->size++;
      graph->vertexList[dst_v]->size++;
      aux += 1;
    }
    else
    {
      
    }

    i++;
  }

  Vertex currentVertex;
  for (i = 0; i < graph->vertexL; i++)
  {
    currentVertex = graph->vertexList[i];
    currentVertex->adj = (int *) malloc((sizeof(int)) * graph->vertexList[i]->size);
    currentVertex->size = 0;
  }

  Edge currentEdge;
  for (i = 0; i < graph->edgeL; i++)
  {
    currentEdge = graph->edgeList[i];
    currentVertex = graph->vertexList[currentEdge->sourceVertex];
    currentVertex->adj[currentVertex->size] = i;
    currentVertex->size++;
    currentVertex = graph->vertexList[currentEdge->destVertex];
    currentVertex->adj[currentVertex->size] = i;
    currentVertex->size++;
  }

  return graph;
}

int comparator(const void *p, const void *q)
{
  struct vpair **l = (struct vpair **) p;
  struct vpair **r = (struct vpair **) q;
  if ((*l)->source == (*r)->source)
  {
    return (*l)->destination - (*r)->destination;
  }
  else
  {
    
  }

  return (*l)->source - (*r)->source;
}

int compareStations(const void *a, const void *b)
{
  return (*((int *) a)) - (*((int *) b));
}

void initializePreflow(Graph graph)
{
  Vertex source = graph->vertexList[0];
  source->height = graph->vertexL;
  int currentNode;
  int i = 0;
  Edge currentEdge;
  while (i < source->size)
  {
    currentNode = source->adj[i];
    currentEdge = graph->edgeList[currentNode];
    if (currentEdge->sourceVertex == 0)
    {
      currentEdge->currentFlow = currentEdge->maxFlow;
      graph->vertexList[currentEdge->destVertex]->excessFlow = currentEdge->maxFlow;
      source->excessFlow = source->excessFlow - currentEdge->maxFlow;
      enQueue(graph->queue, currentEdge->destVertex);
    }
    else
    {
      
    }

    i++;
  }

}

void push(Graph graph, int vertex, Edge edge)
{
  Vertex current = graph->vertexList[vertex];
  Vertex next = 0;
  int flow = (edge->maxFlow < current->excessFlow) ? (edge->maxFlow) : (current->excessFlow);
  if (edge->sourceVertex == vertex)
  {
    edge->currentFlow = edge->currentFlow + flow;
    next = graph->vertexList[edge->destVertex];
    if ((edge->destVertex > 1) && (next->excessFlow == 0))
    {
      enQueue(graph->queue, edge->destVertex);
    }
    else
    {
      
    }

  }
  else
  {
    edge->currentFlow = edge->currentFlow - flow;
    next = graph->vertexList[edge->sourceVertex];
    if ((edge->sourceVertex > 1) && (next->excessFlow == 0))
    {
      enQueue(graph->queue, edge->sourceVertex);
    }
    else
    {
      
    }

  }

  current->excessFlow = current->excessFlow - flow;
  next->excessFlow = next->excessFlow + flow;
}

void relabel(Graph graph, int vertex)
{
  int minHeight = 32767;
  int currentHeight = 0;
  int i = 0;
  Vertex currentVertex = graph->vertexList[vertex];
  int currentNode;
  while (i < currentVertex->size)
  {
    currentNode = currentVertex->adj[i];
    if ((graph->edgeList[currentNode]->sourceVertex != vertex) && (graph->edgeList[currentNode]->currentFlow > 0))
    {
      currentHeight = graph->vertexList[graph->edgeList[currentNode]->sourceVertex]->height;
      if (currentHeight < minHeight)
      {
        minHeight = currentHeight;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    if ((graph->edgeList[currentNode]->destVertex != vertex) && ((graph->edgeList[currentNode]->maxFlow - graph->edgeList[currentNode]->currentFlow) > 0))
    {
      currentHeight = graph->vertexList[graph->edgeList[currentNode]->destVertex]->height;
      if (currentHeight < minHeight)
      {
        minHeight = currentHeight;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    i++;
  }

  currentVertex->height = minHeight + 1;
}

void Discharge(Graph graph, int vertex)
{
  int i = 0;
  Vertex currentVertex = graph->vertexList[vertex];
  int currentNode;
  Edge currentEdge;
  Vertex newVertex;
  while (currentVertex->excessFlow > 0)
  {
    if (currentVertex->size == i)
    {
      relabel(graph, vertex);
      i = 0;
      currentVertex->current = currentVertex->adj[i];
    }
    else
    {
      if (currentVertex->size > i)
      {
        currentVertex->current = currentVertex->adj[i];
        currentNode = currentVertex->adj[i];
        currentEdge = graph->edgeList[currentNode];
        if (currentEdge->sourceVertex == vertex)
        {
          if ((graph->edgeList[currentNode]->maxFlow - graph->edgeList[currentNode]->currentFlow) > 0)
          {
            newVertex = graph->vertexList[currentEdge->destVertex];
            if (currentVertex->height == (newVertex->height + 1))
            {
              push(graph, vertex, currentEdge);
            }
            else
            {
              i++;
            }

          }
          else
          {
            i++;
          }

        }
        else
        {
          if (currentEdge->destVertex == vertex)
          {
            if (graph->edgeList[currentNode]->currentFlow > 0)
            {
              newVertex = graph->vertexList[currentEdge->sourceVertex];
              if (currentVertex->height == (newVertex->height + 1))
              {
                push(graph, vertex, currentEdge);
              }
              else
              {
                i++;
              }

            }
            else
            {
              i++;
            }

          }
          else
          {
            
          }

        }

      }
      else
      {
        i++;
      }

    }

  }

}

void freeLinkedList(Node head)
{
  Node tmp;
  while (head != 0)
  {
    tmp = head;
    head = head->next;
    free(tmp);
  }

}

void freeQueue(Queue q)
{
  freeLinkedList(q->first);
  if (q->last != 0)
  {
    free(q->last);
  }
  else
  {
    
  }

  free(q);
}

int FIFOPushRelable(Graph graph)
{
  int i;
  initializePreflow(graph);
  Node vertex = 0;
  for (i = 2; i < graph->vertexL; i++)
  {
    graph->vertexList[i]->current = graph->vertexList[i]->adj[0];
  }

  while (graph->queue->size != 0)
  {
    vertex = deQueue(graph->queue);
    Discharge(graph, vertex->current);
    free(vertex);
  }

  freeQueue(graph->queue);
  return graph->vertexList[1]->excessFlow;
}

void DFSAlgorytm(Graph graph, int vertex)
{
  int count;
  int flow;
  graph->vertexList[vertex]->visited = 1;
  for (count = 0; count < graph->edgeL; count++)
  {
    if ((graph->edgeList[count]->sourceVertex == vertex) && (graph->vertexList[graph->edgeList[count]->destVertex]->visited == 0))
    {
      if (graph->edgeList[count]->currentFlow > 0)
      {
        DFSAlgorytm(graph, graph->edgeList[count]->destVertex);
      }
      else
      {
        
      }

    }
    else
    {
      if ((graph->edgeList[count]->destVertex == vertex) && (graph->vertexList[graph->edgeList[count]->sourceVertex]->visited == 0))
      {
        flow = graph->edgeList[count]->maxFlow - graph->edgeList[count]->currentFlow;
        if (flow > 0)
        {
          DFSAlgorytm(graph, graph->edgeList[count]->sourceVertex);
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

}

void freeVertex(Vertex v)
{
  free(v->adj);
  free(v);
}

void mincut(Graph graph, int *st, Vpair *edg)
{
  int st_count = 0;
  int edg_count = 0;
  int i;
  int esrc;
  int edst;
  Vertex src;
  Vertex dst;
  int numSources = graph->numSources;
  for (i = 0; i < graph->edgeL; i++)
  {
    src = graph->vertexList[graph->edgeList[i]->sourceVertex];
    dst = graph->vertexList[graph->edgeList[i]->destVertex];
    esrc = graph->edgeList[i]->sourceVertex;
    edst = graph->edgeList[i]->destVertex;
    if ((((src->visited != dst->visited) && (esrc != 0)) && (edst != 0)) && (graph->edgeList[i]->currentFlow > 0))
    {
      if ((((esrc - (numSources + 2)) % 2) == 1) && (esrc > (numSources + 1)))
      {
        if ((((edst - (numSources + 2)) % 2) == 0) && (edst > (numSources + 1)))
        {
          edg[edg_count++] = newVpair(((graph->numSources + esrc) + 1) / 2, ((graph->numSources + edst) + 2) / 2);
        }
        else
        {
          edg[edg_count++] = newVpair(((graph->numSources + esrc) + 1) / 2, edst);
        }

      }
      else
      {
        if ((edst == (esrc + 1)) && (edst > (graph->numSources + 1)))
        {
          st[st_count++] = ((graph->numSources + esrc) + (+2)) / 2;
        }
        else
        {
          if ((((edst - (numSources + 2)) % 2) == 0) && (edst > (numSources + 1)))
          {
            edg[edg_count++] = newVpair(esrc, ((graph->numSources + edst) + 2) / 2);
          }
          else
          {
            edg[edg_count++] = newVpair(esrc, edst);
          }

        }

      }

    }
    else
    {
      
    }

    free(graph->edgeList[i]);
  }

  free(graph->edgeList);
  for (i = 0; i < graph->vertexL; i++)
  {
    freeVertex(graph->vertexList[i]);
  }

  free(graph->vertexList);
  st = (int *) realloc(st, st_count * (sizeof(int)));
  edg = (Vpair *) realloc(edg, edg_count * (sizeof(Vpair)));
  qsort(edg, edg_count, sizeof(Vpair), comparator);
  qsort(st, st_count, sizeof(int), compareStations);
  for (i = 0; i < st_count; i++)
  {
    if (i == (st_count - 1))
    {
      printf("%d", st[i]);
    }
    else
    {
      printf("%d ", st[i]);
    }

  }

  printf("\n");
  for (i = 0; i < edg_count; i++)
    printf("%d %d\n", edg[i]->source, edg[i]->destination);

  free(st);
  for (i = 0; i < edg_count; i++)
  {
    free(edg[i]);
  }

  free(edg);
}

void DFS(Graph graph)
{
  int *stations = (int *) malloc((sizeof(int)) * graph->numStations);
  Vpair *edges = (Vpair *) malloc((sizeof(Vpair)) * graph->numEdges);
  DFSAlgorytm(graph, 1);
  mincut(graph, stations, edges);
}

int main(int argc, char *argv[])
{
  Graph graph = 0;
  graph = newGraph();
  printf("%d\n", FIFOPushRelable(graph));
  DFS(graph);
  free(graph);
  return 0;
}
