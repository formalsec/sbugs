/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int n_cols;
int n_lines;
int s_index;
int t_index;
typedef struct node
{
  int vertex_index;
  struct node *next;
  struct node *prev;
} node;
typedef node *link;
typedef struct AdjListElement
{
  link listHead;
  link listTail;
} adj_list_element;
typedef adj_list_element *adj_link;
typedef struct AdjList
{
  int size;
  adj_link *head;
} adj_list;
adj_list *adjList;
typedef struct queue
{
  int *items;
  int front;
  int rear;
} queue;
queue *bfs_Q = 0;
typedef enum color
{
  WHITE,
  GRAY,
  BLACK
} color;
color *colour;
int *pred;
link newNode(int vertex)
{
  link t = (link) malloc(sizeof(node));
  t->vertex_index = vertex;
  t->next = (t->prev = 0);
  return t;
}

void deleteNode(link node)
{
  if (node->prev != 0)
  {
    node->prev->next = node->next;
  }
  else
  {
    
  }

  if (node->next != 0)
  {
    node->next->prev = node->prev;
  }
  else
  {
    
  }

  free(node);
}

void freeVertexList(link head)
{
  link t = head;
  while (head != 0)
  {
    t = t->next;
    free(head);
    head = t;
  }

}

adj_link newAdjListElement()
{
  adj_link t = (adj_link) malloc(sizeof(adj_list_element));
  t->listHead = 0;
  t->listTail = 0;
  return t;
}

void freeAdjListElement(adj_link t)
{
  freeVertexList(t->listHead);
  free(t);
}

void initQueue()
{
  if (bfs_Q == 0)
  {
    bfs_Q = malloc(sizeof(queue));
    bfs_Q->items = (int *) malloc((sizeof(int)) * adjList->size);
  }
  else
  {
    
  }

  bfs_Q->front = -1;
  bfs_Q->rear = -1;
}

void freeQueue()
{
  free(bfs_Q->items);
  free(bfs_Q);
}

