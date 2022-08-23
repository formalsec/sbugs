/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct Stack *createStack(int capacity);
void push(struct Stack *stack, int item);
int pop(struct Stack *stack);
struct Node *newNode(int dest);
struct Graph *createGraph(int V);
void addEdge(struct Graph *graph, int src, int dest);
void dfs(int at, int id, int n, int *ids, int *low, int *onStack, struct Stack *stack, struct Graph *graph);
void orderFriends(int n, struct Graph *graph);
void addGrade(int *grades, int numStudents);
void addFriend(int numConnections, struct Graph *graph);
void printGrade(int *grades, int numStudents);
void freeList(struct Node *head);
struct Stack
{
  int top;
  int *array;
  int capacity;
};
struct Node
{
  int dest;
  struct Node *next;
};
struct Graph
{
  int V;
  int *grades;
  struct Node **array;
};
struct Stack *createStack(int capacity)
{
  struct Stack *stack = (struct Stack *) calloc(1, sizeof(struct Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (int *) calloc(capacity, sizeof(int));
  return stack;
}

void push(struct Stack *stack, int item)
{
  assert(stack->top <= stack->capacity);
  stack->array[++stack->top] = item;
}

int pop(struct Stack *stack)
{
  if (stack->top == (-1))
  {
    return -1;
  }
  else
  {
    
  }

  return stack->array[stack->top--];
}

struct Node *newNode(int dest)
{
  struct Node *node = (struct Node *) malloc(sizeof(struct Node));
  node->dest = dest - 1;
  node->next = 0;
  return node;
}

struct Graph *createGraph(int V)
{
  struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
  graph->V = V;
  graph->array = (struct Node **) calloc(V, sizeof(struct Node *));
  graph->grades = (int *) calloc(V, sizeof(int));
  return graph;
}

void addEdge(struct Graph *graph, int src, int dest)
{
  struct Node *node = newNode(dest);
  if (graph->array[src - 1] == 0)
  {
    graph->array[src - 1] = node;
  }
  else
  {
    struct Node *temp = graph->array[src - 1];
    while (temp->next)
    {
      temp = temp->next;
    }

    temp->next = node;
  }

}

void dfs(int at, int id, int n, int *ids, int *low, int *onStack, struct Stack *stack, struct Graph *graph)
{
  int to;
  int node;
  push(stack, at);
  onStack[at] = !0;
  ids[at] = (low[at] = id++);
  struct Node *pCrawl = graph->array[at];
  while (pCrawl)
  {
    to = pCrawl->dest;
    graph->grades[at] = (graph->grades[at] > graph->grades[to]) ? (graph->grades[at]) : (graph->grades[to]);
    if (ids[to] == (-1))
    {
      dfs(to, id, n, ids, low, onStack, stack, graph);
      low[at] = (low[at] < low[to]) ? (low[at]) : (low[to]);
      graph->grades[at] = (graph->grades[at] > graph->grades[to]) ? (graph->grades[at]) : (graph->grades[to]);
    }
    else
    {
      if (onStack[to] == (!0))
      {
        low[at] = (low[at] < low[to]) ? (low[at]) : (low[to]);
        graph->grades[at] = (graph->grades[at] > graph->grades[to]) ? (graph->grades[at]) : (graph->grades[to]);
      }
      else
      {
        graph->grades[at] = (graph->grades[at] > graph->grades[to]) ? (graph->grades[at]) : (graph->grades[to]);
      }

    }

    pCrawl = pCrawl->next;
  }

  if (ids[at] == low[at])
  {
    node = pop(stack);
    onStack[node] = 0;
    graph->grades[node] = graph->grades[at];
    while (node != at)
    {
      onStack[node] = 0;
      graph->grades[node] = graph->grades[at];
      node = pop(stack);
    }

  }
  else
  {
    
  }

}

void orderFriends(int n, struct Graph *graph)
{
  int id = 0;
  int i;
  int ids[n];
  int *low;
  int onStack[n];
  low = (int *) calloc(n, sizeof(int));
  struct Stack *stack = createStack(n);
  for (i = 0; i < n; i++)
  {
    ids[i] = -1;
    low[i] = -1;
    onStack[i] = 0;
  }

  for (i = 0; i < n; i++)
  {
    if (ids[i] == (-1))
    {
      dfs(i, id, n, ids, low, onStack, stack, graph);
    }
    else
    {
      
    }

  }

  free(stack->array);
  free(stack);
  free(low);
}

void addGrade(int *grades, int numStudents)
{
  int i;
  int grade;
  char buffer[60];
  for (i = 0; i < numStudents; i++)
  {
    fgets(buffer, 60, stdin);
    grade = new_sym_var(sizeof(int) * 8);
    grades[i] = grade;
  }

}

void addFriend(int numConnections, struct Graph *graph)
{
  int i;
  int std1;
  int std2;
  char buffer[100];
  for (i = 0; i < numConnections; i++)
  {
    fgets(buffer, 100, stdin);
    std1 = new_sym_var(sizeof(int) * 8);
    std2 = new_sym_var(sizeof(int) * 8);
    addEdge(graph, std1, std2);
  }

}

void printGrade(int *grades, int numStudents)
{
  int i;
  for (i = 0; i < numStudents; i++)
  {
    printf("%d\n", grades[i]);
  }

}

void freeList(struct Node *head)
{
  struct Node *tmp;
  while (head != 0)
  {
    tmp = head;
    head = head->next;
    free(tmp);
  }

}

int main()
{
  int numStudents;
  int numConnections;
  char buffer[100];
  int i;
  fgets(buffer, 100, stdin);
  numStudents = new_sym_var(sizeof(int) * 8);
  numConnections = new_sym_var(sizeof(int) * 8);
  assert(numStudents > 0);
  struct Graph *graph = createGraph(numStudents);
  addGrade(graph->grades, numStudents);
  if (numConnections > 0)
  {
    addFriend(numConnections, graph);
    orderFriends(numStudents, graph);
  }
  else
  {
    
  }

  printGrade(graph->grades, numStudents);
  for (i = 0; i < numStudents; i++)
  {
    freeList(graph->array[i]);
  }

  free(graph->grades);
  free(graph->array);
  free(graph);
  return 0;
}

