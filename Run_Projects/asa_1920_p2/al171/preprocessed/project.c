/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


enum crossing
{
  Empty,
  Supermarket,
  Residence
};
enum color
{
  White,
  Gray,
  Black
};
typedef struct Node
{
  int index;
  int crossing;
} Node;
typedef struct AdjNode
{
  Node *node;
  int r_capacity;
  struct AdjNode *next;
} AdjNode;
typedef struct Graph
{
  int numVertices;
  int M;
  int N;
  AdjNode **adjList;
} Graph;
int nodeIndex(int avenue, int street, int numAvenues)
{
  return (numAvenues * (street - 1)) + (avenue - 1);
}

void classifyNode(Graph *graph, int classification, int index)
{
  graph->adjList[index]->node->crossing = classification;
}

void addNode(Graph *graph, int index)
{
  Node *node = (Node *) malloc(sizeof(Node));
  node->index = index;
  node->crossing = Empty;
  AdjNode *adj_node = (AdjNode *) malloc(sizeof(AdjNode));
  adj_node->node = node;
  adj_node->r_capacity = -1;
  adj_node->next = 0;
  graph->adjList[index] = adj_node;
}

void addNodes(Graph *graph)
{
  int i;
  int numVertices = (graph->numVertices * 2) + 2;
  for (i = 0; i < numVertices; i++)
    addNode(graph, i);

}

void addEdge(Graph *graph, int index1, int index2, int capacity)
{
  AdjNode *tmp = graph->adjList[index1];
  Node *node = graph->adjList[index2]->node;
  AdjNode *new = (AdjNode *) malloc(sizeof(AdjNode));
  new->node = node;
  new->r_capacity = capacity;
  new->next = 0;
  while (tmp->next != 0)
  {
    tmp = tmp->next;
  }

  tmp->next = new;
}

void addEdges(Graph *graph, int index)
{
  int M = graph->M;
  int N = graph->N;
  int numVertices = graph->numVertices;
  addEdge(graph, index, index + numVertices, 1);
  addEdge(graph, index + numVertices, index, 0);
  if ((index % N) != 0)
  {
    addEdge(graph, index + numVertices, index - 1, 1);
    addEdge(graph, index - 1, index + numVertices, 0);
  }
  else
  {
    
  }

  if ((index % N) != (N - 1))
  {
    addEdge(graph, index + numVertices, index + 1, 1);
    addEdge(graph, index + 1, index + numVertices, 0);
  }
  else
  {
    
  }

  if (index >= N)
  {
    addEdge(graph, index + numVertices, index - N, 1);
    addEdge(graph, index - N, index + numVertices, 0);
  }
  else
  {
    
  }

  if (index < (N * (M - 1)))
  {
    addEdge(graph, index + numVertices, index + N, 1);
    addEdge(graph, index + N, index + numVertices, 0);
  }
  else
  {
    
  }

}

Graph *newGridGraph(int numAvenues, int numStreets)
{
  int i;
  int M = numStreets;
  int N = numAvenues;
  int numVertices = M * N;
  int rNumVertices = (numVertices * 2) + 2;
  Graph *graph = (Graph *) malloc(sizeof(Graph));
  graph->numVertices = numVertices;
  graph->M = M;
  graph->N = N;
  graph->adjList = (AdjNode **) malloc(rNumVertices * (sizeof(AdjNode *)));
  for (i = 0; i < rNumVertices; i++)
  {
    graph->adjList[i] = 0;
  }

  addNodes(graph);
  for (i = 0; i < numVertices; i++)
    addEdges(graph, i);

  return graph;
}

void freeGridGraph(Graph *graph)
{
  int i;
  int vertices = (graph->numVertices * 2) + 2;
  for (i = 0; i < vertices; i++)
  {
    free(graph->adjList[i]->node);
    AdjNode *current = graph->adjList[i];
    AdjNode *next;
    while (current != 0)
    {
      next = current->next;
      free(current);
      current = next;
    }

  }

  free(graph->adjList);
  free(graph);
}

void printGraph(Graph *graph)
{
  int v;
  for (v = 0; v < ((graph->numVertices * 2) + 2); v++)
  {
    AdjNode *temp = graph->adjList[v];
    if (temp->node->index == (graph->numVertices * 2))
    {
      printf("\n Adjacency list of Supersource \n ");
    }
    else
    {
      if (temp->node->index == ((graph->numVertices * 2) + 1))
      {
        printf("\n Adjacency list of Superdest \n ");
      }
      else
      {
        printf("\n Adjacency list of vertex %d\n ", v);
      }

    }

    while (temp)
    {
      if (temp->node->index == (graph->numVertices * 2))
      {
        printf("Supersource (%d) -> ", temp->r_capacity);
      }
      else
      {
        if (temp->node->index == ((graph->numVertices * 2) + 1))
        {
          printf("Superdest (%d) -> \n", temp->r_capacity);
        }
        else
        {
          printf("%d (%d)-> ", temp->node->index, temp->r_capacity);
        }

      }

      temp = temp->next;
    }

    printf("\n");
  }

}

