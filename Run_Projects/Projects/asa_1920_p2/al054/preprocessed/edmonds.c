/*File generated by PreProcessor.py*/


#include <stdio.h> 
#include <stdlib.h>


typedef struct Node
{
  int dest;
  int flux;
  struct Node *next;
} *VerticeNode;
typedef struct VerticeList
{
  VerticeNode head;
  int type;
  int height;
  int excess;
  int color;
  int d;
  int pi;
} *VerticeList;
typedef struct Graph
{
  int numverts;
  int numedges;
  int nummarkets;
  int numcitizens;
  VerticeList vertices;
} *Graph;
typedef struct node
{
  int val;
} *node_t;
int front;
int tail;
node_t queue;
Graph graph;
void addEdge(int src, int dest)
{
  VerticeNode newNode = (VerticeNode) malloc(sizeof(struct Node));
  newNode->dest = dest;
  newNode->flux = 0;
  newNode->next = graph->vertices[src].head;
  graph->vertices[src].head = newNode;
}

void createGraph(int M, int N, int S, int C)
{
  int vert = (M * N) + 2;
  int edge = (((2 * (M - 1)) * (N - 1)) + (M - 1)) + (N - 1);
  int x;
  int y;
  graph = (Graph) malloc(sizeof(struct Graph));
  graph->numverts = vert;
  graph->numedges = edge;
  graph->nummarkets = S;
  graph->numcitizens = C;
  graph->vertices = (VerticeList) malloc(((vert * 2) - 2) * (sizeof(struct VerticeList)));
  int i;
  for (i = 0; i < ((graph->numverts * 2) - 2); ++i)
  {
    graph->vertices[i].head = 0;
    graph->vertices[i].type = 0;
    graph->vertices[i].height = 0;
    graph->vertices[i].excess = 0;
    graph->vertices[i].color = 3;
    graph->vertices[i].d = 0;
    graph->vertices[i].pi = 0;
  }

  for (i = 0; i < S; i++)
  {
    x = new_sym_var(sizeof(int) * 8);
    y = new_sym_var(sizeof(int) * 8);
    graph->vertices[(M * (y - 1)) + x].type = 2;
    addEdge((((M * (y - 1)) + x) + vert) - 1, vert - 1);
    addEdge(vert - 1, (((M * (y - 1)) + x) + vert) - 1);
  }

  for (i = 0; i < C; i++)
  {
    x = new_sym_var(sizeof(int) * 8);
    y = new_sym_var(sizeof(int) * 8);
    graph->vertices[(M * (y - 1)) + x].type = 1;
    addEdge(0, (M * (y - 1)) + x);
    addEdge((M * (y - 1)) + x, 0);
  }

  for (i = 1; i < (vert - 1); i++)
  {
    if ((i <= (M * (N - 1))) && (((graph->vertices[i].type != graph->vertices[i + M].type) || (graph->vertices[i + M].type == 0)) || (graph->vertices[i].type == 0)))
    {
      addEdge((i + vert) - 1, i + M);
      addEdge(i + M, (i + vert) - 1);
    }
    else
    {
      
    }

    if (((i % M) != 0) && (((graph->vertices[i].type != graph->vertices[i + 1].type) || (graph->vertices[i + 1].type == 0)) || (graph->vertices[i].type == 0)))
    {
      addEdge((i + vert) - 1, i + 1);
      addEdge(i + 1, (i + vert) - 1);
    }
    else
    {
      
    }

    if (((i != 1) && (((i - 1) % M) != 0)) && (((graph->vertices[i].type != graph->vertices[i - 1].type) || (graph->vertices[i - 1].type == 0)) || (graph->vertices[i].type == 0)))
    {
      addEdge((i + vert) - 1, i - 1);
      addEdge(i - 1, (i + vert) - 1);
    }
    else
    {
      
    }

    if ((i > M) && (((graph->vertices[i].type != graph->vertices[i - M].type) || (graph->vertices[i - M].type == 0)) || (graph->vertices[i].type == 0)))
    {
      addEdge((i + vert) - 1, i - M);
      addEdge(i - M, (i + vert) - 1);
    }
    else
    {
      
    }

    addEdge(i, (i + vert) - 1);
    addEdge((i + vert) - 1, i);
  }

}

int deQueue()
{
  int u = queue[front].val;
  front++;
  return u;
}

void enQueue(int u)
{
  queue[tail].val = u;
  tail++;
}

int Bfs()
{
  int i;
  graph->vertices[0].d = 0;
  graph->vertices[0].color = 4;
  graph->vertices[0].pi = 0;
  for (i = 1; i < ((graph->numverts * 2) - 2); ++i)
  {
    graph->vertices[i].d = -1;
    graph->vertices[i].color = 3;
    graph->vertices[i].pi = 0;
  }

  enQueue(0);
  VerticeNode vizinho;
  while (front != tail)
  {
    int u = deQueue();
    vizinho = graph->vertices[u].head;
    while (vizinho != 0)
    {
      if ((graph->vertices[vizinho->dest].color == 3) && (((vizinho->flux == 0) && ((((u > (graph->numverts - 1)) && (vizinho->dest < graph->numverts)) || (vizinho->dest == ((u + graph->numverts) - 1))) || (u == 0))) || ((vizinho->flux == (-1)) && (((u < (graph->numverts - 1)) && ((vizinho->dest > (graph->numverts - 1)) || (vizinho->dest == 0))) || (vizinho->dest == ((u - graph->numverts) + 1))))))
      {
        graph->vertices[vizinho->dest].color = 4;
        graph->vertices[vizinho->dest].d = graph->vertices[u].d + 1;
        graph->vertices[vizinho->dest].pi = u;
        if (vizinho->dest == (graph->numverts - 1))
        {
          tail = 0;
          front = 0;
          return 1;
        }
        else
        {
          
        }

        enQueue(vizinho->dest);
      }
      else
      {
        
      }

      vizinho = vizinho->next;
    }

    graph->vertices[u].color = 5;
  }

  return 0;
}

int edmondsKarp()
{
  int result = 0;
  while (Bfs())
  {
    result++;
    int v;
    int u = graph->numverts - 1;
    VerticeNode current;
    while (u != 0)
    {
      v = graph->vertices[u].pi;
      current = graph->vertices[v].head;
      while (current->dest != u)
      {
        current = current->next;
      }

      current->flux++;
      current = graph->vertices[u].head;
      while (current->dest != v)
      {
        current = current->next;
      }

      current->flux--;
      u = v;
    }

    if ((result == graph->numcitizens) || (result == graph->nummarkets))
    {
      return result;
    }
    else
    {
      
    }

  }

  return result;
}

int main()
{
  int M;
  int N;
  int S;
  int C;
  int result;
  M = new_sym_var(sizeof(int) * 8);
  N = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(int) * 8);
  C = new_sym_var(sizeof(int) * 8);
  createGraph(M, N, S, C);
  queue = (node_t) malloc(((graph->numverts * 2) - 2) * (sizeof(struct node)));
  result = edmondsKarp();
  printf("%d\n", result);
  return 0;
}