int isQEmpty()
{
  if (bfs_Q->rear == (-1))
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

void AddToQueue(int value)
{
  if (bfs_Q->rear != (adjList->size - 1))
  {
    if (bfs_Q->front == (-1))
    {
      bfs_Q->front = 0;
    }
    else
    {
      
    }

    bfs_Q->rear++;
    bfs_Q->items[bfs_Q->rear] = value;
  }
  else
  {
    
  }

}

int RemoveFromQueue()
{
  int item;
  if (isQEmpty())
  {
    item = -1;
  }
  else
  {
    item = bfs_Q->items[bfs_Q->front];
    bfs_Q->front++;
    if (bfs_Q->front > bfs_Q->rear)
    {
      bfs_Q->front = (bfs_Q->rear = -1);
    }
    else
    {
      
    }

  }

  return item;
}

void createEdge(int u, int v)
{
  link t;
  t = newNode(v);
  if (adjList->head[u]->listHead == 0)
  {
    adjList->head[u]->listHead = t;
    adjList->head[u]->listTail = t;
  }
  else
  {
    if (v == t_index)
    {
      t->next = adjList->head[u]->listHead;
      adjList->head[u]->listHead->prev = t;
      adjList->head[u]->listHead = t;
    }
    else
    {
      adjList->head[u]->listTail->next = t;
      t->prev = adjList->head[u]->listTail;
      adjList->head[u]->listTail = t;
    }

  }

}

void deleteEdge(int u, int v)
{
  link t = adjList->head[u]->listHead;
  if (t->vertex_index == v)
  {
    adjList->head[u]->listHead = adjList->head[u]->listHead->next;
    deleteNode(t);
  }
  else
  {
    while (t != 0)
    {
      if (t->vertex_index == v)
      {
        break;
      }
      else
      {
        
      }

      t = t->next;
    }

    deleteNode(t);
  }

}

void fillEdges()
{
  int i;
  int j;
  int vertex_index;
  for (i = 1; i <= n_lines; i++)
  {
    for (j = 1; j <= n_cols; j++)
    {
      vertex_index = ((n_cols * (i - 1)) + j) - 1;
      createEdge(2 * vertex_index, (2 * vertex_index) + 1);
      createEdge((2 * vertex_index) + 1, 2 * vertex_index);
      if (j != n_cols)
      {
        createEdge((2 * vertex_index) + 1, 2 * (vertex_index + 1));
        createEdge((2 * (vertex_index + 1)) + 1, 2 * vertex_index);
      }
      else
      {
        
      }

      if (i != n_lines)
      {
        createEdge((2 * vertex_index) + 1, 2 * (vertex_index + n_cols));
        createEdge((2 * (vertex_index + n_cols)) + 1, 2 * vertex_index);
      }
      else
      {
        
      }

    }

  }

}

void AdjListInit(int size)
{
  int i = 0;
  adjList = (adj_list *) malloc(sizeof(adj_list));
  if (adjList == 0)
  {
    exit(1);
  }
  else
  {
    
  }

  adjList->size = size;
  adjList->head = (adj_link *) malloc((sizeof(adj_link)) * size);
  s_index = adjList->size - 2;
  t_index = adjList->size - 1;
  if (adjList->head == 0)
  {
    exit(1);
  }
  else
  {
    
  }

  for (i = 0; i < size; i++)
    adjList->head[i] = newAdjListElement();

  fillEdges();
}

void freeAdjList()
{
  int i = 0;
  for (i = 0; i < adjList->size; i++)
    freeAdjListElement(adjList->head[i]);

  free(adjList->head);
  free(adjList);
}

void connectS(int u)
{
  if (adjList->head[2 * u]->listTail->vertex_index != s_index)
  {
    createEdge(s_index, 2 * u);
  }
  else
  {
    
  }

}

void connectT(int u)
{
  if (adjList->head[(2 * u) + 1]->listHead->vertex_index != t_index)
  {
    createEdge((2 * u) + 1, t_index);
  }
  else
  {
    
  }

}

void processInput()
{
  char line[100];
  int line_index = 1;
  int n_people;
  int n_markets;
  while (fgets(line, 100, stdin))
  {
    if (line_index == 1)
    {
      int size;
      n_cols = new_sym_var(sizeof(int) * 8);
      n_lines = new_sym_var(sizeof(int) * 8);
      size = 2 * (n_cols * n_lines);
      AdjListInit(size + 2);
      line_index++;
    }
    else
    {
      if (line_index == 2)
      {
        n_markets = new_sym_var(sizeof(int) * 8);
        n_people = new_sym_var(sizeof(int) * 8);
        line_index++;
      }
      else
      {
        if (line_index <= (n_markets + 2))
        {
          int l;
          int c;
          int vertex_index;
          c = new_sym_var(sizeof(int) * 8);
          l = new_sym_var(sizeof(int) * 8);
          vertex_index = ((n_cols * (l - 1)) + c) - 1;
          connectT(vertex_index);
          line_index++;
        }
        else
        {
          int l;
          int c;
          int vertex_index;
          c = new_sym_var(sizeof(int) * 8);
          l = new_sym_var(sizeof(int) * 8);
          vertex_index = ((n_cols * (l - 1)) + c) - 1;
          connectS(vertex_index);
          line_index++;
        }

      }

    }

  }

}

void Initialize()
{
  initQueue();
  memset(pred, -1, adjList->size * (sizeof(int)));
  memset(colour, WHITE, adjList->size * (sizeof(color)));
}

int EdmondsKarp()
{
  int flow = 0;
  pred = (int *) malloc((sizeof(int)) * adjList->size);
  colour = (color *) malloc((sizeof(color)) * adjList->size);
  pred[t_index] = 0;
  while (pred[t_index] != (-1))
  {
    Initialize();
    AddToQueue(s_index);
    colour[s_index] = GRAY;
    while (!isQEmpty())
    {
      int currentVertex;
      link t;
      currentVertex = RemoveFromQueue();
      t = adjList->head[currentVertex]->listHead;
      while (t != 0)
      {
        int adjVertex = t->vertex_index;
        if (colour[adjVertex] == WHITE)
        {
          colour[adjVertex] = GRAY;
          pred[adjVertex] = currentVertex;
          AddToQueue(adjVertex);
        }
        else
        {
          
        }

        t = t->next;
      }

      colour[currentVertex] = BLACK;
    }

    if (pred[t_index] != (-1))
    {
      int delta = 1;
      int p;
      for (p = t_index; p != s_index; p = pred[p])
      {
        deleteEdge(pred[p], p);
        createEdge(p, pred[p]);
      }

      flow += delta;
    }
    else
    {
      
    }

  }

  return flow;
}

void freeEdmondsKarp()
{
  freeQueue();
  free(pred);
  free(colour);
}

int CalculateMaxCirculation()
{
  return EdmondsKarp();
}

void free_all()
{
  freeAdjList();
  freeEdmondsKarp();
}

int main()
{
  int res;
  processInput();
  res = CalculateMaxCirculation();
  printf("%d\n", res);
  free_all();
  return 0;
}

