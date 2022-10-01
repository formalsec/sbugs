/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node
{
  int dest;
  int capacity;
  struct Node *next;
} Node;
typedef struct AdjList
{
  Node *head;
} AdjList;
typedef struct Graph
{
  int v;
  AdjList *array;
} Graph;
typedef struct Stack
{
  int top;
  int *array;
} Stack;
Graph *graph;
int num_av;
int num_str;
int num_sup;
int num_prs;
int num_nodes = 0;
Stack *create_stack(unsigned capacity)
{
  Stack *stack = (Stack *) malloc(sizeof(struct Stack));
  stack->top = -1;
  stack->array = (int *) malloc(capacity * (sizeof(int)));
  return stack;
}

int isEmpty(Stack *stack)
{
  return stack->top == (-1);
}

int pop(Stack *stack)
{
  if (isEmpty(stack))
  {
    return 0;
  }
  else
  {
    
  }

  return stack->array[stack->top--];
}

void push(Stack *stack, int item)
{
  stack->array[++stack->top] = item;
}

int getNode(int str, int av)
{
  return ((str - 1) * num_av) + (av - 1);
}

Node *new_node(int dest)
{
  Node *node = (Node *) malloc(sizeof(Node));
  node->dest = dest;
  node->next = 0;
  return node;
}

Graph *create_graph(int v)
{
  Graph *graph = (Graph *) malloc(sizeof(Graph));
  graph->v = v;
  graph->array = (AdjList *) malloc(v * (sizeof(AdjList)));
  int i;
  for (i = 0; i < v; i++)
  {
    graph->array[i].head = 0;
  }

  return graph;
}

void add_edge(int src, int dest, int capacity)
{
  Node *node = new_node(dest);
  node->next = graph->array[src].head;
  node->capacity = capacity;
  graph->array[src].head = node;
}

int get_Vin(int v)
{
  return v * 2;
}

int get_Vout(int v)
{
  return (v * 2) + 1;
}

void parse_input()
{
  int av = 0;
  int str = 0;
  int node = 0;
  long e;
  num_av = new_sym_var(sizeof(int) * 8);
  num_str = new_sym_var(sizeof(int) * 8);
  num_sup = new_sym_var(sizeof(int) * 8);
  num_prs = new_sym_var(sizeof(int) * 8);
  num_nodes = num_av * num_str;
  graph = create_graph((2 * num_nodes) + 2);
  for (e = 0; e < num_sup; e++)
  {
    av = new_sym_var(sizeof(int) * 8);
    str = new_sym_var(sizeof(int) * 8);
    node = getNode(str, av);
    add_edge(get_Vout(node), (2 * num_nodes) + 1, 1);
    add_edge((2 * num_nodes) + 1, get_Vout(node), 0);
  }

  for (e = 0; e < num_prs; e++)
  {
    av = new_sym_var(sizeof(int) * 8);
    str = new_sym_var(sizeof(int) * 8);
    node = getNode(str, av);
    add_edge(2 * num_nodes, get_Vin(node), 1);
    add_edge(get_Vin(node), 2 * num_nodes, 0);
  }

  for (e = 0; e < num_nodes; e++)
  {
    add_edge(get_Vin(e), get_Vout(e), 1);
    add_edge(get_Vout(e), get_Vin(e), 0);
    if ((e % num_av) > 0)
    {
      add_edge(get_Vout(e), get_Vin(e - 1), 1);
      add_edge(get_Vin(e - 1), get_Vout(e), 0);
    }
    else
    {
      
    }

    if ((e % num_av) < (num_av - 1))
    {
      add_edge(get_Vout(e), get_Vin(e + 1), 1);
      add_edge(get_Vin(e + 1), get_Vout(e), 0);
    }
    else
    {
      
    }

    if ((e / num_av) > 0)
    {
      add_edge(get_Vout(e), get_Vin(e - num_av), 1);
      add_edge(get_Vin(e - num_av), get_Vout(e), 0);
    }
    else
    {
      
    }

    if ((e / num_av) < (num_str - 1))
    {
      add_edge(get_Vout(e), get_Vin(e + num_av), 1);
      add_edge(get_Vin(e + num_av), get_Vout(e), 0);
    }
    else
    {
      
    }

  }

}

int bfs(int source, int target, int *parent)
{
  Node *node;
  Stack *stack = create_stack((2 * num_nodes) + 2);
  memset(parent, -1, ((2 * num_nodes) + 2) * (sizeof(int)));
  push(stack, source);
  parent[source] = -2;
  while (!isEmpty(stack))
  {
    int currentNode = pop(stack);
    node = graph->array[currentNode].head;
    while (node != 0)
    {
      if (parent[node->dest] == (-1))
      {
        if (node->capacity > 0)
        {
          parent[node->dest] = currentNode;
          if (node->dest == target)
          {
            free(stack->array);
            free(stack);
            return 1;
          }
          else
          {
            
          }

          push(stack, node->dest);
        }
        else
        {
          
        }

      }
      else
      {
        
      }

      node = node->next;
    }

  }

  free(stack->array);
  free(stack);
  return 0;
}

int max_capacity(int source, int dest)
{
  int max_capacity = 0;
  int *parent;
  Node *node;
  parent = (int *) malloc(((2 * num_nodes) + 2) * (sizeof(int)));
  while (1)
  {
    int flow = bfs(source, dest, parent);
    if (flow == 0)
    {
      break;
    }
    else
    {
      
    }

    max_capacity += 1;
    int currentNode = dest;
    while (currentNode != source)
    {
      int previousNode = parent[currentNode];
      node = graph->array[previousNode].head;
      while (node->dest != currentNode)
      {
        node = node->next;
      }

      node->capacity = !node->capacity;
      node = graph->array[currentNode].head;
      while (node->dest != previousNode)
      {
        node = node->next;
      }

      node->capacity = !node->capacity;
      currentNode = previousNode;
    }

  }

  free(parent);
  return max_capacity;
}

int main()
{
  parse_input();
  printf("%d\n", max_capacity(2 * num_nodes, (2 * num_nodes) + 1));
  return 0;
}
