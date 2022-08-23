/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct AdjListNode
{
  int dest;
  int cap;
  int flow;
  struct AdjListNode *next;
} *AdjListNode;
typedef struct AdjList
{
  AdjListNode head;
} *AdjList;
typedef struct Vertex
{
  int v;
} *Vertex;
typedef struct Graph
{
  int V;
  Vertex ver;
  AdjList array;
} *Graph;
struct node
{
  int v;
  struct node *next;
};
typedef struct queue
{
  struct node *front;
  struct node *rear;
} *Queue;
struct node *addNode(int v)
{
  struct node *n = (struct node *) malloc(sizeof(struct node));
  n->v = v;
  n->next = 0;
  return n;
}

Queue createQueue()
{
  Queue q = (Queue) malloc(sizeof(struct queue));
  q->front = (q->rear = 0);
  return q;
}

void push(Queue q, int k)
{
  struct node *t = addNode(k);
  if (q->front == 0)
  {
    q->front = (q->rear = t);
    return;
  }
  else
  {
    
  }

  q->rear->next = t;
  q->rear = t;
}

void pop(Queue q)
{
  if (q->front == 0)
  {
    return;
  }
  else
  {
    
  }

  struct node *t = q->front;
  q->front = q->front->next;
  if (q->front == 0)
  {
    q->rear = 0;
  }
  else
  {
    
  }

  free(t);
}

void freeList(struct node *l)
{
  struct node *n;
  while (l != 0)
  {
    n = l;
    l = l->next;
    free(n);
  }

}

AdjListNode newAdjListNode(int dest, int cap)
{
  AdjListNode newNode = (AdjListNode) malloc(sizeof(struct AdjListNode));
  newNode->dest = dest;
  newNode->cap = cap;
  newNode->flow = 0;
  newNode->next = 0;
  return newNode;
}

Graph newGraph(int V)
{
  Graph g = (Graph) malloc(sizeof(struct Graph));
  g->V = V;
  g->ver = (Vertex) malloc(V * (sizeof(struct Vertex)));
  g->array = (AdjList) malloc(V * (sizeof(struct AdjList)));
  int i;
  for (i = 0; i < V; i++)
  {
    g->array[i].head = 0;
    g->ver[i].v = 0;
  }

  return g;
}

AdjListNode getEdge(Graph g, int u, int v)
{
  AdjListNode adj = g->array[u].head;
  while (adj != 0)
  {
    if (adj->dest == v)
    {
      return adj;
    }
    else
    {
      
    }

    adj = adj->next;
  }

  return 0;
}

void freeQueue(Queue q)
{
  while (q->front != 0)
  {
    struct node *t = q->front;
    struct node *n = q->front->next;
    q->front = n;
    free(t);
  }

  free(q);
}

void freeGraph(Graph g)
{
  int i;
  for (i = 0; i < g->V; i++)
  {
    AdjListNode adj = g->array[i].head;
    while (adj != 0)
    {
      AdjListNode aux = adj->next;
      free(adj);
      adj = aux;
    }

  }

  free(g->array);
  free(g->ver);
  free(g);
}

void addEdge(Graph g, int src, int dest, int cap)
{
  int dup = 0;
  AdjListNode adj = g->array[src].head;
  while (adj != 0)
  {
    AdjListNode aux = adj->next;
    if (adj->dest == dest)
    {
      dup = 1;
      break;
    }
    else
    {
      
    }

    adj = aux;
  }

  if (!dup)
  {
    AdjListNode newNode = newAdjListNode(dest, cap);
    newNode->next = g->array[src].head;
    g->array[src].head = newNode;
    newNode = newAdjListNode(src, cap);
    newNode->next = g->array[dest].head;
    g->array[dest].head = newNode;
  }
  else
  {
    
  }

}

void printGraph(Graph g)
{
  int i;
  for (i = 0; i < g->V; i++)
  {
    AdjListNode adj = g->array[i].head;
    printf("vertice %d\n", i);
    printf("Vertices adjacentes ao vertice %d\n", i);
    while (adj != 0)
    {
      printf(" (%d -> %d, flow= %d, cap= %d)\n", i, adj->dest, adj->flow, adj->cap);
      adj = adj->next;
    }

    printf("\n");
  }

  printf("==========Fim==========\n\n");
}

