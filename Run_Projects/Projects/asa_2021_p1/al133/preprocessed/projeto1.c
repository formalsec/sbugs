/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>


typedef struct linked_ints
{
  int n;
  int level;
  struct linked_ints *next;
} linked_ints;
typedef struct node
{
  linked_ints *connections;
  int incoming;
  int chain;
} node;
int get_node(linked_ints *head)
{
  return head->n;
}

int get_level(linked_ints *head)
{
  return head->level;
}

linked_ints *push(linked_ints *head, int n)
{
  linked_ints *new_head = (linked_ints *) malloc(sizeof(linked_ints));
  new_head->n = n;
  new_head->level = 1;
  new_head->next = head;
  return new_head;
}

linked_ints *push_both(linked_ints *head, int n, int level)
{
  linked_ints *new_head = (linked_ints *) malloc(sizeof(linked_ints));
  new_head->n = n;
  new_head->level = level;
  new_head->next = head;
  return new_head;
}

linked_ints *pop(linked_ints *head)
{
  linked_ints *new_head = head->next;
  free(head);
  return new_head;
}

void destroy(linked_ints *head)
{
  while (head != 0)
  {
    head = pop(head);
  }

}

void print(linked_ints *head)
{
  linked_ints *printing = head;
  while (printing != 0)
  {
    printf("N: %d\n", printing->n + 1);
    printing = printing->next;
  }

}

void propagate(node *graph, linked_ints *path, int start)
{
  int chain = start;
  linked_ints *iterator = path;
  while (iterator != 0)
  {
    if (chain > graph[iterator->n].chain)
    {
      graph[iterator->n].chain = chain;
    }
    else
    {
      return;
    }

    chain++;
    iterator = iterator->next;
  }

}

int longest_chain(node *graph, linked_ints *queue)
{
  int max_chain = 0;
  int i;
  linked_ints *path = 0;
  while (queue != 0)
  {
    int node = get_node(queue);
    int level = get_level(queue);
    queue = pop(queue);
    if (graph[node].chain != (-1))
    {
      int new_chain = (level + graph[node].chain) - 1;
      if (new_chain > max_chain)
      {
        max_chain = new_chain;
      }
      else
      {
        
      }

      propagate(graph, path, graph[node].chain + 1);
      if (queue == 0)
      {
        break;
      }
      else
      {
        
      }

      int step = level - get_level(queue);
      for (i = 0; i < step; i++)
        path = pop(path);

      continue;
    }
    else
    {
      
    }

    path = push(path, node);
    linked_ints *iterator = graph[node].connections;
    if (iterator == 0)
    {
      propagate(graph, path, 1);
      if (level > max_chain)
      {
        max_chain = level;
      }
      else
      {
        
      }

      if (queue == 0)
      {
        break;
      }
      else
      {
        
      }

      int step = level - get_level(queue);
      for (i = 0; i < (step + 1); i++)
      {
        path = pop(path);
      }

    }
    else
    {
      
    }

    while (iterator != 0)
    {
      int end = get_node(iterator);
      iterator = iterator->next;
      queue = push_both(queue, end, level + 1);
    }

  }

  destroy(queue);
  return max_chain;
}

int main()
{
  int n_dependencies;
  int v;
  int i;
  node *graph;
  if (2 <= 0)
  {
    perror("Error reading arguments");
  }
  else
  {
    v = new_sym_var(sizeof(int) * 8);
    n_dependencies = new_sym_var(sizeof(int) * 8);
    
  }

  graph = (node *) malloc((sizeof(node)) * v);
  for (i = 0; i < v; i++)
  {
    graph[i].incoming = 0;
    graph[i].connections = 0;
    graph[i].chain = -1;
  }

  for (i = 0; i < n_dependencies; i++)
  {
    int source;
    int end;
    if (2 <= 0)
    {
      perror("Error reading arguments");
    }
    else
    {
      source = new_sym_var(sizeof(int) * 8);
      end = new_sym_var(sizeof(int) * 8);
      
    }

    graph[source - 1].connections = push(graph[source - 1].connections, end - 1);
    graph[end - 1].incoming++;
  }

  linked_ints *queue = 0;
  int n_sources = 0;
  for (i = 0; i < v; i++)
  {
    if (graph[i].incoming == 0)
    {
      n_sources++;
      queue = push(queue, i);
    }
    else
    {
      
    }

  }

  printf("%d %d\n", n_sources, longest_chain(graph, queue));
  for (i = 0; i < v; i++)
  {
    destroy(graph[i].connections);
  }

  free(graph);
  return 0;
}

