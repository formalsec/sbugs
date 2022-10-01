/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


struct node;
typedef struct node *link;
typedef struct node
{
  struct node *next;
  int value;
} node;
struct vertice;
typedef struct vertice *edge;
typedef struct vertice
{
  struct vertice *next;
  int id;
  int cap;
} vertice;
typedef struct queue
{
  node *head;
  node *tail;
} queue;
typedef struct list
{
  vertice *head;
  vertice *tail;
} list;
int *parentsList;
int *currentPathCapacity;
list **adj;
int g;
int min(int a, int b)
{
  return (a < b) ? (a) : (b);
}

list *newList()
{
  list *new = (list *) malloc(sizeof(list));
  new->head = (new->tail = 0);
  return new;
}

void deleteList(list *l)
{
  if (l->head == 0)
  {
    free(l);
  }
  else
  {
    edge current = l->head;
    l->head = l->head->next;
    free(current);
    deleteList(l);
  }

}

void addEdge(int from, int to, int cap)
{
  list *adjList = adj[from];
  edge new = (edge) malloc(sizeof(vertice));
  new->next = 0;
  new->id = to;
  new->cap = cap;
  if (adjList->head == 0)
  {
    adjList->head = (adjList->tail = new);
  }
  else
  {
    adjList->tail->next = new;
    adjList->tail = new;
  }

}

queue *newQueue()
{
  queue *q = (queue *) malloc(sizeof(queue));
  q->head = 0;
  q->tail = 0;
  return q;
}

void deleteQueue(queue *q)
{
  link prev = q->head;
  link next = prev;
  while (next != 0)
  {
    next = prev->next;
    free(prev);
    prev = next;
  }

  free(q);
}

void push(queue *q, int value)
{
  if (q == 0)
  {
    q = newQueue();
  }
  else
  {
    
  }

  link new = (link) malloc(sizeof(node));
  new->value = value;
  new->next = 0;
  if (q->head == 0)
  {
    q->head = (q->tail = new);
  }
  else
  {
    q->tail->next = new;
    q->tail = new;
  }

}

int pop(queue *q)
{
  if ((q == 0) || (q->head == 0))
  {
    return -1;
  }
  else
  {
    if (q->head == q->tail)
    {
      int value = q->head->value;
      free(q->head);
      q->head = (q->tail = 0);
      return value;
    }
    else
    {
      int value = q->head->value;
      link old = q->head;
      q->head = q->head->next;
      free(old);
      return value;
    }

  }

}

int isEmpty(queue *q)
{
  return q->head == 0;
}

void deleteAll()
{
  int i;
  for (i = 0; i < g; i++)
  {
    deleteList(adj[i]);
  }

  free(adj);
  free(parentsList);
  free(currentPathCapacity);
}

void processInput()
{
  int m;
  int n;
  int s;
  int c;
  m = new_sym_var(sizeof(int) * 8);
  n = new_sym_var(sizeof(int) * 8);
  s = new_sym_var(sizeof(int) * 8);
  c = new_sym_var(sizeof(int) * 8);
  g = ((m * n) * 2) + 2;
  adj = (list **) malloc((sizeof(list *)) * g);
  int i;
  for (i = 0; i < g; i++)
  {
    adj[i] = newList();
  }

  for (i = 0; i < s; i++)
  {
    int x;
    int y;
    x = new_sym_var(sizeof(int) * 8);
    y = new_sym_var(sizeof(int) * 8);
    addEdge(0, (1 + ((m * 2) * (y - 1))) + (2 * (x - 1)), 1);
  }

  for (i = 0; i < c; i++)
  {
    int x;
    int y;
    x = new_sym_var(sizeof(int) * 8);
    y = new_sym_var(sizeof(int) * 8);
    addEdge(((1 + ((m * 2) * (y - 1))) + (2 * (x - 1))) + 1, g - 1, 1);
  }

  for (i = 1; i < (g - 2); i += 2)
  {
    addEdge(i, i + 1, 1);
  }

  for (i = 2; i < (g - 1); i += 2)
  {
    if ((i % (2 * m)) != 0)
    {
      addEdge(i, i + 1, 1);
    }
    else
    {
      
    }

    if (((i - 2) % (2 * m)) != 0)
    {
      addEdge(i, i - 3, 1);
    }
    else
    {
      
    }

    if ((i - (2 * m)) > 0)
    {
      addEdge(i, (i - (2 * m)) - 1, 1);
    }
    else
    {
      
    }

    if ((i + (2 * m)) < (g - 1))
    {
      addEdge(i, (i + (2 * m)) - 1, 1);
    }
    else
    {
      
    }

  }

}

int bfs(int startNode, int endNode)
{
  int i;
  for (i = 0; i < g; i++)
  {
    parentsList[i] = -1;
    currentPathCapacity[i] = 0;
  }

  queue *q = newQueue();
  push(q, startNode);
  parentsList[startNode] = 9;
  currentPathCapacity[startNode] = 9;
  while (!isEmpty(q))
  {
    int currentNode = pop(q);
    edge current = adj[currentNode]->head;
    while (current != 0)
    {
      int to = current->id;
      if (parentsList[to] == (-1))
      {
        if (current->cap == 1)
        {
          parentsList[to] = currentNode;
          currentPathCapacity[to] = min(currentPathCapacity[currentNode], current->cap);
          if (to == endNode)
          {
            deleteQueue(q);
            return currentPathCapacity[endNode];
          }
          else
          {
            
          }

          push(q, to);
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      current = current->next;
    }

  }

  deleteQueue(q);
  return 0;
}

int edmondsKarp(int startNode, int endNode)
{
  int maxFlow = 0;
  parentsList = (int *) malloc((sizeof(int)) * g);
  currentPathCapacity = (int *) malloc((sizeof(int)) * g);
  while (!0)
  {
    int flow = bfs(startNode, endNode);
    if (flow == 0)
    {
      break;
    }
    else
    {
      
    }

    maxFlow += flow;
    int currentNode = endNode;
    while (currentNode != startNode)
    {
      int previousNode = parentsList[currentNode];
      edge head = adj[previousNode]->head;
      while (head != 0)
      {
        if (head->id == currentNode)
        {
          head->cap -= flow;
          break;
        }
        else
        {
          
        }

        head = head->next;
      }

      int done = 0;
      head = adj[currentNode]->head;
      while (head != 0)
      {
        if (head->id == previousNode)
        {
          head->cap += flow;
          done = !0;
          break;
        }
        else
        {
          
        }

        head = head->next;
      }

      if (done == 0)
      {
        addEdge(currentNode, previousNode, flow);
      }
      else
      {
        
      }

      currentNode = previousNode;
    }

  }

  return maxFlow;
}

int main()
{
  processInput();
  printf("%d\n", edmondsKarp(0, g - 1));
  deleteAll();
  return 0;
}