int head;
int tail;
int *queue;
void enqueue(int v)
{
  queue[tail] = v;
  tail++;
}

int dequeue()
{
  int v = queue[head];
  head++;
  return v;
}

int bfs(Graph *graph, int supersource, int superdest, int *parent)
{
  int i;
  int u;
  int v;
  AdjNode *v_node;
  int numVertices = (graph->numVertices * 2) + 2;
  queue = (int *) malloc(numVertices * (sizeof(int)));
  int color[numVertices];
  for (i = 0; i < numVertices; i++)
    color[i] = White;

  head = (tail = 0);
  color[supersource] = Gray;
  parent[supersource] = -1;
  enqueue(supersource);
  while (head != tail)
  {
    u = dequeue();
    v_node = graph->adjList[u]->next;
    while (v_node != 0)
    {
      v = v_node->node->index;
      if ((color[v] == White) && (v_node->r_capacity > 0))
      {
        color[v] = Gray;
        parent[v] = u;
        enqueue(v);
      }
      else
      {
        
      }

      v_node = v_node->next;
    }

    color[u] = Black;
  }

  free(queue);
  return color[superdest] == Black;
}

void printPath(int *parent, int source, int dest)
{
  int i = parent[dest];
  printf(" Superdest <- ");
  while (i != source)
  {
    printf("%d <- ", i);
    i = parent[i];
  }

  printf(" Supersource: Path\n");
}

int min(int a, int b)
{
  return (a < b) ? (a) : (b);
}

int residualCapacity(Graph *graph, int u, int v)
{
  AdjNode *node = graph->adjList[u]->next;
  while (node->node->index != v)
    node = node->next;

  return node->r_capacity;
}

void updateCapacity(Graph *graph, int u, int v, int flow)
{
  AdjNode *forward_node = graph->adjList[u]->next;
  int supersource = graph->numVertices * 2;
  int superdest = (graph->numVertices * 2) + 1;
  while (forward_node->node->index != v)
    forward_node = forward_node->next;

  forward_node->r_capacity -= flow;
  if ((v != superdest) && (u != supersource))
  {
    AdjNode *backwards_node = graph->adjList[v]->next;
    while (backwards_node->node->index != u)
      backwards_node = backwards_node->next;

    backwards_node->r_capacity += flow;
  }
  else
  {
    
  }

}

int fordFulkerson(Graph *graph, int supersource, int superdest)
{
  int u;
  int v;
  int max_flow = 0;
  int *parent = (int *) malloc(((graph->numVertices * 2) + 2) * (sizeof(int)));
  while (bfs(graph, supersource, superdest, parent))
  {
    int path_flow = 32767 - 100;
    v = superdest;
    while (v != supersource)
    {
      u = parent[v];
      path_flow = min(path_flow, residualCapacity(graph, u, v));
      v = parent[v];
    }

    v = superdest;
    while (v != supersource)
    {
      u = parent[v];
      updateCapacity(graph, u, v, path_flow);
      v = parent[v];
    }

    max_flow += path_flow;
  }

  free(parent);
  return max_flow;
}

int main()
{
  int i;
  int numAvenues;
  int numStreets;
  int numSmarkets;
  int numPeople;
  int avenue;
  int street;
  int index;
  int supersource;
  int superdest;
  numAvenues = new_sym_var(sizeof(int) * 8);
  numStreets = new_sym_var(sizeof(int) * 8);
  numSmarkets = new_sym_var(sizeof(int) * 8);
  numPeople = new_sym_var(sizeof(int) * 8);
  Graph *graph = newGridGraph(numAvenues, numStreets);
  int numVertices = graph->numVertices;
  supersource = numVertices * 2;
  superdest = supersource + 1;
  for (i = 0; i < numSmarkets; i++)
  {
    avenue = new_sym_var(sizeof(int) * 8);
    street = new_sym_var(sizeof(int) * 8);
    index = nodeIndex(avenue, street, numAvenues);
    classifyNode(graph, Supermarket, index);
    addEdge(graph, index + numVertices, superdest, 32767 - 100);
  }

  for (i = 0; i < numPeople; i++)
  {
    avenue = new_sym_var(sizeof(int) * 8);
    street = new_sym_var(sizeof(int) * 8);
    index = nodeIndex(avenue, street, numAvenues);
    classifyNode(graph, Residence, index);
    addEdge(graph, supersource, index, 32767 - 100);
  }

  printf("%d\n", fordFulkerson(graph, supersource, superdest));
  freeGridGraph(graph);
  return 0;
}

