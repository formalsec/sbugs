/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


struct Node
{
  int flow_here;
  int back_flow;
  int flow_cap;
  int Id;
  struct Node *next;
} Node;
struct QueueNode
{
  int Id;
  struct QueueNode *next;
} QueueNode;
int f;
int e;
int t;
int imaginary_id;
int max_flow;
struct QueueNode *first_point;
struct QueueNode *last_point;
int *parent;
int *visited;
struct Node *network;
void collect_input();
void calculate_max_flow();
void print_results();
int flow_here(int u, int v);
int flow_cap(int u, int v);
int subtract_flow(int u, int v, int path_flow);
int add_backflow(int u, int v, int path_flow);
int bfs(int s, int t);
int push_to_queue(int newValue, struct QueueNode *last_point, struct QueueNode *first_point);
int pop_from_queue(struct QueueNode *first_point);
void dfs(int s);
int main()
{
  collect_input();
  calculate_max_flow();
  return 0;
}

void collect_input()
{
  int i;
  int current = 2;
  int current_cap;
  int k;
  int o;
  int d;
  int z;
  char temp;
  struct Node *new_link;
  struct Node *network_point;
  z = 3;
  f = new_sym_var(sizeof(int) * 8);
  e = new_sym_var(sizeof(int) * 8);
  t = new_sym_var(sizeof(int) * 8);
  k = f + e;
  imaginary_id = (k + k) + 2;
  network = malloc((sizeof(Node)) * ((((2 + f) + f) + e) + e));
  do
  {
    z = 2;
    current_cap = new_sym_var(sizeof(int) * 8);
    temp = new_sym_var(sizeof(char) * 8);
    network[current - 1].Id = current;
    network[current - 1].flow_here = 0;
    network[current - 1].back_flow = 0;
    network[current - 1].next = 0;
    network[(current + k) - 1].Id = current + k;
    network[(current + k) - 1].flow_here = 0;
    network[(current + k) - 1].back_flow = 0;
    network[(current + k) - 1].next = 0;
    new_link = malloc(sizeof(Node));
    new_link->Id = current + k;
    new_link->next = 0;
    new_link->flow_here = current_cap;
    new_link->flow_cap = current_cap;
    new_link->back_flow = 0;
    network[current - 1].next = new_link;
    current++;
  }
  while (temp != '\n');
  current = f + 2;
  do
  {
    z = 2;
    current_cap = new_sym_var(sizeof(int) * 8);
    temp = new_sym_var(sizeof(char) * 8);
    network[current - 1].Id = current;
    network[current - 1].flow_here = 0;
    network[current - 1].back_flow = 0;
    network[current - 1].next = 0;
    network[(current + k) - 1].Id = current + k;
    network[(current + k) - 1].flow_here = current_cap;
    network[(current + k) - 1].back_flow = 0;
    network[(current + k) - 1].next = 0;
    new_link = malloc(sizeof(Node));
    new_link->Id = current + k;
    new_link->next = 0;
    new_link->flow_here = current_cap;
    new_link->back_flow = 0;
    new_link->flow_cap = current_cap;
    network[current - 1].next = new_link;
    current++;
  }
  while (temp != '\n');
  for (i = 0; i < t; i++)
  {
    z = 3;
    o = new_sym_var(sizeof(int) * 8);
    d = new_sym_var(sizeof(int) * 8);
    current_cap = new_sym_var(sizeof(int) * 8);
    o = network[o - 1].next->Id;
    network_point = &network[o - 1];
    new_link = malloc(sizeof(Node));
    new_link->Id = d;
    new_link->back_flow = 0;
    new_link->flow_here = current_cap;
    new_link->flow_cap = current_cap;
    new_link->next = network_point->next;
    network_point->next = new_link;
  }

  z = z + 1;
  network[imaginary_id - 1].Id = imaginary_id;
  network[imaginary_id - 1].flow_here = 0;
  network[imaginary_id - 1].back_flow = 0;
  network[imaginary_id - 1].next = 0;
  network_point = &network[imaginary_id - 1];
  for (i = 2; i <= (f + 1); i++)
  {
    new_link = malloc(sizeof(Node));
    new_link->Id = i;
    new_link->flow_here = 2147483647;
    new_link->flow_cap = 2147483647;
    new_link->back_flow = 0;
    new_link->next = network_point->next;
    network_point->next = new_link;
  }

}