void printGrid(int A, int R, int s, int t, Graph g)
{
  int i;
  int j;
  for (i = 0; i < A; i++)
  {
    for (j = 0; j < R; j++)
    {
      if (getEdge(g, s, (i * R) + j) != 0)
      {
        printf("C ");
      }
      else
      {
        if (getEdge(g, (i * R) + j, t) != 0)
        {
          printf("S ");
        }
        else
        {
          printf("* ");
        }

      }

    }

    printf("\n");
  }

}

int inBounds(int A, int R, int i, int j)
{
  return ((0 <= i) && (i < A)) && ((0 <= j) && (j < R));
}

int min(int A, int B)
{
  if (A < B)
  {
    return A;
  }
  else
  {
    
  }

  return B;
}

int bfs(Graph g, int s, int t, int parent[], int visited[])
{
  Queue q = createQueue();
  memset(parent, -1, g->V * (sizeof(int)));
  memset(visited, 0, g->V * (sizeof(int)));
  push(q, s);
  parent[s] = -2;
  visited[s] = 1;
  while (q->front != 0)
  {
    int currN = q->front->v;
    int bottleneck = 9999;
    AdjListNode adj = g->array[currN].head;
    pop(q);
    while (adj != 0)
    {
      int to = adj->dest;
      if (visited[to] == 0)
      {
        if (((adj->cap - adj->flow) > 0) && (g->ver[to].v == 0))
        {
          parent[to] = currN;
          push(q, to);
          bottleneck = min(bottleneck, adj->cap - adj->flow);
          if (to == t)
          {
            freeQueue(q);
            return bottleneck;
          }
          else
          {
            
          }

        }
        else
        {
          
        }

        visited[to] = 1;
      }
      else
      {
        
      }

      adj = adj->next;
    }

  }

  freeQueue(q);
  return 0;
}

int edmondsKarp(Graph g, int s, int t)
{
  int maxFlow = 0;
  int *parent = (int *) malloc(g->V * (sizeof(int)));
  int *visited = (int *) malloc(g->V * (sizeof(int)));
  memset(visited, 0, g->V * (sizeof(int)));
  memset(parent, -1, g->V * (sizeof(int)));
  while (1)
  {
    int flow = bfs(g, s, t, parent, visited);
    if (flow == 0)
    {
      break;
    }
    else
    {
      
    }

    maxFlow += flow;
    int currN = t;
    while (currN != s)
    {
      int prevN = parent[currN];
      AdjListNode adj = getEdge(g, prevN, currN);
      adj->flow = flow;
      g->ver[prevN].v = 1;
      currN = prevN;
    }

  }

  free(parent);
  free(visited);
  return maxFlow;
}

int main(int argc, const char *argv[])
{
  int A = 0;
  int R = 0;
  int S = 0;
  int C = 0;
  int i = 0;
  int j = 0;
  A = new_sym_var(sizeof(int) * 8);
  R = new_sym_var(sizeof(int) * 8);
  S = new_sym_var(sizeof(int) * 8);
  C = new_sym_var(sizeof(int) * 8);
  int s = A * R;
  int t = (A * R) + 1;
  Graph g = newGraph((A * R) + 2);
  for (i = 0; i < A; i++)
  {
    for (j = 0; j < R; j++)
    {
      if (inBounds(A, R, i + 1, j))
      {
        addEdge(g, (i * R) + j, ((i + 1) * R) + j, 1);
      }
      else
      {
        
      }

      if (inBounds(A, R, i - 1, j))
      {
        addEdge(g, (i * R) + j, ((i - 1) * R) + j, 1);
      }
      else
      {
        
      }

      if (inBounds(A, R, i, j + 1))
      {
        addEdge(g, (i * R) + j, ((i * R) + j) + 1, 1);
      }
      else
      {
        
      }

      if (inBounds(A, R, i, j - 1))
      {
        addEdge(g, (i * R) + j, ((i * R) + j) - 1, 1);
      }
      else
      {
        
      }

    }

  }

  for (i = 0; i < S; i++)
  {
    int u = 0;
    int v = 0;
    u = new_sym_var(sizeof(int) * 8);
    v = new_sym_var(sizeof(int) * 8);
    u = u - 1;
    v = v - 1;
    addEdge(g, (u * R) + v, t, 1);
  }

  for (i = 0; i < C; i++)
  {
    int u = 0;
    int v = 0;
    u = new_sym_var(sizeof(int) * 8);
    v = new_sym_var(sizeof(int) * 8);
    u = u - 1;
    v = v - 1;
    addEdge(g, s, (u * R) + v, 1);
  }

  printf("%d\n", edmondsKarp(g, s, t));
  freeGraph(g);
  return 0;
}