void calculate_max_flow()
{
  int u;
  int v;
  int i;
  int path_flow = 2147483647;
  visited = malloc((sizeof(int)) * imaginary_id);
  parent = malloc((sizeof(int)) * imaginary_id);
  for (i = 0; i < imaginary_id; i++)
    parent[i] = 1;

  for (i = 0; i < imaginary_id; i++)
    visited[i] = 0;

  while (bfs(imaginary_id, 1) == 1)
  {
    path_flow = 2147483647;
    for (v = 1; v != imaginary_id; v = parent[v - 1])
    {
      u = parent[v - 1];
      path_flow = (path_flow < flow_here(u, v)) ? (path_flow) : (flow_here(u, v));
    }

    for (v = 1; v != imaginary_id; v = parent[v - 1])
    {
      u = parent[v - 1];
      subtract_flow(u, v, path_flow);
      add_backflow(u, v, path_flow);
    }

    max_flow += path_flow;
  }

  for (i = 0; i < imaginary_id; i++)
    visited[i] = 0;

  dfs(imaginary_id);
  print_results();
}

int flow_here(int u, int v)
{
  struct Node *current;
  current = &network[u - 1];
  current = current->next;
  while (current != 0)
  {
    if (current->Id == v)
    {
      return current->flow_here;
    }
    else
    {
      
    }

    current = current->next;
  }

  return 0;
}

int flow_cap(int u, int v)
{
  struct Node *current;
  current = &network[u - 1];
  current = current->next;
  while (current != 0)
  {
    if (current->Id == v)
    {
      return current->flow_cap;
    }
    else
    {
      
    }

    current = current->next;
  }

  return 0;
}

int subtract_flow(int u, int v, int path_flow)
{
  struct Node *current;
  current = &network[u - 1];
  current = current->next;
  while (current != 0)
  {
    if (current->Id == v)
    {
      current->flow_here = current->flow_here - path_flow;
      return 0;
    }
    else
    {
      
    }

    current = current->next;
  }

  return 0;
}

int add_backflow(int u, int v, int path_flow)
{
  struct Node *current;
  current = &network[u - 1];
  current = current->next;
  while (current != 0)
  {
    if (current->Id == v)
    {
      current->back_flow = current->back_flow + path_flow;
      return 0;
    }
    else
    {
      
    }

    current = current->next;
  }

  return 0;
}

int bfs(int s, int t)
{
  int visited[imaginary_id];
  int u;
  struct Node *current;
  struct QueueNode *newNode;
  newNode = malloc(sizeof(QueueNode));
  newNode->next = 0;
  newNode->Id = s;
  first_point = newNode;
  last_point = newNode;
  visited[s - 1] = 1;
  parent[s - 1] = -1;
  while (first_point->Id != (-1))
  {
    u = first_point->Id;
    pop_from_queue(first_point);
    current = &network[u - 1];
    current = current->next;
    while (current != 0)
    {
      if (visited[current->Id - 1] == 0)
      {
        push_to_queue(current->Id, last_point, first_point);
        parent[current->Id - 1] = u;
        visited[current->Id - 1] = 1;
      }
      else
      {
        
      }

      current = current->next;
    }

  }

  if (visited[t - 1] == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

int push_to_queue(int newValue, struct QueueNode *last_point, struct QueueNode *first_point)
{
  struct QueueNode *newNode;
  if (first_point->Id == (-1))
  {
    first_point->Id = newValue;
    return 0;
  }
  else
  {
    
  }

  newNode = malloc(sizeof(QueueNode));
  last_point->next = newNode;
  newNode->next = 0;
  newNode->Id = newValue;
  last_point = newNode;
  return 0;
}

int pop_from_queue(struct QueueNode *first_point)
{
  struct QueueNode *temp;
  if (first_point->next == 0)
  {
    first_point->Id = -1;
    return 0;
  }
  else
  {
    temp = first_point;
    first_point = temp->next;
    free(temp);
    return 0;
  }

}

void dfs(int s)
{
  struct Node *current;
  visited[s - 1] = 1;
  if (s != 1)
  {
    current = &network[s - 1];
    current = current->next;
    while (current != 0)
    {
      if ((visited[current->Id - 1] == 0) && (flow_here(s, current->Id) != 0))
      {
        dfs(current->Id);
      }
      else
      {
        
      }

      current = current->next;
    }

  }
  else
  {
    
  }

}

void print_results()
{
  int i;
  int j;
  int space = 0;
  printf("%d\n", max_flow);
  for (i = f + 2; i < ((f + e) + 2); i++)
  {
    for (j = (f + e) + 2; j < imaginary_id; j++)
    {
      if (((visited[i - 1] != 0) && (visited[j - 1] == 0)) && (flow_cap(i, j) != 0))
      {
        if (space)
        {
          printf(" ");
        }
        else
        {
          
        }

        printf("%d", i);
        space = 1;
      }
      else
      {
        
      }

    }

  }

  printf("\n");
  space = 0;
  for (i = (f + e) + 2; i < imaginary_id; i++)
  {
    for (j = f + 2; j < imaginary_id; j++)
    {
      if (((visited[i - 1] != 0) && (visited[j - 1] == 0)) && (flow_cap(i, j) != 0))
      {
        if (space)
        {
          printf("\n");
        }
        else
        {
          
        }

        printf("%d %d", (i - f) - e, j);
        space = 1;
      }
      else
      {
        
      }

    }

  }

}

